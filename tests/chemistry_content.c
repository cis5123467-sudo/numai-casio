/* Production navigation/content checks independent of the target CPU. */
#define __attribute__(x)
#define PLATFORM_DEVICE 1
#define NUMAI_VERSION "test"
#define main calculator_main
#include "../src/main.c"
#undef main
#include <assert.h>
/* Conservative font width for a content-capacity check; actual rendering is
 * checked separately with screenshots from the G3A in the SuperH emulator. */
int casio_width(const char *s,int n,bool small,bool bold) {
    int length=(int)strlen(s); if(n>=0 && n<length)length=n;
    return length*(small?5:bold?8:7);
}
void casio_text(int x,int y,const char *s,uint16_t a,uint16_t b,bool small,bool large,bool bold) {(void)x;(void)y;(void)s;(void)a;(void)b;(void)small;(void)large;(void)bold;}
void eadk_display_push_rect_uniform(eadk_rect_t r,eadk_color_t c) {(void)r;(void)c;}
extern const Course pinned_sciences[];
int main(void) {
    int retained=0;
    for (int s=0;s<3;s++) {
        const Course *old=&pinned_sciences[s], *now=&courses[s+3];
        assert(old->count==now->count);
        for(int ch=0;ch<old->count;ch++) {
            const Chapter *a=&old->chapters[ch], *b=&now->chapters[ch];
            if(s<2)assert(a->count==b->count);
            for(int i=0;i<a->count;i++) {
                const Topic *before=&a->topics[i], *after=NULL;
                for(int j=0;j<b->count;j++) if(!strcmp(before->title,b->topics[j].title))after=&b->topics[j];
                assert(after);
                assert(!strncmp(after->course,before->course,strlen(before->course)));
                if(s<2)assert(!strcmp(after->course,before->course));
                if(before->example)assert(after->example && !strcmp(after->example,before->example));
                if(s==2)retained++;
            }
        }
    }
    assert(retained==151);
    int index=-1;
    for(int i=0;i<course_count;i++) if(!strcmp(courses[i].code,"8462"))index=i;
    assert(index>=0); course_selection=(Selection){index,0};
    const Course *chem=course(); assert(chem->count==13);
    int pages=0,keys=0,maxlines=0;
    for(int c=0;c<chem->count;c++) {
        chapter_selection=(Selection){c,0};
        const Chapter *ch=chapter();
        assert(!strcmp(ch->topics[0].title,"Key Ideas") || c==10);
        for(int t=0;t<ch->count;t++) {
            topic_selection=(Selection){t,0}; const Topic *item=topic();
            assert(item->course && *item->course);
            if(item->key_ideas) {
                assert(strlen(item->course)>strlen(item->key_ideas));
                assert(strstr(item->course,"Detailed explanation and examples"));
                assert(strstr(item->key_ideas,"Key ideas")); keys++;
            }
            page=Topics; choose(); assert(page==Reading && read_content==item->course);
            read_length=0; wrap_topic_reading();
            if(read_length>maxlines)maxlines=read_length;
            assert(read_length<WRAP_LIMIT-3);
            if(item->key_ideas) {
                assert(handle_key(eadk_key_ok,false,false));
                assert(read_content==item->key_ideas && reading_is_topic());
                read_length=0; wrap_topic_reading(); assert(read_length<80);
                assert(handle_key(eadk_key_back,false,false));
                assert(page==Reading && read_content==item->course);
                assert(handle_key(eadk_key_exe,false,false));
                assert(read_content==item->key_ideas);
                assert(handle_key(eadk_key_exe,false,false));
                assert(read_content==item->course);
            }
            find_related();
            if(related_count) {
                assert(handle_key(eadk_key_var,false,false));
                assert(page==RelatedEquations || page==PhysicsDetail);
            }
            pages++;
        }
    }
    assert(pages==162 && keys==151);
    chapter_selection=(Selection){3,0}; assert(chapter()->count==18);
    assert(strstr(chapter()->topics[1].course,"CuO + C"));
    assert(strstr(chapter()->topics[2].course,"Aluminium"));
    assert(strstr(chapter()->topics[11].course,"0.0800"));
    page=Search; equation_search=false;
    set_field(&search_query,"chemistry cryolite",false); refresh_search(); assert(search_total>0);
    set_field(&search_query,"chemistry superphosphate",false); refresh_search(); assert(search_total>0);
    set_field(&search_query,"chemistry pentene",false); refresh_search(); assert(search_total>0);
    printf("%d Chemistry cards, %d Key ideas views, 13 section summaries, search, equation links and full text capacity passed (maximum %d conservative wrapped lines).\n",pages,keys,maxlines);
}
