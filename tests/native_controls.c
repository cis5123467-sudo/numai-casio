#define __attribute__(x)
/* Host integration checks run the production editor and handlers unchanged. */
#define PLATFORM_DEVICE 1
#define NUMAI_VERSION "test"
#define main calculator_main
#include "../src/main.c"
#undef main
#include <assert.h>
#include "../src/casio_keys.h"
static void key(int k) { assert(handle_key(k,false,false)); }
static void shifted_key(int k) { assert(handle_key(k,true,false)); }
static void reset_prompt(const char *s) { page=Prompt; native_menu=0; selecting_text=false; set_field(&prompt,s,false); }
int main(void) {
    const int physical[] = {0xa6,0x84,0xa7,0x86,0xa8,0xa9,0xab,0x74,0x85,0xac,0x76,0xaa,0x81,0x71,0x83,0x75,0xad,0x82,0x61,0x51,0xae,0x73,0x72,0xaf,0x55,0x64,0x65,0x66,0x53,0x54};
    for (int i=0;i<30;i++) {
        assert(casio_event_key(0,9-i/6,6-i%6,true)==physical[i]);
        assert(casio_event_key(0x63,9-i/6,6-i%6,false)==0x63);
    }
    assert(casio_event_key(0x14,1,3,true)==KEY_FORMAT);
    const int letters[]={eadk_key_xnt,eadk_key_fraction,eadk_key_sqrt,eadk_key_power,eadk_key_square,
        eadk_key_exp,eadk_key_comma,eadk_key_sine,eadk_key_cosine,eadk_key_tangent,
        eadk_key_left_parenthesis,eadk_key_right_parenthesis,eadk_key_seven,eadk_key_eight,
        eadk_key_nine,eadk_key_four,eadk_key_five,eadk_key_six,eadk_key_multiplication,
        eadk_key_division,eadk_key_one,eadk_key_two,eadk_key_three,eadk_key_plus,eadk_key_minus,eadk_key_zero};
    for(int i=0;i<26;i++) { assert(alpha_character(letters[i],true)=='A'+i); assert(alpha_character(letters[i],false)=='a'+i); }
    reset_prompt(""); for(int i=0;i<26;i++) assert(handle_key(letters[i],false,true));
    assert(!strcmp(prompt.text,"ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    reset_prompt("12345"); key(eadk_key_left); key(eadk_key_left); shifted_key(eadk_key_zero);
    key(eadk_key_left); key(eadk_key_left); assert(selection_start(&prompt)==1 && selection_end(&prompt)==3);
    key(eadk_key_ok); assert(native_menu==1); key(eadk_key_ok); assert(!strcmp(clipboard,"23"));
    key(eadk_key_right); shifted_key(eadk_key_dot); assert(!strcmp(prompt.text,"1232345"));
    key(eadk_key_clear); assert(!*prompt.text);
    reset_prompt("12345"); shifted_key(eadk_key_zero); key(eadk_key_left); key(eadk_key_left);
    key(eadk_key_ok); key(eadk_key_down); key(eadk_key_ok); assert(!strcmp(clipboard,"45") && !strcmp(prompt.text,"123"));
    reset_prompt("12"); key(eadk_key_left); shifted_key(eadk_key_backspace); key(eadk_key_nine);
    assert(!strcmp(prompt.text,"19")); shifted_key(eadk_key_backspace);
    reset_prompt(""); shifted_key(eadk_key_xnt); assert(!strcmp(prompt.text,"->"));
    reset_prompt(""); shifted_key(eadk_key_left_parenthesis); assert(!strcmp(prompt.text,"="));
    reset_prompt(""); shifted_key(eadk_key_seven); assert(!strcmp(prompt.text,"pi"));
    reset_prompt(""); shifted_key(eadk_key_sqrt); assert(!strcmp(prompt.text,"cbrt("));
    reset_prompt(""); shifted_key(eadk_key_power); assert(!strcmp(prompt.text,"log()/log()") && prompt.cursor==4);
    reset_prompt(""); key(eadk_key_ee); assert(!strcmp(prompt.text,"*10^"));
    reset_prompt(""); key(eadk_key_fraction); assert(!strcmp(prompt.text,"/"));
    reset_prompt(""); key(eadk_key_variable); key(eadk_key_ok); assert(lowercase_letters);
    key(eadk_key_down); key(eadk_key_ok); assert(!strcmp(prompt.text,"a"));
    reset_prompt(""); strcpy(ans,"42"); shifted_key(eadk_key_format); assert(!strcmp(prompt.text,"(42)"));
    page=PhysicsDetail; assert(handle_key(eadk_key_format,false,true)); assert(page==Prompt);
    key(eadk_key_settings); assert(page==Settings); key(eadk_key_back); assert(page==Prompt);
    key(eadk_key_nexttab); assert(page==Toolbox); key(eadk_key_nexttab); assert(page==CasMenu);
    key(eadk_key_nexttab); assert(page==Prompt); key(eadk_key_prevtab); assert(page==CasMenu);
    key(eadk_key_toolbox); assert(page==Toolbox); key(eadk_key_pageup); key(eadk_key_pagedown);
    assert(course_list_selection.row>0);
    double v; assert(cas_read_number("cbrt(-27)",&v) && fabs(v+3)<1e-10);
    assert(cas_read_number("log(8)/log(2)",&v) && fabs(v-3)<1e-10);
    puts("Native alphabet A-Z, case, clipboard copy/cut/paste, overwrite, clear, store, roots/logs, Ans, home, settings, tabs and paging passed");
}
