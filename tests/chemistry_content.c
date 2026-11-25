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
    int retained=0, summaries=0;
    for (int s=0;s<3;s++) {
        const Course *old=&pinned_sciences[s], *now=&courses[s+3];
        assert(old->count==now->count);
        for(int ch=0;ch<old->count;ch++) {
            const Chapter *a=&old->chapters[ch], *b=&now->chapters[ch];
            assert(a->count==b->count);
            assert(!strcmp(b->topics[0].title,"Key Ideas"));
            summaries++;
            for(int i=0;i<a->count;i++) {
                const Topic *before=&a->topics[i], *after=NULL;
                for(int j=0;j<b->count;j++) if(!strcmp(before->title,b->topics[j].title))after=&b->topics[j];
                assert(after);
                assert(!strncmp(after->course,before->course,strlen(before->course)));
                assert(!strcmp(after->course,before->course));
                if(before->example)assert(after->example && !strcmp(after->example,before->example));
                if(s==2)retained++;
            }
        }
    }
    assert(retained==162 && summaries==34);
    int index=-1;
    for(int i=0;i<course_count;i++) if(!strcmp(courses[i].code,"8462"))index=i;
    assert(index>=0); course_selection=(Selection){index,0};
    const Course *chem=course(); assert(chem->count==13);
    int pages=0,maxlines=0;
    for(int c=0;c<chem->count;c++) {
        chapter_selection=(Selection){c,0};const Chapter *ch=chapter();
        for(int t=0;t<ch->count;t++) {
            topic_selection=(Selection){t,0};const Topic *item=topic();
            assert(item->course && *item->course);
            page=Topics;choose();assert(page==Reading && read_content==item->course);
            read_length=0;wrap_topic_reading();assert(read_length<WRAP_LIMIT-3);
            if(read_length>maxlines)maxlines=read_length;
            find_related();if(related_count) {
                handle_key(eadk_key_var,false,false);
                for(int i=0;i<3 && page!=Reading;i++)handle_key(eadk_key_back,false,false);
                assert(page==Reading && read_content==item->course);
            }
            pages++;
        }
    }
    assert(pages==162);
    chapter_selection=(Selection){3,0}; assert(chapter()->count==18);
    assert(strstr(chapter()->topics[1].course,"CuO + C"));
    assert(strstr(chapter()->topics[2].course,"Aluminium"));
    assert(strstr(chapter()->topics[11].course,"0.0800"));
    page=Search;equation_search=false;
    set_field(&search_query,"chemistry cryolite",false);refresh_search();assert(search_total>0);
    page=CasMenu;
    assert(handle_key(eadk_key_four,false,false));
    assert(page==OrganicFamilies);
    int diagrams=0;
    for(int f=0;f<organic_family_count;f++) {
        organic_family=(Selection){f,0};
        choose();
        assert(page==OrganicList);
        for(int i=0;i<organic_families[f].count;i++) {
            organic_choice=(Selection){i,0};
            choose();
            assert(page==OrganicDetail);
            assert(handle_key(eadk_key_toolbox,false,false));
            assert(page==Reading && !strcmp(course()->code,"8462"));
            read_length=0;
            wrap_topic_reading();
            bool has_diagram=false;
            for(int line=0;line<read_length;line++) if(!wrapped[line].source)has_diagram=true;
            assert(has_diagram);
            back();
            assert(page==OrganicDetail);
            back();
            diagrams++;
        }
        page=OrganicFamilies;
    }
    assert(diagrams==18);
    page=PhysicsList;
    chemistry_sheet=false;
    physics_list_selection=(Selection){0};
    assert(handle_key(eadk_key_zero,false,false));
    assert(physics_list_selection.row==35);
    assert(handle_key(eadk_key_zero,false,false));
    assert(physics_list_selection.row==0);
    assert(handle_key(eadk_key_xnt,false,true)); /* Casio ALPHA+A: tenth row. */
    assert(page==PhysicsDetail && physics_selection.row==8);
    printf("34 first-position Key Ideas pages, all 162 Chemistry entries, 18 formula links, menu shortcuts and search passed. Maximum %d Chemistry lines.\n",maxlines);
}
