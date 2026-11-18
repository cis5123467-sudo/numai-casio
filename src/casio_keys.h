#ifndef NUMAI_CASIO_KEYS_H
#define NUMAI_CASIO_KEYS_H
#include <stdbool.h>
#include <gint/keycodes.h>
/* Canonical Graph Math+/fx-CG100 physical rows, top to bottom. Normalise
 * event positions too: older Math+-aware gint builds translate only rows
 * 7-9, leaving the function rows 5-6 with legacy CG50 event.key values.
 * keydown() already uses the full inverse map. Using row/column here prevents
 * a single physical press from delivering two different app actions. */
static const unsigned char casio_native_rows[30] = {
    KEY_ON, KEY_HOME, KEY_PREVTAB, KEY_UP, KEY_NEXTTAB, KEY_PAGEUP,
    KEY_SETTINGS, KEY_BACK, KEY_LEFT, KEY_OK, KEY_RIGHT, KEY_PAGEDOWN,
    KEY_SHIFT, KEY_ALPHA, KEY_VARS, KEY_DOWN, KEY_CATALOG, KEY_TOOLS,
    KEY_XOT, KEY_FRAC, KEY_SQRT, KEY_POWER, KEY_SQUARE, KEY_EXPFUN,
    KEY_COMMA, KEY_SIN, KEY_COS, KEY_TAN, KEY_LEFTP, KEY_RIGHTP
};
static inline int casio_event_key(int key, int row, int col, bool mathplus) {
    if (mathplus) {
        if (row >= 5 && row <= 9 && col >= 1 && col <= 6)
            return casio_native_rows[6*(9-row)+(6-col)];
        if (row == 1 && col == 3) return KEY_FORMAT;
    }
    return key;
}
#endif
