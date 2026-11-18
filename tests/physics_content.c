#define __attribute__(x)
#define PLATFORM_DEVICE 1
#define NUMAI_VERSION "test"
#define main calculator_main
#include "../src/main.c"
#undef main
#include <assert.h>
static int footer_rects,unit_rects,raised_digits,literal_slashes;
static bool check_units;
int casio_width(const char *s,int n,bool small,bool bold) {
    int length=(int)strlen(s);if(n>=0 && n<length)length=n;
    return length*(small?5:bold?8:7);
}
void casio_text(int x,int y,const char *s,uint16_t a,uint16_t b,bool small,bool large,bool bold) {
    (void)x;(void)y;(void)a;(void)b;(void)large;(void)bold;
    if(check_units) {
        assert(!strchr(s,'^'));
        if(small && !strcmp(s,"3"))raised_digits++;
        if(strchr(s,MathLiteralSlash))literal_slashes++;
    }
}
void eadk_display_push_rect_uniform(eadk_rect_t r,eadk_color_t c) {
    (void)c;if(r.x==0 && r.y==FOOTER && r.width==EADK_SCREEN_WIDTH && r.height==14)footer_rects++;
    if(check_units)unit_rects++;
}
extern const Course pinned_sciences[];
int main(void) {
    course_selection=(Selection){3,0}; assert(!strcmp(course()->code,"8463"));
    assert(course()->count==pinned_sciences[0].count);
    int count=0,maxlines=0;
    for(int ch=0;ch<course()->count;ch++) {
        chapter_selection=(Selection){ch,0}; const Chapter *current=chapter(),*expected=&pinned_sciences[0].chapters[ch];
        assert(current->count==expected->count);
        if(ch<8)assert(!strcmp(current->topics[0].title,"Key Ideas"));
        for(int t=0;t<current->count;t++) {
            topic_selection=(Selection){t,0};const Topic *a=topic(),*b=&expected->topics[t];
            assert(!strcmp(a->title,b->title) && !strcmp(a->course,b->course));
            assert(!strcmp(a->example,b->example));
            page=Topics;choose();assert(page==Reading && read_content==a->course);
            read_length=0;wrap_topic_reading();assert(read_length<WRAP_LIMIT-3);
            if(read_length>maxlines)maxlines=read_length;
            find_related();if(related_count) {
                handle_key(eadk_key_var,false,false);
                for(int i=0;i<3 && page!=Reading;i++)handle_key(eadk_key_back,false,false);
                assert(page==Reading && read_content==a->course);
            }
            count++;
        }
    }
    assert(count==129);
    assert(!math_word("in mol",2) && !math_word("to dm",2));
    assert(math_word("Is ",2) && math_word("to)",2));
    int links=0;
    for(int sheet=0;sheet<2;sheet++) {
        chemistry_sheet=sheet;
        int n=sheet?chemistry_equation_count:physics_equation_count;
        for(int i=0;i<n;i++) {
            physics_selection=(Selection){i,0};page=PhysicsDetail;
            open_physics_topic();
            assert(page==Reading);
            assert(!strcmp(course()->code,sheet?"8462":"8463"));
            const char *reference=equation()->section;
            assert(strcspn(topic()->course,"\n")==strlen(reference));
            assert(!strncmp(topic()->course,reference,strlen(reference)));
            links++;
        }
    }
    assert(links==64);
    page=Toolbox;course_list_selection=(Selection){1,0};choose();assert(page==Search && !equation_search);
    page=Prompt;set_field(&prompt,"",false);pin_notice=NULL;calc_count=0;footer_rects=0;
    draw();assert(CalcBottom==EADK_SCREEN_HEIGHT && footer_rects==0);
    pin_notice="Unsaved session";draw();assert(footer_rects==1);pin_notice=NULL;
    check_units=true;unit_text(10,50,"kg/m^3",Ink,White);check_units=false;
    assert(raised_digits>0 && literal_slashes>0 && unit_rects==0);
    printf("129 Physics entries match NumWorks v0.1.3; all 8 chapter summaries, links and capacity pass (maximum %d lines). Calculator footer/status and raised-unit/literal-slash checks pass.\n",maxlines);
}
