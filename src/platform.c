#include "eadk.h"
#include "palette.h"
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/clock.h>
#include <gint/hardware.h>
#include "casio_keys.h"
#include <string.h>

static bool dirty;

void casio_init(void) {
    extern void __printf_enable_fp(void);
    __printf_enable_fp();
    dclear(C_WHITE);
    key_event_t event;
    while ((event = pollevent()).type != KEYEV_NONE) {}
    while (keydown_any(KEY_EXE, KEY_OK, 0)) {
        clearevents();
        sleep_ms(10);
    }
}

void eadk_display_push_rect(eadk_rect_t rect, const eadk_color_t *pixels) {
    int right = rect.x + rect.width < DWIDTH ? rect.x + rect.width : DWIDTH;
    int bottom = rect.y + rect.height < DHEIGHT ? rect.y + rect.height : DHEIGHT;
    for (int y = rect.y; y < bottom; y++)
        for (int x = rect.x; x < right; x++)
            gint_vram[y * DWIDTH + x] = pixels[(y - rect.y) * rect.width + x - rect.x];
    dirty = true;
}

void eadk_display_push_rect_uniform(eadk_rect_t rect, eadk_color_t colour) {
    int right = rect.x + rect.width < DWIDTH ? rect.x + rect.width : DWIDTH;
    int bottom = rect.y + rect.height < DHEIGHT ? rect.y + rect.height : DHEIGHT;
    for (int y = rect.y; y < bottom; y++)
        for (int x = rect.x; x < right; x++) gint_vram[y * DWIDTH + x] = colour;
    dirty = true;
}

extern font_t casio_small_font;

static font_t text_font(bool small, bool bold) {
    font_t font = small ? casio_small_font : *dfont_default();
    if (bold) font.char_spacing++;
    return font;
}

static void native_symbols(const char *text, int length, char output[384]) {
    size_t position = 0;
    for (int i = 0; text[i] && (length < 0 || i < length) && position + 4 < 384; i++) {
        const char *symbol = NULL;
        if (text[i] == 24) symbol = "O";
        else if (text[i] == 25) symbol = "V";
        else if (text[i] == 26) symbol = "2";
        else if (text[i] == 29) symbol = "+";
        else if (text[i] == 30) symbol = "M";
        else if (text[i] == 31) symbol = "~";
        if (symbol) {
            while (*symbol) output[position++] = *symbol++;
        } else output[position++] = text[i] == 28 ? '/' : text[i];
    }
    output[position] = 0;
}

int casio_width(const char *text, int length, bool small, bool bold) {
    if (!text || !length || !*text) return 0;
    char native[384];
    native_symbols(text, length, native);
    font_t font = text_font(small, bold);
    int width;
    dsize(native, &font, &width, NULL);
    return width;
}

void casio_text(int x, int y, const char *text, uint16_t ink, uint16_t paper,
                bool small, bool large, bool bold) {
    (void)large;
    font_t font = text_font(small, bold);
    font_t const *previous = dfont(&font);
    char native[384];
    native_symbols(text, -1, native);
    int px = x;
    int py = y + (small ? 0 : 1);
    if (paper == PaleGold) {
        int width;
        dsize(native, &font, &width, NULL);
        drect(px, py, px + width - 1, py + font.data_height - 1, paper);
    }
    // Ordinary runs retain the font's proportional advances. The math
    // symbols have explicit shapes because the system font covers ASCII.
    const char *run = text;
    int position = px;
    for (const char *at = text;; at++) {
        bool symbol = (*at >= 24 && *at <= 26) || (*at >= 29 && *at <= 31);
        if (*at && !symbol) continue;
        char part[384];
        native_symbols(run, (int)(at-run), part);
        int width = 0;
        if (*part) {
            dtext_opt(position, py, ink, C_NONE, DTEXT_LEFT, DTEXT_TOP, part);
            if (bold) dtext_opt(position + 1, py, ink, C_NONE, DTEXT_LEFT, DTEXT_TOP, part);
            dsize(part, &font, &width, NULL);
            position += width;
            if (*at) position += font.char_spacing;
        }
        if (!*at) break;
        char marker[2] = {*at,0}, fallback[384];
        native_symbols(marker, 1, fallback);
        dsize(fallback, &font, &width, NULL);
        int left = position + 1, right = position + width - 2;
        int top = py + (small ? 0 : 1), bottom = top + 6;
        if (*at == 24) {
            dline(left+1,top,right-1,top,ink); dline(left+1,bottom,right-1,bottom,ink);
            dline(left,top+1,left,bottom-1,ink); dline(right,top+1,right,bottom-1,ink);
            dline(left,top+3,right,top+3,ink);
        } else if (*at == 25) {
            dline(left,top+3,left+2,bottom,ink); dline(left+2,bottom,left+4,top,ink);
            dline(left+4,top,right,top,ink);
        } else if (*at == 26) {
            int t = py;
            dline(left,t,left+2,t,ink); dpixel(left+2,t+1,ink); dpixel(left+1,t+2,ink);
            dline(left,t+3,left+2,t+3,ink);
        } else if (*at == 29) {
            // A square cross aligns with the centre of the native digit glyphs.
            int side = small ? 3 : 5;
            int cross_left = position + (width - side) / 2;
            int cross_top = py + 2;
            for (int i = 0; i < side; i++) {
                dpixel(cross_left+i, cross_top+i, ink);
                dpixel(cross_left+side-1-i, cross_top+i, ink);
            }
        } else if (*at == 30) {
            dline(left,top,right,top,ink);
            dline(left+1,top,left+1,bottom,ink);
            dline(right-1,top,right-1,bottom,ink);
        } else {
            for (int row = 0; row < 2; row++) {
                int y = py + (small ? 1 : 2) + row*3;
                int middle = (left+right)/2;
                dline(left,y+1,middle,y,ink);
                dline(middle,y,right,y+1,ink);
            }
        }
        position += width;
        if (at[1]) position += font.char_spacing;
        run = at + 1;
    }
    dfont(previous);
    dirty = true;
}

static const struct { int casio; eadk_key_t numworks; } keymap[] = {
    {KEY_LEFT, eadk_key_left}, {KEY_UP, eadk_key_up}, {KEY_DOWN, eadk_key_down}, {KEY_RIGHT, eadk_key_right},
    {KEY_OK, eadk_key_ok}, {KEY_EXE, eadk_key_exe}, {KEY_BACK, eadk_key_back}, {KEY_HOME, eadk_key_home},
    {KEY_SHIFT, eadk_key_shift}, {KEY_ALPHA, eadk_key_alpha},
    {KEY_XOT, eadk_key_xnt}, {KEY_X, eadk_key_xnt}, {KEY_VARS, eadk_key_variable},
    {KEY_CATALOG, eadk_key_toolbox}, {KEY_TOOLS, eadk_key_var}, {KEY_DEL, eadk_key_backspace},
    {KEY_EXPFUN, eadk_key_exp}, {KEY_LN, eadk_key_ln}, {KEY_LOG, eadk_key_log},
    {KEY_NEXTTAB, eadk_key_nexttab}, {KEY_COMMA, eadk_key_comma}, {KEY_POWER, eadk_key_power},
    {KEY_SIN, eadk_key_sine}, {KEY_COS, eadk_key_cosine}, {KEY_TAN, eadk_key_tangent},
    {KEY_NEG, eadk_key_pi}, {KEY_SQRT, eadk_key_sqrt}, {KEY_SQUARE, eadk_key_square},
    {KEY_7, eadk_key_seven}, {KEY_8, eadk_key_eight}, {KEY_9, eadk_key_nine},
    {KEY_LEFTP, eadk_key_left_parenthesis}, {KEY_RIGHTP, eadk_key_right_parenthesis},
    {KEY_4, eadk_key_four}, {KEY_5, eadk_key_five}, {KEY_6, eadk_key_six},
    {KEY_MUL, eadk_key_multiplication}, {KEY_DIV, eadk_key_division},
    {KEY_1, eadk_key_one}, {KEY_2, eadk_key_two}, {KEY_3, eadk_key_three},
    {KEY_ADD, eadk_key_plus}, {KEY_SUB, eadk_key_minus}, {KEY_0, eadk_key_zero},
    {KEY_DOT, eadk_key_dot}, {KEY_EXP, eadk_key_ee}, {KEY_STORE, eadk_key_store},
    {KEY_FORMAT, eadk_key_format}, {KEY_FRAC, eadk_key_fraction},
    {KEY_SETTINGS, eadk_key_settings}, {KEY_ACON, eadk_key_clear},
    {KEY_PREVTAB, eadk_key_prevtab}, {KEY_PAGEUP, eadk_key_pageup}, {KEY_PAGEDOWN, eadk_key_pagedown}
};

eadk_keyboard_state_t eadk_keyboard_scan(void) {
    eadk_keyboard_state_t state = 0;
    key_event_t event;
    while ((event = pollevent()).type != KEYEV_NONE) {
        if (event.type != KEYEV_DOWN) continue;
        int key = casio_event_key(event.key, event.row, event.col, gint[HWCALC] == HWCALC_FXCG100);
        for (unsigned i = 0; i < sizeof(keymap) / sizeof(*keymap); i++)
            if (keymap[i].casio == key) state |= UINT64_C(1) << keymap[i].numworks;
    }
    for (unsigned i = 0; i < sizeof(keymap) / sizeof(*keymap); i++)
        if (keydown(keymap[i].casio)) state |= UINT64_C(1) << keymap[i].numworks;
    return state;
}

void eadk_timing_msleep(uint32_t ms) {
    if (dirty) {
        dupdate();
        dirty = false;
    }
    if (ms) sleep_ms(ms);
}
