#include "eadk.h"
#include "topics.h"
#include "physics.h"
#include "units.h"
#include "solvers.h"
#include "mathview.h"
#include "scriptstore.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "NumAI";
const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

enum {
    White = 0xffff, Ink = 0x2104, Grey = 0x6b4d, Light = 0xef7d,
    Line = 0xd6ba, Gold = 0xfda6, PaleGold = 0xffb8, Blue = 0x32b8,
    HistoryTint = 0xf7bf, FocusTint = 0xd6bc, ModalBar = 0x630e, PlotRed = 0xe9a7
};
static const char higher_label[] = "(higher only)";
static const char physics_sheet_title[] = "AQA GCSE Physics equation sheet";
static const char chemistry_sheet_title[] = "AQA GCSE Chemistry equation sheet";

enum { CHAR_WIDTH = 7, CHAR_HEIGHT = 14, TEXT_WIDTH = 80, FOOTER = EADK_SCREEN_HEIGHT - 14,
       HISTORY_LIMIT = 5, WRAP_LIMIT = 240, FAVOURITE_LIMIT = 48, SESSION_LIMIT = 4, SESSION_NAME_SIZE = 24,
       CALCULATION_LIMIT = 12, EXTRA_LIMIT = 8 };

typedef enum { Prompt, Toolbox, Chapters, Topics, TopicMenu, Examples, Form, Reading,
               Result, CasMenu, History, Settings, Shortcuts, PhysicsList, PhysicsDetail,
               PhysicsSubjects, PhysicsForm, ScienceResult,
               UnitGroups, UnitFrom, UnitTo, UnitValue, UnitResult, Favourites,
               ToolForm, ToolOutput, DecimalPlaces, CalcHistory, CalcExtras,
               GeneralMenu, EquationFavourites, SessionName, SessionList, About, HistoryResult, Search, RelatedEquations } Page;
typedef enum { CoursePins, PhysicsPins, ChemistryPins } FavouriteGroup;
typedef enum { MenuCourses, MenuEquations, MenuNewSession, MenuOpenSession,
               MenuHistory, MenuShortcuts, MenuPreferences, MenuAbout, GeneralCount } GeneralItem;
enum { CasFavourites, CasPhysics, CasChemistry, CasUnits, CasRearrange, CasOperationStart,
       CasTrig = CasOperationStart + OperationCount - 1, CasTriangle, CasSearch, CasCount };
static const char *const general_items[GeneralCount] = {
    "Courses", "Equations and CAS", "New Session", "Open Session",
    "History", "Keyboard Shortcuts", "Preferences", "About"
};
typedef struct { int row, first; } Selection;
typedef struct {
    char text[EXPRESSION_SIZE];
    int cursor, anchor;
} Field;
typedef enum { ReuseNone, ReuseCas, ReuseTopic, ReuseScience, ReuseExtra, ReuseUnit } ReuseKind;
typedef struct {
    ReuseKind kind;
    int id, subject, course, chapter, topic, count;
    bool degrees;
    char inputs[SCIENCE_VARIABLES][EXPRESSION_SIZE];
} ReuseData;
typedef struct {
    ReuseData reuse;
    char question[EXPRESSION_SIZE];
    Operation operation;
    char title[TEXT_WIDTH + 1];
    Solution solution;
} HistoryEntry;
typedef struct {
    int length;
    bool highlight;
    const char *source;
} WrappedLine;
typedef enum { TrigSolver, TriangleSolver, PhysicsRearrange, ExtraToolCount } ExtraTool;
typedef struct { int course, chapter, row; bool equation, chemistry; } Favourite;
typedef struct { char input[EXPRESSION_SIZE]; CalculationValue result; } CalcEntry;
typedef struct { const char *label; char text[EXPRESSION_SIZE], reuse[EXPRESSION_SIZE]; } ExtraResult;
static const char *const extra_tool_names[] = {"Trigonometric equation solver", "Triangle solver",
                                                "Physics formula rearranger"};

static Page page, form_parent, result_parent, reading_parent;
static Page general_parent, toolbox_parent, cas_parent, favourite_parent;
static bool general_active;
static Page equation_parent = PhysicsList, tool_parent = CasMenu;
static Page search_parent, related_parent;
static bool equation_from_related;
static Selection search_selection, related_selection;
static Field search_query;
typedef struct { int course, chapter, row; bool equation, chemistry; } SearchMatch;
enum { SEARCH_LIMIT = 64 };
static SearchMatch search_matches[SEARCH_LIMIT], related_matches[SEARCH_LIMIT];
static int search_count, search_total, related_count;
static bool equation_search;
static Selection general_selection, equation_favourite_selection, session_selection, course_list_selection;
static Selection course_selection, chapter_selection, topic_selection, topic_action, cas_selection, settings_selection;
static Selection history_selection, example_selection, physics_selection, physics_subject;
static Selection unit_group, unit_from, unit_to;

static Selection favourite_selection, decimal_selection, physics_list_selection;
static FavouriteGroup favourite_group;
static Field physics_fields[SCIENCE_VARIABLES], unit_input;
static int physics_focus, physics_first, physics_offset, science_result_offset;
static bool chemistry_sheet, unit_input_error, unit_copied;
static bool physics_answer_ok;
static char physics_notes[SCIENCE_REFERENCE_SIZE], unit_expression[112], unit_work[112], unit_number[32];
static ScienceWorking science_work;
static Field prompt, forms[6], session_name;
static const char *form_labels[6];
static int field_count, active_field, form_first, read_offset, read_length, shortcuts_offset;
static const Topic *form_topic;
static Operation form_operation, result_operation;
static ExtraTool extra_tool;
static Solution tool_solution;
static int tool_first, tool_offset;
static Favourite favourites[FAVOURITE_LIMIT];
static int favourite_count;
static bool favourite_origin;
static const char *pin_notice, *session_error;
static CalcEntry calculations[CALCULATION_LIMIT];
static ExtraResult extra_results[EXTRA_LIMIT];
static int calc_count, calc_row, calc_first, calc_column, extras_count, extras_row, extras_first;
static HistoryEntry history[HISTORY_LIMIT];
static Solution solution;
static int history_count, history_offset;
static bool has_result, degrees = true, decimal, show_steps = true, shift;
static int decimal_places = 5;
static enum { AlphaOff, AlphaOnce, AlphaLocked } alpha;
static char clipboard[EXPRESSION_SIZE];
static bool lowercase_letters, selecting_text, overwrite_text;
static Field *clipboard_field, *native_field;
static int native_menu, native_row; /* 1: clipboard, 2: variables and symbols */
static Page native_parent = GeneralMenu;
static const char *const symbol_inputs[] = {"!", "=", ">", "<", "_", "%", "abs(", "ncr(", "npr(", "i", "{", "}", ":", "[", "]", "theta", "r"};
static int native_count(void) { return native_menu == 1 ? 2 : 27 + (int)(sizeof(symbol_inputs)/sizeof(*symbol_inputs)); }

static char ans[EXPRESSION_SIZE], result_question[EXPRESSION_SIZE];
static const char *read_content, *read_title;
static const char *related_read_content, *related_read_title;
static Page related_reading_parent;
static SearchMatch related_topic;
static int related_read_offset;
static WrappedLine wrapped[WRAP_LIMIT];
typedef struct {
    CalcEntry calculations[CALCULATION_LIMIT];
    HistoryEntry history[HISTORY_LIMIT];
    CasVariables variables;
    char ans[EXPRESSION_SIZE];
    int calc_count, history_count, preferences, decimal_places;
    unsigned sequence;
} Session;
static char session_names[SESSION_LIMIT][SESSION_NAME_SIZE];
static bool session_exists[SESSION_LIMIT];
static int session_count, active_session;

static void restore_session(const Session *next) {
    memcpy(calculations, next->calculations, sizeof(calculations));
    memcpy(history, next->history, sizeof(history));
    memcpy(ans, next->ans, sizeof(ans));
    cas_set_variables(&next->variables);
    calc_count = next->calc_count;
    history_count = next->history_count;
    calc_first = 0;
    has_result = false;
    prompt = (Field){0};
    page = Prompt;
}

static bool valid_reuse(const ReuseData *reuse);

#include "sessions.inc"

static void rectangle(int x, int y, int width, int height, eadk_color_t colour) {
    if (width <= 0 || height <= 0) return;
    eadk_display_push_rect_uniform((eadk_rect_t){x, y, width, height}, colour);
}

int casio_width(const char *, int, bool, bool);
void casio_text(int, int, const char *, uint16_t, uint16_t, bool, bool, bool);

static void draw_text(int x, int y, const char *text, eadk_color_t ink,
                      eadk_color_t paper, bool bold) {
    casio_text(x, y, text, ink, paper, false, false, bold);
}

static int styled_text(int x, int y, const char *text, eadk_color_t ink, eadk_color_t paper, bool draw) {
    bool science = page == Reading && y >= 25 && y < FOOTER && course_selection.row >= 0 &&
                   course_selection.row < course_count && !strncmp(courses[course_selection.row].code, "846", 3);
    if (!science) {
        if (draw) draw_text(x,y,text,ink,paper,false);
        return casio_width(text,-1,false,false);
    }
    int initial_x = x;
    static const char *const terms[] = {
        "photosynthesis", "respiration", "diffusion", "osmosis", "active transport", "nucleus",
        "mitochondria", "ribosomes", "enzymes", "antibodies", "antigens", "chromosomes", "alleles",
        "genotype", "phenotype", "negative feedback", "energy", "current", "potential difference",
        "resistance", "resultant", "velocity", "acceleration", "frequency", "wavelength",
        "irradiation", "contamination", "isotopes", "protons", "neutrons", "electrons",
        "oxidation", "reduction", "activation energy", "equilibrium", "moles", "catalyst",
        "exothermic", "endothermic", "independent variable", "dependent variable",
        "systematic", "random", "concentration", "Key ideas", "Understand the mechanism",
        "Apply your understanding", "Related equations", "Related formulas", "water",
        "membrane", "partially permeable", "concentration gradient", "turgid", "flaccid",
        "plasmids", "DNA", "chloroplasts", "mitosis", "meiosis", "stem cells",
        "pathogens", "vaccination", "antibiotics", "natural selection", "haemoglobin",
        "platelets", "glucose", "insulin", "glucagon", "thyroxine", "adrenaline",
        "receptors", "effectors", "synapses", "neurones", "habitat", "biodiversity",
        "mass", "charge", "force", "momentum", "density", "pressure", "half-life",
        "magnetic field", "induction", "infrared", "redshift", "ionic", "covalent",
        "delocalised", "ions", "electrolysis", "oxidation", "reduction", "precipitate",
        "chromatography", "functional group", "hydrocarbons", "polymers", "yield"
    };
    const char *at = text;
    while (*at && x < EADK_SCREEN_WIDTH) {
        const char *first = at;
        size_t bold_length = 0;
        while (*at && !bold_length) {
            if (at == text || !isalpha((unsigned char)at[-1])) {
                for (unsigned i = 0; i < sizeof(terms) / sizeof(*terms); i++) {
                    size_t length = strlen(terms[i]);
                    size_t j = 0;
                    while (j < length && at[j] && tolower((unsigned char)at[j]) == tolower((unsigned char)terms[i][j])) j++;
                    if (j == length && !isalpha((unsigned char)at[j])) { bold_length = length; break; }
                }
            }
            if (!bold_length) at++;
        }
        char segment[TEXT_WIDTH + 1];
        int length = (int)(at - first);
        if (length) {
            snprintf(segment, sizeof(segment), "%.*s", length, first);
            if (draw) draw_text(x, y, segment, ink, paper, false);
            x += casio_width(segment,-1,false,false);
        }
        if (bold_length) {
            snprintf(segment, sizeof(segment), "%.*s", (int)bold_length, at);
            if (draw) draw_text(x, y, segment, ink, paper, true);
            x += casio_width(segment,-1,false,true);
            at += bold_length;
        }
    }
    return x-initial_x;
}

static void string_at(int x, int y, const char *text, eadk_color_t ink, eadk_color_t paper) {
    styled_text(x,y,text,ink,paper,true);
}

static int styled_width(const char *text, int length) {
    if (!length || !*text) return 0;
    if (length < 0) length = (int)strlen(text);
    if (length > TEXT_WIDTH) length = TEXT_WIDTH;
    char copy[TEXT_WIDTH+1];
    memcpy(copy,text,(size_t)length);
    copy[length] = 0;
    return styled_text(0,30,copy,Ink,White,false);
}


static void fit_text(char output[TEXT_WIDTH + 1], const char *text, int pixels, int limit) {
    int length = (int)strcspn(text, "\n");
    if (limit > TEXT_WIDTH) limit = TEXT_WIDTH;
    if (length > limit) length = limit;
    memcpy(output, text, (size_t)length);
    output[length] = 0;
    bool truncated = text[length] && text[length] != '\n';
    while (length && casio_width(output, -1, false, false) + (truncated ? 15 : 0) > pixels) {
        output[--length] = 0;
        truncated = true;
    }
    if (truncated && length + 3 <= TEXT_WIDTH) memcpy(output + length, "...", 4);
}

static void clipped(int x, int y, const char *text, int columns, eadk_color_t ink, eadk_color_t paper) {
    char visible[TEXT_WIDTH + 1];
    fit_text(visible, text, EADK_SCREEN_WIDTH - x - 8, columns);
    string_at(x, y, visible, ink, paper);
}

static const char *higher_suffix(const char *title) {
    const char *suffix = strstr(title, " (higher only)");
    return suffix && !strcmp(suffix + 1, higher_label) ? suffix : NULL;
}

static void title_with_tier(int x, int y, const char *title, int columns,
                            eadk_color_t ink, eadk_color_t paper) {
    const char *suffix = higher_suffix(title);
    if (suffix) {
        char base[TEXT_WIDTH + 1], visible[TEXT_WIDTH + 1];
        snprintf(base, sizeof(base), "%.*s", (int)(suffix-title), title);
        int tail = casio_width(higher_label, -1, false, false);
        fit_text(visible, base, EADK_SCREEN_WIDTH - x - tail - 14, columns);
        string_at(x, y, visible, ink, paper);
        string_at(x + casio_width(visible,-1,false,false) + 6, y, higher_label, ink, paper);
    } else clipped(x, y, title, columns, ink, paper);
}

static const char *modifier_text(void) {
    if (selecting_text) return "CLIP";
    if (shift) return "SHIFT";
    return alpha == AlphaLocked ? (lowercase_letters ? "abc*" : "ABC*") :
           alpha ? (lowercase_letters ? "abc" : "ABC") : overwrite_text ? "OVR" : "";
}

static void header(const char *title, const char *tag, bool filled) {
    eadk_color_t paper = filled ? Gold : White;
    rectangle(0, 0, EADK_SCREEN_WIDTH, 21, paper);
    int margin = 8;
    if (tag) {
        int width = casio_width(tag, -1, false, false);
        string_at(EADK_SCREEN_WIDTH - 8 - width, 3, tag, Ink, paper);
        margin += width + 7;
    }
    const char *modifier = modifier_text();
    int modifier_width = casio_width(modifier, -1, false, false);
    if (modifier_width) {
        string_at(8, 3, modifier, filled ? White : Blue, paper);
        if (margin < modifier_width + 15) margin = modifier_width + 15;
    }
    char capital[160], centered[TEXT_WIDTH + 1];
    snprintf(capital, sizeof(capital), "%s", title);
    for (char *c = capital; *c; c++) *c = (char)toupper((unsigned char)*c);
    fit_text(centered, capital, EADK_SCREEN_WIDTH - 2*margin, TEXT_WIDTH);
    string_at((EADK_SCREEN_WIDTH-casio_width(centered,-1,false,false))/2,3,
              centered,filled ? White : Blue,paper);
    rectangle(0, 21, EADK_SCREEN_WIDTH, 2, Gold);
}

static void home_header(void) {
    rectangle(0, 0, EADK_SCREEN_WIDTH, 21, Gold);
    string_at(6, 3, degrees ? "deg" : "rad", White, Gold);
    string_at(38, 3, modifier_text(), White, Gold);
    string_at((EADK_SCREEN_WIDTH - casio_width("NUMAI",-1,false,false))/2, 3, "NUMAI", White, Gold);
}

static void footer(const char *label) {
    if (pin_notice) label = pin_notice;
    eadk_color_t paper = Light;
    rectangle(0, FOOTER, EADK_SCREEN_WIDTH, 14, paper);
    clipped(5, FOOTER, label, TEXT_WIDTH, Grey, paper);
}

static void scrollbar(int first, int total, int visible, int y, int height) {
    if (total <= visible) return;
    int bar = height * visible / total;
    if (bar < 7) bar = 7;
    rectangle(EADK_SCREEN_WIDTH - 3, y, 2, height, Light);
    rectangle(EADK_SCREEN_WIDTH - 3, y + (height - bar) * first / (total - visible), 2, bar, Line);
}

static MathBox revision_line(const char *, int, int, eadk_color_t, eadk_color_t, bool);

static void wrap(const char *text, int width, bool highlight, int *count) {
    int limit = width < TEXT_WIDTH ? width : TEXT_WIDTH;
    while (*text && *count < WRAP_LIMIT) {
        const char *start = text;
        int length = 0, space = -1;
        while (text[length] && text[length] != '\n' && length < limit &&
               styled_width(start, length + 1) <= EADK_SCREEN_WIDTH - 28) {
            if (text[length] == ' ') space = length;
            length++;
        }
        bool split = text[length] && text[length] != '\n';
        if (split && space > 0) length = space;
        if (!length && *text != '\n') length = 1;
        // Typeset fractions and powers can change the width of an inline run.
        char line[TEXT_WIDTH + 1];
        for (;;) {
            memcpy(line, start, (size_t)length);
            line[length] = 0;
            if (revision_line(line, 0, 0, Ink, White, false).width <= EADK_SCREEN_WIDTH - 28 || length <= 1) break;
            int previous = length - 1;
            while (previous > 0 && start[previous] != ' ') previous--;
            length = previous ? previous : length - 1;
        }
        wrapped[(*count)++] = (WrappedLine){length, highlight, start};
        text = start + length;
        if (*text == '\n') text++;
        else while (*text == ' ') text++;
    }
}

#include "revision_view.inc"

static int selection_start(const Field *field) {
    return field->cursor < field->anchor ? field->cursor : field->anchor;
}

static int selection_end(const Field *field) {
    return field->cursor > field->anchor ? field->cursor : field->anchor;
}

static void field_entry(int x, int y, int width, const Field *field, const char *placeholder, bool focused) {
    int columns = TEXT_WIDTH;
    int start = 0;
    while (start < field->cursor &&
           casio_width(field->text + start, field->cursor - start, false, false) > width - 12) start++;
    eadk_color_t edge = focused ? Gold : Line;
    rectangle(x, y, width, 18, edge);
    rectangle(x + 1, y + 1, width - 2, 16, White);
    char content[TEXT_WIDTH + 1];
    if (!*field->text && placeholder) {
        clipped(x + 4, y + 2, placeholder, columns, Grey, White);
    } else {
        int count = (int)strlen(field->text + start);
        if (count > columns) count = columns;
        while (count && casio_width(field->text + start, count, false, false) > width - 12) count--;
        int lo = focused ? selection_start(field) - start : 0;
        int hi = focused ? selection_end(field) - start : 0;
        if (lo < 0) lo = 0;
        if (hi > count) hi = count;
        if (lo > count) lo = count;
        if (hi < lo) hi = lo;
        const int boundaries[] = {0, lo, hi, count};
        for (int i = 0; i < 3; i++) {
            int offset = boundaries[i], n = boundaries[i + 1] - offset;
            if (!n) continue;
            memcpy(content, field->text + start + offset, (size_t)n);
            content[n] = 0;
            string_at(x + 4 + casio_width(field->text + start, offset, false, false),
                      y + 2, content, Ink, i == 1 ? PaleGold : White);
        }
    }
    if (focused && field->anchor == field->cursor)
        rectangle(x + 4 + casio_width(field->text + start, field->cursor - start, false, false),
                  y + 3, 1, 12, Blue);
}

static void large_math_text(int x, int y, const char *text, uint16_t ink, uint16_t paper, bool small);

static bool expression_draft(const Field *field, char preview[EXPRESSION_SIZE], int width, bool large,
                             MathBox *box) {
    const char *text = field->text;
    if (!*text) return false;
    int length = (int)strlen(text);
    if (field->anchor != field->cursor &&
        (selection_start(field) != 0 || selection_end(field) != length)) return false;
    // Let the plain editor scroll past the screen when an expression is long.
    if (casio_width(text, -1, false, false) > width - 3) return false;
    if (!strpbrk(text, "/^") && !strstr(text, "sqrt(")) {
        if (!large) return false;
    }
    // Use the plain editor for command prefixes and values with explicit units.
    if (strpbrk(text, "<>{}[]")) return false;
    for (int i = 1; i + 1 < length; i++)
        if (text[i] == ' ' && isdigit((unsigned char)text[i - 1]) && isalpha((unsigned char)text[i + 1]))
            return false;
    int depth = 0;
    for (const char *at = text; *at; at++) {
        if (*at == '(') depth++;
        if (*at == ')' && --depth < 0) return false;
    }
    if (length + depth + 1 >= EXPRESSION_SIZE) return false;
    memcpy(preview, text, (size_t)length);
    if (text[length - 1] == '^' || text[length - 1] == '/') preview[length++] = '?';
    memset(preview + length, ')', (size_t)depth);
    preview[length + depth] = 0;
    *box = large ? measure_calculation(preview, width - 3) : measure_math(preview, width - 3);
    return true;
}

static int expression_height(const Field *field, int width, int max, bool large) {
    char preview[EXPRESSION_SIZE];
    MathBox box;
    int base = large ? 30 : 18;
    if (!expression_draft(field, preview, width - 8, large, &box)) return base;
    int height = box.above + box.below + 6;
    if (large && height < base) height = base;
    return height + (large ? 2 : 0) > max ? base : height + (large ? 2 : 0);
}

static void expression_entry(int x, int y, int width, int height, const Field *field,
                             const char *placeholder, bool focused, bool large) {
    char preview[EXPRESSION_SIZE];
    MathBox box;
    if (!expression_draft(field, preview, width - 8, large, &box) ||
        box.above + box.below + 4 > height) {
        field_entry(x, y + (height - 18) / 2, width, field, placeholder, focused);
        return;
    }
    rectangle(x, y, width, height, focused ? Gold : Line);
    rectangle(x + 1, y + 1, width - 2, height - 2, White);
    int mid = y + (height - box.above - box.below) / 2 + box.above;
    bool selected = focused && field->anchor != field->cursor;
    eadk_color_t paper = selected ? PaleGold : White;
    if (selected) rectangle(x + 3, mid - box.above - 1, box.width + 2, box.above + box.below + 2, paper);
    MathCanvas canvas = {large ? large_math_text : math_text, rectangle, Ink, paper};
    MathCaret caret = paint_math_input(preview, width - 11, x + 4, mid, &canvas, field->cursor, large);
    if (focused && !selected) rectangle(caret.x, caret.y, 1, caret.height, Blue);
}

static const Course *course(void) { return &courses[course_selection.row]; }
static const Chapter *chapter(void) { return &course()->chapters[chapter_selection.row]; }
static const Topic *topic(void) { return &chapter()->topics[topic_selection.row]; }

#include "search.inc"

static const PhysicsEquation *equation(void) {
    return &(chemistry_sheet ? chemistry_equations : physics_equations)[physics_selection.row];
}

static int science_subject(int row) {
    const PhysicsEquation *item = equation();
    for (int i = 0; i < item->count; i++)
        if (item->variables[i].formula && row-- == 0) return i;
    return 0;
}

static const UnitGroup *selected_unit_group(void) {
    return &unit_groups[unit_group.row];
}

static int physics_slot(int field) {
    return field >= science_subject(physics_subject.row) ? field + 1 : field;
}

static const char *favourite_title(const Favourite *item) {
    if (item->equation)
        return (item->chemistry ? chemistry_equations : physics_equations)[item->row].title;
    return courses[item->course].chapters[item->chapter].topics[item->row].title;
}

static int favourite_index(int row) {
    for (int i = 0; i < favourite_count; i++) {
        const Favourite *item = &favourites[i];
        FavouriteGroup group = item->equation ? (item->chemistry ? ChemistryPins : PhysicsPins) : CoursePins;
        if (group == favourite_group && row-- == 0) return i;
    }
    return -1;
}

static void open_favourites(FavouriteGroup group, Page parent) {
    favourite_group = group;
    favourite_parent = parent;
    favourite_selection = (Selection){0};
    page = Favourites;
}

static Operation cas_menu_operation(int row) {
    int index = row - CasOperationStart;
    return (Operation)(index >= Expand ? index + 1 : index);
}

static const char *selection_text(Page menu, int i) {
    switch (menu) {
        case Toolbox: return i == 0 ? "Favourites" : i == 1 ? "Search topics" : courses[i - 2].title;
        case RelatedEquations: return match_title(&related_matches[i]);
        case GeneralMenu: return general_items[i];
        case SessionList: {
            static char label[SESSION_NAME_SIZE + 3];
            snprintf(label, sizeof(label), "%s%s", session_names[i], i == active_session ? " *" : "");
            return label;
        }
        case EquationFavourites: return i == 0 ? "Physics" : "Chemistry";
        case Chapters: return course()->chapters[i].title;
        case Topics: return chapter()->topics[i].title;
        case TopicMenu: {
            static const char *const actions[] = {"Course notes", "Method and working", "Enter your values", "Worked examples"};
            return actions[i == 2 && !topic()->labels[0] ? 3 : i];
        }
        case Examples:
            return i == 0 ? (topic()->example ? "Original example" : "Calculator example") :
                            topic()->detail->examples[i - 1].title;
        case CasMenu:
            if (i == CasSearch) return "Search equations";
            if (i == CasFavourites) return "Favourites";
            if (i == CasPhysics) return physics_sheet_title;
            if (i == CasChemistry) return chemistry_sheet_title;
            if (i == CasUnits) return "Unit conversions";
            if (i == CasRearrange) return extra_tool_names[PhysicsRearrange];
            if (i == CasTrig) return extra_tool_names[TrigSolver];
            if (i == CasTriangle) return extra_tool_names[TriangleSolver];
            return operation_names[cas_menu_operation(i)];
        case Favourites: return favourite_title(&favourites[favourite_index(i)]);
        case DecimalPlaces: {
            static char number[24];
            snprintf(number,sizeof(number),"%d%s",i,i == 5 ? " (default)" : "");
            return number;
        }
        case UnitGroups: return unit_groups[i].name;
        case UnitFrom: case UnitTo: return selected_unit_group()->units[i].symbol;
        case PhysicsSubjects: {
            static char label[80];
            const PhysicsVariable *variable = &equation()->variables[science_subject(i)];
            snprintf(label, sizeof(label), "%s: %s [%s]", variable->symbol, variable->name, variable->unit);
            return label;
        }
        case History: return history[i].question;
        case Settings: {
            if (i == 0) return degrees ? "Angle unit                    Degrees" : "Angle unit                    Radians";
            if (i == 1) return decimal ? "Numeric answers               Decimal" : "Numeric answers              Fractions";
            if (i == 2) return show_steps ? "Worked steps                      On" : "Worked steps                     Off";
            if (i == 3) return "CAS help";
            static char label[43];
            snprintf(label,sizeof(label),"Decimal places                     %d",decimal_places);
            return label;
        }
        default: return "";
    }
}

static int count_for(Page menu) {
    switch (menu) {
        case Toolbox: return course_count + 2;
        case RelatedEquations: return related_count;
        case Chapters: return course()->count;
        case Topics: return chapter()->count;
        case TopicMenu: return topic()->labels[0] ? 4 : 3;
        case Examples: return 1 + EXTRA_EXAMPLES;
        case CasMenu: return CasCount;
        case GeneralMenu: return GeneralCount;
        case EquationFavourites: return 2;
        case SessionList: return session_count;
        case Favourites: {
            int count = 0;
            while (favourite_index(count) >= 0) count++;
            return count;
        }
        case DecimalPlaces: return 11;
        case PhysicsList: return 2 + (chemistry_sheet ? chemistry_equation_count : physics_equation_count);
        case PhysicsSubjects: {
            const PhysicsEquation *item = equation();
            int count = 0;
            for (int i = 0; i < item->count; i++) count += item->variables[i].formula != NULL;
            return count;
        }
        case UnitGroups: return unit_group_count;
        case UnitFrom: case UnitTo: return selected_unit_group()->count;
        case History: return history_count;
        case Settings: return 5;
        default: return 0;
    }
}

static Selection *selection_for(Page menu) {
    switch (menu) {
        case Toolbox: return &course_list_selection;
        case RelatedEquations: return &related_selection;
        case GeneralMenu: return &general_selection;
        case SessionList: return &session_selection;
        case EquationFavourites: return &equation_favourite_selection;
        case Chapters: return &chapter_selection;
        case Topics: return &topic_selection;
        case TopicMenu: return &topic_action;
        case Examples: return &example_selection;
        case CasMenu: return &cas_selection;
        case PhysicsList: return &physics_list_selection;
        case PhysicsSubjects: return &physics_subject;
        case UnitGroups: return &unit_group;
        case UnitFrom: return &unit_from;
        case UnitTo: return &unit_to;
        case Favourites: return &favourite_selection;
        case DecimalPlaces: return &decimal_selection;
        case History: return &history_selection;
        case Settings: return &settings_selection;
        default: return NULL;
    }
}

static void draw_list(const char *title, const char *tag, bool filled) {
    const int y0 = 25, row_height = 20;
    const int rows = (FOOTER - y0) / row_height;
    Selection *s = selection_for(page);
    int count = count_for(page);
    header(title, tag, filled);
    if (s->row < s->first) s->first = s->row;
    if (s->row >= s->first + rows) s->first = s->row - rows + 1;
    for (int row = 0; row < rows && s->first + row < count; row++) {
        int i = s->first + row, y = y0 + row * row_height;
        bool active = s->row == i;
        eadk_color_t paper = active ? PaleGold : White;
        if (active) {
            rectangle(4, y, EADK_SCREEN_WIDTH - 9, row_height - 1, paper);
            string_at(8, y + 3, ">", Blue, paper);
        } else if (page == Toolbox) {
            static const eadk_color_t stripes[] = {Blue, 0x5ca9, 0x9275, 0xc369, 0x46b1, 0x6b96};
            rectangle(4, y + 1, 3, 18, stripes[i % (sizeof(stripes) / sizeof(*stripes))]);
        }
        const char *label = selection_text(page, i);
        const char *setting_value = page == Settings ? strstr(label, "  ") : NULL;
        if (setting_value) {
            char setting_name[TEXT_WIDTH + 1];
            snprintf(setting_name, sizeof(setting_name), "%.*s", (int)(setting_value-label), label);
            while (*setting_value == ' ') setting_value++;
            string_at(21, y+3, setting_name, active ? Blue : Ink, paper);
            string_at(EADK_SCREEN_WIDTH-14-casio_width(setting_value,-1,false,false),
                      y+3, setting_value, active ? Blue : Ink, paper);
        } else title_with_tier(21, y + 3, label, TEXT_WIDTH, active ? Blue : Ink, paper);
    }
    if (page == SessionList)
        string_at(8, 186, session_store.records ? "Auto-saves to Casio USB storage." :
                  "Sessions last until NumAI closes.", Grey, White);
    if (!count) string_at(8, 36, page == Favourites ?
                          "No favourites yet. Pin with Shift+TOOLS." : "No saved calculations yet.", Grey, White);
    scrollbar(s->first, count, rows, y0, row_height * rows);
    footer(page == Settings ? "OK: change   BACK: return" :
           page == Favourites ? "OK: open   SHIFT+TOOLS: unpin   BACK" :
           page == Topics || page == TopicMenu ? "OK: open   SHIFT+TOOLS: pin   BACK" :
           "OK: choose   UP/DOWN: move   BACK");
}

static const struct { const char *key; const char *function; } shortcuts[] = {
    {"CATALOG", "Browse courses and topics"},
    {"TOOLS", "Open Equations and CAS"},
    {"SHIFT+EXE", "Open or close NumAI menu"},
    {"OK / EXE", "Open item or calculate"},
    {"UP / DOWN", "Move, scroll or change field"},
    {"BACK / HOME", "Go back / return to launcher"},
    {"x/\030/T", "Enter x; ALPHA enters A"},
    {"SHIFT+(", "Enter ="},
    {"ALPHA", "Enter one printed red letter"},
    {"SHIFT+ALPHA", "Lock letters; ALPHA unlocks"},
    {"VARIABLE", "Variables, symbols, letter case"},
    {"VARIABLE, RIGHT", "Symbols: !, =, >, <, _ and more"},
    {"SHIFT+0", "Start selecting text"},
    {"LEFT / RIGHT", "Move cursor or selection end"},
    {"OK (selection)", "Choose Copy or Cut"},
    {"SHIFT+.", "Paste NumAI clipboard"},
    {"SHIFT+TOOLS", "Copy result or toggle favourite"},
    {"AC", "Clear the current input"},
    {"SHIFT+DEL", "Toggle insert / overwrite"},
    {"SHIFT+x/\030/T", "Enter -> to store a value"},
    {"SHIFT+sin", "Enter asin("},
    {"SHIFT+cos", "Enter acos("},
    {"SHIFT+tan", "Enter atan("},
    {"SHIFT+7", "Enter pi"},
    {"SHIFT+\031", "Enter cube root"},
    {"SHIFT+x\032", "Enter log("},
    {"SHIFT+e^", "Enter ln("},
    {"FORMAT", "Show answer formats / extras"},
#if NUMAI_FXCG100
    {"ALPHA+FORMAT", "Insert Ans (fx-CG100)"},
    {"SHIFT+ALPHA+FORMAT", "Calculation home"},
#else
    {"SHIFT+FORMAT", "Insert Ans (Graph Math+)"},
    {"ALPHA+FORMAT", "Calculation home"},
#endif
    {"SETTINGS", "Open Preferences"},
    {"Tab LEFT/RIGHT", "Previous / next field or view"},
    {"PAGE UP/DOWN", "Scroll one page"},
    {">*", "Factorise"},
    {">/", "Simplify"},
    {"=>", "Solve for x"},
    {">**", "Complete the square"}
};

enum { SHORTCUT_ROWS = 8, SHORTCUT_COUNT = sizeof(shortcuts) / sizeof(*shortcuts) };

static void draw_shortcuts(void) {
    const int table_x = 6, function_x = 142, top = 25, head_height = 20, row_height = 20;
    header("Keyboard shortcuts", NULL, false);
    rectangle(table_x, top, EADK_SCREEN_WIDTH - 12, head_height, Light);
    draw_text(10, top + 3, "Key bind", Blue, Light, true);
    draw_text(function_x + 4, top + 3, "Function", Blue, Light, true);
    for (int row = 0; row < SHORTCUT_ROWS; row++) {
        int y = top + head_height + row * row_height;
        int i = shortcuts_offset + row;
        const eadk_color_t paper = row % 2 ? Light : White;
        rectangle(table_x, y, EADK_SCREEN_WIDTH - 12, row_height, paper);
        draw_text(10, y + 4, shortcuts[i].key, Ink, paper, true);
        string_at(function_x + 4, y + 4, shortcuts[i].function, Ink, paper);
        rectangle(table_x, y + row_height - 1, EADK_SCREEN_WIDTH - 12, 1, Line);
    }
    rectangle(function_x, top, 1, head_height + SHORTCUT_ROWS * row_height, Line);
    scrollbar(shortcuts_offset, SHORTCUT_COUNT, SHORTCUT_ROWS,
              top + head_height, SHORTCUT_ROWS * row_height);
    footer("UP/DOWN: scroll    BACK: menu");
}

static void equation_title(const PhysicsEquation *item, char *title, size_t size) {
    snprintf(title, size, "%s%s", item->title, item->higher ? " (higher only)" : "");
}

static void display_wrapped_line(const WrappedLine *line, int x, int y, eadk_color_t color, eadk_color_t paper) {
    char body[TEXT_WIDTH + 1];
    snprintf(body, sizeof(body), "%.*s", line->length, line->source);
    string_at(x, y, body, color, paper);
}

static void draw_physics_list(void) {
    const int height = 78, favourite_height = 24, top = 25;
    Selection *sel = &physics_list_selection;
    int count = count_for(PhysicsList);
    header(chemistry_sheet ? chemistry_sheet_title : physics_sheet_title, chemistry_sheet ? "8462" : "8463", false);
    if (sel->row < sel->first) sel->first = sel->row;
    if (sel->row > sel->first + (sel->first == 0 ? 2 : 1)) sel->first = sel->row - 1;
    int shown = 0;
    for (int row = sel->first, y = top; row < count; row++) {
        int row_height = row == 0 ? favourite_height : height;
        if (y + row_height > FOOTER) break;
        bool active = row == sel->row;
        eadk_color_t paper = active ? PaleGold : White;
        if (active) {
            rectangle(4, y, EADK_SCREEN_WIDTH - 9, row_height - 1, paper);
            string_at(8, y + 2, ">", Blue, paper);
        }
        if (row == 0) {
            string_at(21, y + 2, "Favourite Equations", active ? Blue : Ink, paper);
        } else if (row == count - 1) {
            string_at(21, y + 2, "Search equations", active ? Blue : Ink, paper);
        } else {
            const PhysicsEquation *item = &(chemistry_sheet ? chemistry_equations : physics_equations)[row - 1];
            char title[80];
            equation_title(item, title, sizeof(title));
            title_with_tier(21, y + 2, title, TEXT_WIDTH, active ? Blue : Ink, paper);
            char words[SCIENCE_WORD_SIZE];
            physics_word_equation(item, words);
            int line_count = 0;
            wrap(words, TEXT_WIDTH, false, &line_count);
            for (int i = 0; i < line_count && i < 4; i++) {
                if (i == 3 && line_count > 4) string_at(21, y + 18 + i*14, "...  OK for full equation", Grey, paper);
                else display_wrapped_line(&wrapped[i], 21, y + 18 + i*14, Grey, paper);
            }
        }
        y += row_height;
        shown++;
    }
    scrollbar(sel->first, count, shown, top, FOOTER - top);
    footer("TOOLS: search   SHIFT+TOOLS: favourite");
}

static void draw_physics_detail(void) {
    const PhysicsEquation *item = equation();
    char title[80], topic_label[TEXT_WIDTH + 1];
    equation_title(item, title, sizeof(title));
    header(title, NULL, false);
    snprintf(topic_label, sizeof(topic_label), "Topic: %s", item->topic);
    string_at(8, 25, topic_label, Ink, White);
    snprintf(topic_label, sizeof(topic_label), "CATALOG: open topic %s", item->section);
    string_at(8, 40, topic_label, Grey, White);
    read_length = 0;
    read_offset = physics_offset;
    wrap(physics_notes, TEXT_WIDTH, false, &read_length);
    reader(56, FOOTER - 25);
    physics_offset = read_offset;
    rectangle(6, FOOTER - 24, EADK_SCREEN_WIDTH - 12, 22, PaleGold);
    string_at(12, FOOTER - 20, "Solver", Blue, PaleGold);
    string_at(EADK_SCREEN_WIDTH - 78, FOOTER - 20, "OK / EXE", Blue, PaleGold);
    footer("UP/DOWN: read   SHIFT+TOOLS: pin   BACK");
}

static void draw_physics_form(void) {
    const PhysicsEquation *item = equation();
    int subject_index = science_subject(physics_subject.row);
    const PhysicsVariable *subject = &item->variables[subject_index];
    header(chemistry_sheet ? "Chemistry solver" : "Physics solver", subject->symbol, false);
    char caption[112];
    snprintf(caption, sizeof(caption), "Find %s [%s]", subject->name, subject->unit);
    clipped(8, 25, caption, TEXT_WIDTH, Blue, White);
    physics_subject_equation(item, subject_index, caption, sizeof(caption));
    MathBox formula = revision_line(caption, 0, 0, Ink, White, false);
    revision_line(caption, 8, 40 + formula.above, Ink, White, true);
    int first_y = 44 + formula.above + formula.below;
    int fields = item->count - 1, heights[SCIENCE_VARIABLES], labels[SCIENCE_VARIABLES];
    for (int i = 0; i < fields; i++) {
        const PhysicsVariable *v = &item->variables[physics_slot(i)];
        snprintf(caption, sizeof(caption), "%s: %s [%s]", v->symbol, v->name, v->unit);
        MathBox label = revision_line(caption, 0, 0, Grey, White, false);
        labels[i] = label.above + label.below;
        heights[i] = expression_height(&physics_fields[physics_slot(i)], EADK_SCREEN_WIDTH - 14, 50, false);
    }
    if (physics_focus < physics_first) physics_first = physics_focus;
    int required = 0;
    int bottom = *science_work.answer ? FOOTER - 28 : FOOTER - 3;
    for (int i = physics_focus; i >= physics_first; i--) {
        required += heights[i] + labels[i] + 6;
        if (required > bottom - first_y && i < physics_focus) {
            physics_first = i + 1;
            break;
        }
    }
    int y = first_y, shown = 0;
    for (int i = physics_first; i < fields && y + heights[i] + labels[i] + 6 <= bottom; i++) {
        const PhysicsVariable *v = &item->variables[physics_slot(i)];
        bool focused = i == physics_focus;
        snprintf(caption, sizeof(caption), "%s: %s [%s]", v->symbol, v->name, v->unit);
        MathBox label = revision_line(caption, 0, 0, Grey, White, false);
        revision_line(caption, 8, y + label.above, focused ? Blue : Grey, White, true);
        const char *hint = v->flags & ScienceOptional ? "Optional (0 if blank)" :
                           focused ? "Value or value + unit" : NULL;
        expression_entry(7, y + labels[i], EADK_SCREEN_WIDTH - 14, heights[i], &physics_fields[physics_slot(i)],
                         hint, focused, false);
        y += heights[i] + labels[i] + 6;
        shown++;
    }
    if (shown) scrollbar(physics_first, fields, shown, first_y, bottom - first_y);
    if (*science_work.answer)
        clipped(8, FOOTER - 23, science_work.answer, TEXT_WIDTH, Ink, PaleGold);
    footer("UP/DOWN: field   EXE: solve   BACK");
}

static void draw_science_result(void) {
    header(chemistry_sheet ? "Chemistry working" : "Physics working", NULL, false);
    char formula[112], substitution[SCIENCE_SUBSTITUTION_SIZE + 13];
    physics_subject_equation(equation(), science_subject(physics_subject.row), formula, sizeof(formula));
    snprintf(substitution, sizeof(substitution), "Substitute: %s", science_work.substituted);
    read_length = 0;
    read_offset = science_result_offset;
    wrap(science_work.answer, TEXT_WIDTH, physics_answer_ok, &read_length);
    wrap(formula, TEXT_WIDTH, false, &read_length);
    if (*science_work.substituted) wrap(substitution, TEXT_WIDTH, false, &read_length);
    if (*science_work.conversions) {
        wrap("\nUnit conversions", TEXT_WIDTH, false, &read_length);
        wrap(science_work.conversions, TEXT_WIDTH, false, &read_length);
    }
    if (*science_work.steps) {
        wrap("\nWorking", TEXT_WIDTH, false, &read_length);
        wrap(science_work.steps, TEXT_WIDTH, false, &read_length);
    }
    reader(27, FOOTER - 3);
    science_result_offset = read_offset;
    footer("UP/DOWN: scroll   BACK: inputs");
}

static void draw_unit_conversion(void) {
    const Unit *units = selected_unit_group()->units;
    char title[60];
    snprintf(title, sizeof(title), "%s to %s", units[unit_from.row].symbol, units[unit_to.row].symbol);
    header("Unit conversions", NULL, true);
    clipped(8, 30, selected_unit_group()->name, TEXT_WIDTH, Ink, White);
    clipped(8, 48, title, TEXT_WIDTH, Blue, White);
    if (page == UnitValue) {
        int height = expression_height(&unit_input, EADK_SCREEN_WIDTH - 14, 66, false);
        expression_entry(7, 74, EADK_SCREEN_WIDTH - 14, height, &unit_input, "Enter a number or expression", true, false);
        if (unit_input_error) string_at(8, 80 + height, "Check the value or its size.", Ink, White);
        footer("EXE: convert   BACK: change unit");
        return;
    }
    read_offset = 0;
    read_length = 0;
    wrap(unit_expression, TEXT_WIDTH, false, &read_length);
    wrap(unit_work, TEXT_WIDTH, false, &read_length);
    char answer[60];
    snprintf(answer, sizeof(answer), "%s %s", unit_number, units[unit_to.row].symbol);
    wrap(answer, TEXT_WIDTH, true, &read_length);
    reader(72, FOOTER - 29);
    if (unit_copied) string_at(8, FOOTER - 22, "Number copied to NumAI clipboard", Blue, White);
    footer("SHIFT+TOOLS: copy number   BACK");
}

static void draw_tool(void) {
    header(extra_tool_names[extra_tool],NULL,false);
    if (page == ToolOutput) {
        read_length = 0;
        read_offset = tool_offset;
        if (show_steps) wrap(tool_solution.steps,TEXT_WIDTH,false,&read_length);
        wrap(tool_solution.answer,TEXT_WIDTH,tool_solution.ok,&read_length);
        reader(27, FOOTER - 3);
        tool_offset = read_offset;
        footer("UP/DOWN: read   BACK: inputs");
        return;
    }
    const char *hint = extra_tool == TriangleSolver ? "Leave unknown sides or angles blank." :
                       extra_tool == TrigSolver ? "Use sin, cos or tan. Set both bounds." :
                       "Use [name] for multi-letter symbols.";
    string_at(8,26,hint,Grey,White);
    const int top = 48;
    int heights[6];
    for (int i = 0; i < field_count; i++) heights[i] = expression_height(&forms[i], EADK_SCREEN_WIDTH - 14, 64, false);
    if (active_field < tool_first) tool_first = active_field;
    int needed = 0;
    for (int i = active_field; i >= tool_first; i--) {
        needed += heights[i] + 21;
        if (needed > FOOTER - top) {
            tool_first = i + 1;
            break;
        }
    }
    int y = top, shown = 0;
    for (int i = tool_first; i < field_count && y + heights[i] + 17 < FOOTER; i++) {
        char angle_label[20];
        const char *label = form_labels[i];
        if (extra_tool == TriangleSolver && i >= 3) {
            snprintf(angle_label,sizeof(angle_label),"Angle %c [%s]",'A'+i-3,degrees?"deg":"rad");
            label = angle_label;
        }
        string_at(8,y,label,i == active_field ? Blue : Grey,White);
        expression_entry(7,y+15,EADK_SCREEN_WIDTH - 14,heights[i],&forms[i],NULL,i == active_field,false);
        y += heights[i] + 21;
        shown++;
    }
    scrollbar(tool_first,field_count,shown,top,FOOTER - top);
    footer("UP/DOWN: field   EXE: solve   BACK");
}

#include "calculator_view.inc"

static void draw(void) {
    eadk_display_push_rect_uniform(eadk_screen_rect, White);
    switch (page) {
        case Prompt:
        case CalcHistory: case CalcExtras:
            draw_calculator();
            if (page == CalcExtras) draw_calc_extras();
            break;
        case Toolbox: draw_list("Courses", NULL, true); break;
        case Chapters: draw_list(course()->title, course()->code, false); break;
        case Topics: draw_list(chapter()->title, NULL, false); break;
        case TopicMenu: draw_list(topic()->title, NULL, false); break;
        case Examples: draw_list("Worked examples", NULL, false); break;
        case PhysicsList: draw_physics_list(); break;
        case PhysicsDetail: draw_physics_detail(); break;
        case PhysicsSubjects: draw_list("Choose the unknown", NULL, false); break;
        case PhysicsForm: draw_physics_form(); break;
        case ScienceResult: draw_science_result(); break;
        case UnitGroups: draw_list("Unit conversions", NULL, true); break;
        case UnitFrom: draw_list("Convert from", NULL, false); break;
        case UnitTo: draw_list("Convert to", NULL, false); break;
        case UnitValue: case UnitResult: draw_unit_conversion(); break;
        case CasMenu: draw_list("Equations and CAS", NULL, true); break;
        case GeneralMenu: draw_list("NumAI menu", NULL, true); break;
        case EquationFavourites: draw_list("Equation favourites", NULL, false); break;
        case SessionList: draw_list("Open session", NULL, false); break;
        case SessionName:
            header("New session", NULL, false);
            string_at(8, 30, "Enter a name (letters, digits or _).", Grey, White);
            field_entry(7, 50, EADK_SCREEN_WIDTH - 14, &session_name, "Session name", true);
            const char *storage_hint = session_store.records ? "Stored in numai.sav on the USB drive." :
                                       "Sessions last until NumAI closes.";
            string_at(8, 82, session_error ? session_error : storage_hint, Grey, White);
            footer("ALPHA: letters   EXE: create   BACK");
            break;
        case About:
            header("About", NULL, false);
            string_at(8, 31, "NumAI " NUMAI_VERSION, Ink, White);
            string_at(8, 51, "Revision and calculation for Graph Math+", Grey, White);
            footer("BACK: menu");
            break;
        case Search: draw_search(); break;
        case RelatedEquations: draw_list("Related equations", NULL, false); break;
        case History: draw_list("History", NULL, false); break;
        case HistoryResult: {
            const HistoryEntry *item = &history[history_selection.row];
            header(*item->title ? item->title : operation_names[item->operation], NULL, false);
            read_length = 0;
            read_offset = history_offset;
            wrap(item->question, TEXT_WIDTH, false, &read_length);
            if (show_steps) wrap(item->solution.steps, TEXT_WIDTH, false, &read_length);
            wrap(item->solution.answer, TEXT_WIDTH, true, &read_length);
            reader(27, FOOTER - 3);
            history_offset = read_offset;
            footer(item->reuse.kind != ReuseNone ? "OK: reuse inputs   UP/DOWN: read   BACK" :
                   "UP/DOWN: scroll   BACK: history");
            break;
        }
        case Settings: draw_list("Preferences", NULL, false); break;
        case Favourites:
            draw_list(favourite_group == CoursePins ? "Favourites" :
                      favourite_group == PhysicsPins ? "Physics favourites" : "Chemistry favourites", NULL, false);
            break;
        case DecimalPlaces: draw_list("Decimal places",NULL,false); break;
        case ToolForm: case ToolOutput: draw_tool(); break;
        case Shortcuts: draw_shortcuts(); break;
        case Form:
            header(form_topic ? form_topic->title : operation_names[form_operation], NULL, false);
            int y = 27, heights[6], shown = 0;
            for (int i = 0; i < field_count; i++) heights[i] = expression_height(&forms[i], EADK_SCREEN_WIDTH - 14, 58, false);
            if (active_field < form_first) form_first = active_field;
            int required = 0;
            for (int i = active_field; i >= form_first; i--) {
                required += heights[i] + 20;
                if (required > FOOTER - 27) { form_first = i + 1; break; }
            }
            for (int i = form_first; i < field_count && y + heights[i] + 17 < FOOTER; i++) {
                string_at(8, y, form_labels[i], i == active_field ? Blue : Grey, White);
                expression_entry(7, y + 15, EADK_SCREEN_WIDTH - 14, heights[i], &forms[i], NULL, i == active_field, false);
                y += heights[i] + 20;
                shown++;
            }
            scrollbar(form_first, field_count, shown, 27, FOOTER - 27);
            if (y + 19 < FOOTER) string_at(8, y + 3, "Enter your values, then press EXE.", Grey, White);
            footer("UP/DOWN: field    EXE: work it out");
            break;
        case Reading:
            header(read_title, NULL, false);
            read_length = 0;
            wrap_topic_reading();
            reader(30, FOOTER - 3);
            footer(reading_is_topic() && related_count ? "TOOLS: related equations   UP/DOWN   BACK" :
                   "UP/DOWN: scroll    BACK: return");
            break;
        case Result:
            header(operation_names[result_operation], NULL, false);
            read_length = 0;
            wrap(result_question, TEXT_WIDTH, false, &read_length);
            if (show_steps && solution.steps[0]) wrap(solution.steps, TEXT_WIDTH, false, &read_length);
            wrap(solution.answer, TEXT_WIDTH, true, &read_length);
            reader(27, FOOTER - 29);
            expression_entry(4, FOOTER - 24, EADK_SCREEN_WIDTH - 8, 20, &prompt, "Type a question, or press CATALOG", true, false);
            footer("UP/DOWN: read   CATALOG   TOOLS   EXE");
            break;
    }
    if (native_menu) {
        rectangle(0, 0, EADK_SCREEN_WIDTH, EADK_SCREEN_HEIGHT, White);
        header(native_menu == 1 ? "Clipboard" : "Variables and symbols", NULL, true);
        int first = native_row > 6 ? native_row-6 : 0;
        CasVariables variables; cas_get_variables(&variables);
        for (int row = first; row < native_count() && row < first+8; row++) {
            char label[100];
            if (native_menu == 1) snprintf(label, sizeof(label), "%s", row ? "Cut" : "Copy");
            else if (!row) snprintf(label, sizeof(label), "Letter case: %s (OK to change)", lowercase_letters ? "abc" : "ABC");
            else if (row <= 26) {
                int index = (lowercase_letters ? 0 : 26) + row-1;
                if (variables.set[index]) snprintf(label, sizeof(label), "%c = %.10g", (lowercase_letters ? 'a' : 'A')+row-1, variables.value[index]);
                else snprintf(label, sizeof(label), "%c", (lowercase_letters ? 'a' : 'A')+row-1);
            } else snprintf(label, sizeof(label), "%s", symbol_inputs[row-27]);
            int y = 28 + (row-first)*21;
            rectangle(5,y-2,EADK_SCREEN_WIDTH-10,21,row == native_row ? Light : White);
            string_at(10,y,label,Ink,row == native_row ? Light : White);
        }
        footer(native_menu == 2 ? "LEFT: letters  RIGHT: symbols  OK: insert" : "UP/DOWN: choose   OK: select   BACK");
    }
}

static void set_field(Field *field, const char *value, bool selected) {
    snprintf(field->text, sizeof(field->text), "%s", value ? value : "");
    field->cursor = (int)strlen(field->text);
    field->anchor = selected ? 0 : field->cursor;
}

static void replace_range(Field *field, int from, int to, const char *text) {
    size_t length = strlen(text), tail = strlen(field->text + to);
    if ((size_t)from + length + tail >= sizeof(field->text)) return;
    memmove(field->text + from + length, field->text + to, tail + 1);
    memcpy(field->text + from, text, length);
    field->cursor = field->anchor = from + (int)length;
}

static void insert(Field *field, const char *text) {
    replace_range(field, selection_start(field), selection_end(field), text);
}

static void finish_parentheses(Field *field) {
    int depth = 0;
    char *end = field->text;
    for (; *end; end++) {
        if (*end == '(') depth++;
        if (*end == ')' && --depth < 0) return;
    }
    if (!depth || depth > 18) return;
    char *at = end;
    // Keep a closing command brace at the end of the prompt.
    while (at > field->text && isspace((unsigned char)at[-1])) at--;
    if (at > field->text && at[-1] == '}') at--;
    if (end - field->text + depth >= (int)sizeof(field->text)) return;
    memmove(at + depth, at, (size_t)(end - at) + 1);
    memset(at, ')', (size_t)depth);
    field->cursor = field->anchor = (int)strlen(field->text);
}

static const char *skip_spaces(const char *text) {
    while (isspace((unsigned char)*text)) text++;
    return text;
}

static Operation prompt_operation(const char *text, char operand[EXPRESSION_SIZE]) {
    static const struct { const char *prefix; Operation operation; } commands[] = {
        {">**", CompleteSquare}, {">*", Factorise}, {">/", Simplify}, {"=>", Solve}
    };
    text = skip_spaces(text);
    for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
        size_t prefix = strlen(commands[i].prefix);
        if (strncmp(text, commands[i].prefix, prefix)) continue;
        const char *first = skip_spaces(text + prefix), *end = first + strlen(first);
        while (end > first && isspace((unsigned char)end[-1])) end--;
        if (end - first >= 2 && *first == '{' && end[-1] == '}') {
            first++;
            end--;
        }
        snprintf(operand, EXPRESSION_SIZE, "%.*s", (int)(end - first), first);
        return commands[i].operation;
    }
    snprintf(operand, EXPRESSION_SIZE, "%s", text);
    return strchr(text, '=') && !strpbrk(text, "<>") ? Solve : Calculate;
}

static void form_for(Operation operation, const Topic *item, Page parent) {
    static const char *const defaults[] = {
        "2/3+1/6", "x^2-5x+6", "3x+2(x-1)", "(x+1)(x-3)", "x^2-5x+6=0",
        "x^3-4x+2", "3x^2-4", "x^2+1", "x^2+1", "cos(x)=x", "2x^2+12x+11"
    };
    form_parent = parent;
    form_operation = operation;
    form_topic = item;
    active_field = form_first = 0;
    field_count = 0;
    if (item) {
        while (field_count < MAX_FIELDS && item->labels[field_count]) {
            form_labels[field_count] = item->labels[field_count];
            set_field(&forms[field_count], item->values[field_count], true);
            field_count++;
        }
    } else {
        form_labels[0] = (operation == Solve || operation == FindRoot) ? "Equation in x" : "Expression in x";
        if (operation == Calculate) form_labels[0] = "Expression";
        if (operation == CompleteSquare) form_labels[0] = "Quadratic in x";
        if (operation == Integrate || operation == Definite) form_labels[0] = "Integrand f(x)";
        char operand[EXPRESSION_SIZE];
        prompt_operation(prompt.text, operand);
        set_field(&forms[0], *operand ? operand : defaults[operation], !*operand);
        field_count = (operation == Definite || operation == FindRoot) ? 3 : operation == Substitute ? 2 : 1;
        if (operation == Definite) {
            form_labels[1] = "Lower limit";
            form_labels[2] = "Upper limit";
            set_field(&forms[1], "0", true);
            set_field(&forms[2], "2", true);
        }
        if (operation == FindRoot) {
            form_labels[1] = "Lower bound";
            form_labels[2] = "Upper bound";
            set_field(&forms[1], "0", true);
            set_field(&forms[2], "1", true);
        }
        if (operation == Substitute) {
            form_labels[1] = "Value of x";
            set_field(&forms[1], "2", true);
        }
    }
    page = Form;
}

static void record(HistoryEntry *entries, int *count, int limit, const char *question,
                   Operation operation, const char *title, const Solution *answer) {
    if (*count < limit) (*count)++;
    for (int i = *count - 1; i > 0; i--) entries[i] = entries[i - 1];
    snprintf(entries[0].question, sizeof(entries[0].question), "%s", question);
    entries[0].reuse = (ReuseData){0};
    entries[0].operation = operation;
    snprintf(entries[0].title, sizeof(entries[0].title), "%s", title ? title : "");
    entries[0].solution = *answer;
}

static void record_form_inputs(void) {
    char inputs[200];
    size_t used = 0;
    for (int i = 0; i < field_count && used < sizeof(inputs) - 1; i++) {
        if (!*forms[i].text) continue;
        int added = snprintf(inputs + used, sizeof(inputs) - used, "%s: %s\n",
                             form_labels[i], forms[i].text);
        if (added < 0 || (size_t)added >= sizeof(inputs) - used) break;
        used += (size_t)added;
    }
    if (!used) return;
    Solution *saved = &history[0].solution;
    size_t length = strlen(saved->steps);
    if (length >= sizeof(saved->steps) - used) length = sizeof(saved->steps) - used - 1;
    memmove(saved->steps + used, saved->steps, length);
    memcpy(saved->steps, inputs, used);
    saved->steps[used + length] = 0;
}

#include "reuse.inc"

static void update_ans(char *dest, const Solution *answer) {
    if (!answer->ok) return;
    const char *str = answer->answer;
    if (strncmp(str, "approx. ", 8) == 0) str += 8;
    if (strspn(str, "-+0123456789.e/") == strlen(str) && strlen(str) < EXPRESSION_SIZE)
        strcpy(dest, str);
}

static bool build_formula(char output[EXPRESSION_SIZE * 4], const char *formula) {
    size_t written = 0, limit = EXPRESSION_SIZE * 4;
    for (; *formula; formula++) {
        if (*formula != '$') {
            if (written + 1 >= limit) return false;
            output[written++] = *formula;
            continue;
        }
        int field = *++formula - '1';
        if (field < 0 || field >= field_count || !forms[field].text[0]) return false;
        size_t size = strlen(forms[field].text);
        if (written + 2 + size >= limit) return false;
        output[written++] = '(';
        memcpy(output + written, forms[field].text, size);
        written += size;
        output[written++] = ')';
    }
    output[written] = 0;
    return true;
}

static void show_result(const char *question, Operation operation, Page parent, bool save) {
    result_operation = operation;
    snprintf(result_question, sizeof(result_question), "%s", question);
    if (save) {
        record(history, &history_count, HISTORY_LIMIT, result_question, operation, NULL, &solution);
        if (operation == Calculate || operation == Definite || operation == Substitute)
            update_ans(ans, &solution);
        if (parent == Form) capture_form_reuse(form_topic ? ReuseTopic : ReuseCas, operation);
        else if (parent == Prompt) {
            history[0].reuse = (ReuseData){.kind=ReuseCas,.id=operation,.count=1,.degrees=degrees};
            char operand[EXPRESSION_SIZE];
            prompt_operation(question, operand);
            snprintf(history[0].reuse.inputs[0], EXPRESSION_SIZE, "%s", operand);
        }
        if (parent == Form && field_count > 1) record_form_inputs();
        session_autosave();
    }
    has_result = true;
    read_offset = 0;
    read_length = 0;
    result_parent = parent;
    page = Result;
}

static void submit_form(bool example) {
    for (int i = 0; i < field_count; i++) finish_parentheses(&forms[i]);
    char generated[EXPRESSION_SIZE * 4];
    const char *input = forms[0].text;
    bool formula = form_topic && form_topic->formula;
    if (formula && !build_formula(generated, form_topic->formula)) {
        solution = (Solution){0};
        strcpy(solution.answer, "Enter a value in each field and keep expressions short.");
    } else {
        if (formula) input = generated;
        bool input_degrees = degrees;
        for (int i = 0; i < field_count; i++) {
            if (strstr(form_labels[i], "(degrees)")) input_degrees = true;
            if (strstr(form_labels[i], "(radians)")) input_degrees = false;
        }
        solve_expression(form_operation, input, forms[1].text, forms[2].text,
                         input_degrees, decimal, &solution);
        if (formula && solution.ok)
            snprintf(solution.steps, sizeof(solution.steps), "%s\nSubstitute: %.300s", form_topic->method, input);
    }
    show_result(formula ? form_topic->title : input, form_operation, example ? Examples : Form, !example);
}

static void submit_prompt(void) {
    finish_parentheses(&prompt);
    const char *text = prompt.text;
    if (!*text) return;
    char operand[EXPRESSION_SIZE];
    Operation operation = prompt_operation(text, operand);
    CalculationValue value;
    if (operation == Calculate && cas_calculation(operand,degrees,&value)) {
        if (calc_count<CALCULATION_LIMIT) calc_count++;
        memmove(calculations+1,calculations,(size_t)(calc_count-1)*sizeof(*calculations));
        snprintf(calculations[0].input,sizeof(calculations[0].input),"%s",operand);
        calculations[0].result=value;
        if (*value.exact) snprintf(ans,sizeof(ans),"%s",value.exact);
        else snprintf(ans,sizeof(ans),"%.17g",value.value);
        session_autosave();
        calc_first=0;
        set_field(&prompt,"",false);
        page=Prompt;
        return;
    }
    solve_expression(operation, operand, "", "", degrees, decimal, &solution);
    show_result(text, operation, Prompt, true);
    if (solution.ok) set_field(&prompt, "", false);
}

static void begin_read(const char *title, const char *content) {
    reading_parent = page;
    read_title = title;
    read_content = content;
    read_offset = 0;
    read_length = 0;
    page = Reading;
}

static void open_equation(void) {
    physics_offset = 0;
    physics_subject = (Selection){0};
    for (int i = 0; i < equation()->count; i++) set_field(&physics_fields[i],"",false);
    physics_reference(equation(),physics_notes);
    page = PhysicsDetail;
}

static bool pin_current(void) {
    Favourite item = {0};
    if (page == Favourites) {
        int index = favourite_index(favourite_selection.row);
        if (index < 0) return true;
        item = favourites[index];
    } else if (page == PhysicsDetail || page == PhysicsList) {
        if (page == PhysicsList && (!physics_list_selection.row ||
            physics_list_selection.row == count_for(PhysicsList) - 1)) return true;
        int row = page == PhysicsDetail ? physics_selection.row : physics_list_selection.row - 1;
        item = (Favourite){.row=row,.equation=true,.chemistry=chemistry_sheet};
    } else if (page == Topics || page == TopicMenu ||
               (page == Reading && (reading_parent == Topics || reading_parent == Favourites ||
                                     reading_parent == TopicMenu || reading_parent == PhysicsDetail))) {
        item = (Favourite){course_selection.row,chapter_selection.row,topic_selection.row,false,false};
    } else return false;
    for (int i = 0; i < favourite_count; i++) {
        Favourite *saved = &favourites[i];
        if (saved->row != item.row || saved->equation != item.equation ||
            (item.equation ? saved->chemistry != item.chemistry :
             saved->course != item.course || saved->chapter != item.chapter)) continue;
        memmove(saved,saved+1,(size_t)(--favourite_count-i)*sizeof(*saved));
        if (page == Favourites) {
            int count = count_for(page);
            if (favourite_selection.row >= count) favourite_selection.row = count ? count - 1 : 0;
        }
        pin_notice = "Removed from Favourites";
        return true;
    }
    if (favourite_count < FAVOURITE_LIMIT) {
        favourites[favourite_count++] = item;
        pin_notice = item.equation ? "Equation added to Favourites" : "Topic added to Favourites";
    } else pin_notice = "Favourites list is full";
    return true;
}

static void open_favourite(void) {
    Favourite item = favourites[favourite_index(favourite_selection.row)];
    if (item.equation) {
        favourite_origin = true;
        chemistry_sheet = item.chemistry;
        physics_selection = (Selection){item.row,0};
        open_equation();
        return;
    }
    course_selection = (Selection){item.course,0};
    chapter_selection = (Selection){item.chapter,0};
    topic_selection = (Selection){item.row,0};
    if (!topic()->method) begin_read(topic()->title,topic()->course);
    else {
        favourite_origin = true;
        topic_action = (Selection){0};
        page = TopicMenu;
    }
}

static void open_tool(ExtraTool selection) {
    extra_tool = selection;
    active_field = tool_first = 0;
    if (selection == TriangleSolver) {
        static const char *const labels[] = {"Side a (opposite A)","Side b (opposite B)","Side c (opposite C)",
                                             "Angle A","Angle B","Angle C"};
        field_count = 6;
        for (int i = 0; i < field_count; i++) {
            form_labels[i] = labels[i];
            set_field(&forms[i],"",false);
        }
    } else {
        field_count = selection == TrigSolver ? 3 : 2;
        form_labels[0] = selection == TrigSolver ? "Equation in x" : "Physics equation";
        set_field(&forms[0],selection == TrigSolver ? "sin(x)=0.5" : "v^2=u^2+2as",true);
        form_labels[1] = selection == TrigSolver ? "Lower bound" : "Symbol to isolate";
        set_field(&forms[1],selection == TrigSolver ? "0" : "a",true);
        if (selection == TrigSolver) {
            form_labels[2] = "Upper bound";
            set_field(&forms[2],degrees ? "360" : "2pi",true);
        }
    }
    tool_parent = CasMenu;
    page = ToolForm;
}

static void submit_tool(void) {
    for (int i = 0; i < field_count; i++) finish_parentheses(&forms[i]);
    if (extra_tool == TrigSolver)
        cas_trig_equation(forms[0].text,forms[1].text,forms[2].text,degrees,&tool_solution);
    else if (extra_tool == PhysicsRearrange)
        rearrange_physics(forms[0].text,forms[1].text,&tool_solution);
    else {
        const char *inputs[6];
        for (int i = 0; i < 6; i++) inputs[i] = forms[i].text;
        solve_triangle(inputs,degrees,&tool_solution);
    }
    record(history, &history_count, HISTORY_LIMIT,
           extra_tool == TriangleSolver ? extra_tool_names[extra_tool] : forms[0].text,
           Calculate, extra_tool_names[extra_tool], &tool_solution);
    capture_form_reuse(ReuseExtra, extra_tool);
    record_form_inputs();
    session_autosave();
    tool_offset = 0;
    page = ToolOutput;
}

static void open_physics_topic(void) {
    const char *section = equation()->section;
    size_t length = strlen(section);
    for (int i = 0; i < course_count; i++) {
        const Course *entry = &courses[i];
        if (strcmp(entry->code, chemistry_sheet ? "8462" : "8463")) continue;
        for (int j = 0; j < entry->count; j++) {
            const Chapter *group = &entry->chapters[j];
            const Topic *match = NULL;
            for (int k = 0; k < group->count; k++) {
                const Topic *card = &group->topics[k];
                if (!strncmp(card->course, section, length) && card->course[length] == '\n') {
                    if (!match) match = card;
                    if (chemistry_sheet && equation()->higher && higher_suffix(card->title)) {
                        match = card;
                        break;
                    }
                }
            }
            if (match) {
                course_selection = (Selection){i,0};
                chapter_selection = (Selection){j,0};
                topic_selection = (Selection){(int)(match-group->topics),0};
                begin_read(match->title, match->course);
                return;
            }
        }
        return;
    }
}

static const char cas_help[] =
    "In a form, UP/DOWN moves between values. Typing replaces a selected default. EXE works it out.\n"
    "CAS uses one variable x. Solve handles real polynomial roots. The interval tool bisects a continuous function. "
    "Indefinite integrals cover polynomials and selected elementary functions. Definite integrals accept polynomials.\n"
    "Numeric functions include ncr(n,r), npr(n,r), binom(n,r,p), and norm(z).";

static void back(void) {
    switch (page) {
        case Toolbox: page = toolbox_parent; break;
        case CasMenu: page = cas_parent; break;
        case GeneralMenu: page = general_parent; general_active = false; break;
        case About: case SessionName: case SessionList: page = GeneralMenu; break;
        case EquationFavourites: page = CasMenu; break;
        case Chapters: page = Toolbox; break;
        case Topics: page = Chapters; break;
        case TopicMenu:
            page = favourite_origin ? Favourites : Topics;
            favourite_origin = false;
            break;
        case Examples: page = TopicMenu; break;
        case PhysicsList: page = CasMenu; break;
        case PhysicsDetail:
            page = favourite_origin ? Favourites : equation_parent;
            favourite_origin = false;
            break;
        case PhysicsSubjects: page = PhysicsDetail; break;
        case PhysicsForm: page = PhysicsSubjects; break;
        case ScienceResult:
            science_work.answer[0] = 0;
            page = PhysicsForm;
            break;
        case UnitGroups: page = CasMenu; break;
        case UnitFrom: page = UnitGroups; break;
        case UnitTo: page = UnitFrom; break;
        case UnitValue: page = UnitTo; break;
        case UnitResult: page = UnitValue; break;
        case Form: page = form_parent; break;
        case Result: page = result_parent; break;
        case Settings: page = native_parent; break;
        case DecimalPlaces: page = Settings; break;
        case Favourites: page = favourite_parent; break;
        case ToolForm: page = tool_parent; break;
        case ToolOutput: page = ToolForm; break;
        case CalcHistory: page = Prompt; break;
        case CalcExtras: page = CalcHistory; break;
        case Shortcuts: case History: page = GeneralMenu; break;
        case HistoryResult: page = History; break;
        case Reading: page = reading_parent; break;
        case Search: page = search_parent; break;
        case RelatedEquations:
            page = related_parent;
            if (page == Reading) {
                read_content = related_read_content;
                read_title = related_read_title;
                reading_parent = related_reading_parent;
                read_offset = related_read_offset;
                course_selection = (Selection){related_topic.course,0};
                chapter_selection = (Selection){related_topic.chapter,0};
                topic_selection = (Selection){related_topic.row,0};
            }
            break;
        default: break;
    }
}

static void choose(void) {
    switch (page) {
        case Toolbox:
            if (course_list_selection.row == 1) { begin_search(false); break; }
            if (!course_list_selection.row) {
                open_favourites(CoursePins, Toolbox);
                break;
            }
            course_selection = (Selection){course_list_selection.row - 2, 0};
            chapter_selection = (Selection){0};
            page = Chapters;
            break;
        case Chapters:
            topic_selection = (Selection){0};
            page = Topics;
            break;
        case Topics:
            if (!topic()->method) begin_read(topic()->title, topic()->course);
            else {
                topic_action = (Selection){0};
                page = TopicMenu;
            }
            break;
        case TopicMenu: {
            const Topic *item = topic();
            int row = topic_action.row;
            if (row == 0) begin_read(item->title, item->detail->notes);
            else if (row == 1) begin_read(item->title, item->method);
            else if (row == 2 && item->labels[0]) form_for(item->operation, item, TopicMenu);
            else {
                example_selection = (Selection){0};
                page = Examples;
            }
            break;
        }
        case Examples: {
            const Topic *item = topic();
            if (example_selection.row > 0) {
                const WorkedExample *example = &item->detail->examples[example_selection.row - 1];
                begin_read(example->title, example->working);
            } else if (item->example) begin_read(item->title, item->example);
            else {
                form_for(item->operation, item, Examples);
                submit_form(true);
            }
            break;
        }
        case GeneralMenu:
            switch (general_selection.row) {
                case MenuCourses:
                    if (general_parent == Toolbox) general_parent = toolbox_parent;
                    toolbox_parent = GeneralMenu;
                    course_list_selection = (Selection){0};
                    page = Toolbox;
                    break;
                case MenuEquations:
                    if (general_parent == CasMenu) general_parent = cas_parent;
                    cas_parent = GeneralMenu;
                    cas_selection = (Selection){0};
                    page = CasMenu;
                    break;
                case MenuNewSession: session_name = (Field){0}; session_error = NULL; page = SessionName; break;
                case MenuOpenSession: session_selection = (Selection){active_session,0}; page = SessionList; break;
                case MenuHistory: history_selection = (Selection){0}; page = History; break;
                case MenuShortcuts: shortcuts_offset = 0; page = Shortcuts; break;
                case MenuPreferences: native_parent = GeneralMenu; settings_selection = (Selection){0}; page = Settings; break;
                case MenuAbout: page = About; break;
            }
            break;
        case SessionList:
            if (open_session(session_selection.row)) {
                general_active = false;
                session_autosave();
            }
            break;
        case CasMenu:
            switch (cas_selection.row) {
                case CasFavourites: equation_favourite_selection = (Selection){0}; page = EquationFavourites; break;
                case CasSearch: begin_search(true); break;
                case CasPhysics: case CasChemistry:
                    chemistry_sheet = cas_selection.row == CasChemistry;
                    favourite_origin = equation_from_related = false;
                    equation_parent = PhysicsList;
                    physics_list_selection = (Selection){0};
                    page = PhysicsList;
                    break;
                case CasUnits:
                    unit_group = (Selection){0};
                    set_field(&unit_input, "", false);
                    page = UnitGroups;
                    break;
                case CasRearrange: open_tool(PhysicsRearrange); break;
                case CasTrig: open_tool(TrigSolver); break;
                case CasTriangle: open_tool(TriangleSolver); break;
                default: form_for(cas_menu_operation(cas_selection.row), NULL, CasMenu); break;
            }
            break;
        case EquationFavourites:
            open_favourites(equation_favourite_selection.row == 0 ? PhysicsPins : ChemistryPins, EquationFavourites);
            break;
        case Favourites:
            if (favourite_index(favourite_selection.row) >= 0) open_favourite();
            break;
        case DecimalPlaces:
            decimal_places = decimal_selection.row;
            session_autosave();
            if (general_parent == CalcExtras && calc_count) prepare_calc_extras();
            page = Settings;
            break;
        case UnitGroups:
            unit_from = (Selection){0};
            page = UnitFrom;
            break;
        case UnitFrom:
            unit_to = (Selection){unit_from.row == 0 ? 1 : 0, 0};
            page = UnitTo;
            break;
        case UnitTo:
            unit_input_error = false;
            page = UnitValue;
            break;
        case RelatedEquations:
            open_search_match(&related_matches[related_selection.row]);
            break;
        case PhysicsList:
            if (physics_list_selection.row == count_for(PhysicsList) - 1) begin_search(true);
            else if (!physics_list_selection.row) open_favourites(chemistry_sheet ? ChemistryPins : PhysicsPins, PhysicsList);
            else {
                physics_selection = (Selection){physics_list_selection.row - 1, 0};
                equation_parent = PhysicsList;
                equation_from_related = false;
                open_equation();
            }
            break;
        case PhysicsSubjects:
            physics_focus = physics_first = 0;
            science_work.answer[0] = 0;
            page = PhysicsForm;
            break;
        case History:
            if (history_count) {
                history_offset = 0;
                page = HistoryResult;
            }
            break;
        case Settings:
            if (settings_selection.row == 0) degrees = !degrees;
            if (settings_selection.row == 1) decimal = !decimal;
            if (settings_selection.row == 2) show_steps = !show_steps;
            if (settings_selection.row < 3) session_autosave();
            if (settings_selection.row == 3) begin_read("CAS help", cas_help);
            if (settings_selection.row == 4) {
                decimal_selection = (Selection){decimal_places,0};
                page = DecimalPlaces;
            }
            break;
        default: break;
    }
}

static const char *key_text(int key) {
    static const char *const keys[64] = {
        [eadk_key_xnt] = "x", [eadk_key_exp] = "exp(", [eadk_key_ln] = "ln(",
        [eadk_key_log] = "log(", [eadk_key_imaginary] = "i", [eadk_key_comma] = ",", [eadk_key_power] = "^",
        [eadk_key_sine] = "sin(", [eadk_key_cosine] = "cos(", [eadk_key_tangent] = "tan(",
        [eadk_key_pi] = "-", [eadk_key_sqrt] = "sqrt(", [eadk_key_square] = "^2",
        [eadk_key_seven] = "7", [eadk_key_eight] = "8", [eadk_key_nine] = "9",
        [eadk_key_left_parenthesis] = "(", [eadk_key_right_parenthesis] = ")",
        [eadk_key_four] = "4", [eadk_key_five] = "5", [eadk_key_six] = "6",
        [eadk_key_multiplication] = "*", [eadk_key_division] = "/",
        [eadk_key_one] = "1", [eadk_key_two] = "2", [eadk_key_three] = "3",
        [eadk_key_plus] = "+", [eadk_key_minus] = "-", [eadk_key_zero] = "0",
        [eadk_key_dot] = ".", [eadk_key_ee] = "*10^",
        [eadk_key_fraction] = "/", [eadk_key_store] = "->"
    };
    return key >= 0 && key < 64 ? keys[key] : NULL;
}

static const char *shift_text(int key) {
    switch (key) {
        case eadk_key_xnt: return "->";
        case eadk_key_exp: return "ln(";
        case eadk_key_square: return "log(";
        case eadk_key_log: return "10^("; /* legacy CG50 key */
        case eadk_key_ln: return "exp(";
        case eadk_key_comma: return ":";
        case eadk_key_sine: return "asin(";
        case eadk_key_cosine: return "acos(";
        case eadk_key_tangent: return "atan(";
        case eadk_key_sqrt: return "cbrt(";
        case eadk_key_left_parenthesis: return "=";
        case eadk_key_seven: return "pi";
        case eadk_key_nine: return "i";
        case eadk_key_four: return "[";
        case eadk_key_five: return "]";
        case eadk_key_one: return "r";
        case eadk_key_two: return "theta";
        case eadk_key_minus: return "-";
        default: return NULL;
    }
}

static char alpha_character(int key, bool capitals) {
    static const char letters[64] = {
        [eadk_key_xnt]='a', [eadk_key_fraction]='b', [eadk_key_sqrt]='c',
        [eadk_key_power]='d', [eadk_key_square]='e', [eadk_key_exp]='f',
        [eadk_key_comma]='g', [eadk_key_sine]='h', [eadk_key_cosine]='i',
        [eadk_key_tangent]='j', [eadk_key_left_parenthesis]='k', [eadk_key_right_parenthesis]='l',
        [eadk_key_seven]='m', [eadk_key_eight]='n', [eadk_key_nine]='o',
        [eadk_key_four]='p', [eadk_key_five]='q', [eadk_key_six]='r',
        [eadk_key_multiplication]='s', [eadk_key_division]='t',
        [eadk_key_one]='u', [eadk_key_two]='v', [eadk_key_three]='w',
        [eadk_key_plus]='x', [eadk_key_minus]='y', [eadk_key_zero]='z',
        [eadk_key_dot]=' ', [eadk_key_ee]='"'
    };
    char letter = key >= 0 && key < 64 ? letters[key] : 0;
    return capitals ? (char)toupper((unsigned char)letter) : letter;
}

static void edit(Field *field, int key, bool shifted, bool alphabetic, char letter) {
    int from = selection_start(field), to = selection_end(field);
    if (letter) {
        const char text[] = {letter, 0};
        if (overwrite_text && from == to && field->text[field->cursor]) field->anchor++;
        insert(field, text); selecting_text = false;
        return;
    }
    bool function = shifted && !alphabetic;
    if (key == eadk_key_clear) { set_field(field, "", false); selecting_text = false; return; }
    if (function && key == eadk_key_zero) {
        selecting_text = true; clipboard_field = field; field->anchor = field->cursor; return;
    }
    if (function && key == eadk_key_dot) {
        if (*clipboard) insert(field, clipboard);
        selecting_text = false; return;
    }
    if (function && key == eadk_key_backspace) { overwrite_text = !overwrite_text; return; }
    if (function && key == eadk_key_power) {
        insert(field, "log()/log()"); field->cursor -= 7; field->anchor = field->cursor; return;
    }
    if (function && key == eadk_key_fraction) {
        insert(field, "(0+0/1)"); field->cursor -= 6; field->anchor = field->cursor + 1; return;
    }
    if (key <= eadk_key_right && (function || key == eadk_key_left || key == eadk_key_right)) {
        int end = (int)strlen(field->text);
        if (!function && !selecting_text && from != to) {
            field->anchor = field->cursor;
            return;
        }
        if (key == eadk_key_up) field->cursor = 0;
        if (key == eadk_key_down) field->cursor = end;
        if (key == eadk_key_left && field->cursor > 0) field->cursor--;
        if (key == eadk_key_right && field->cursor < end) field->cursor++;
        if (!function && !selecting_text) field->anchor = field->cursor;
        return;
    }
    if (key == eadk_key_backspace) {
        if (to > from) replace_range(field, from, to, "");
        else if (function) {
            if (field->text[field->cursor])
                replace_range(field, field->cursor, (int)strlen(field->text), "");
            else set_field(field, "", false);
        } else if (field->cursor > 0) replace_range(field, field->cursor - 1, field->cursor, "");
        return;
    }
    if (function && key == eadk_key_var) {
        if (to > from) snprintf(clipboard, sizeof(clipboard), "%.*s", to-from, field->text+from);
        return;
    }
    const char *text = function ? shift_text(key) : NULL;
    char previous[EXPRESSION_SIZE + 2];
    if (key == eadk_key_ans && *ans) {
        snprintf(previous, sizeof(previous), "(%s)", ans);
        text = previous;
    }
    if (!text && !function && !alphabetic) text = key_text(key);
    if (text) {
        if (overwrite_text && from == to && field->text[field->cursor]) field->anchor++;
        insert(field, text); selecting_text = false;
    }
}

static void submit_conversion(void) {
    finish_parentheses(&unit_input);
    double value, result;
    const Unit *units = selected_unit_group()->units;
    const Unit *from = &units[unit_from.row], *to = &units[unit_to.row];
    unit_input_error = !cas_read_number(unit_input.text, &value) || !unit_convert(value, from, to, &result);
    if (unit_input_error) return;
    snprintf(unit_number, sizeof(unit_number), "%.12g", result);
    snprintf(unit_expression, sizeof(unit_expression), "%.12g %s", value, from->symbol);
    unit_working(unit_work, sizeof(unit_work), value, from, to, result);
    unit_copied = false;
    Solution converted = {.ok = true};
    snprintf(converted.steps, sizeof(converted.steps), "%s", unit_work);
    snprintf(converted.answer, sizeof(converted.answer), "%s %s", unit_number, to->symbol);
    record(history, &history_count, HISTORY_LIMIT, unit_expression, Calculate, "Unit conversions", &converted);
    history[0].reuse = (ReuseData){.kind=ReuseUnit,.id=unit_group.row,.subject=unit_from.row,
                                 .topic=unit_to.row,.count=1,.degrees=degrees};
    snprintf(history[0].reuse.inputs[0], EXPRESSION_SIZE, "%s", unit_input.text);
    session_autosave();
    page = UnitResult;
}

static void open_calculation_history(void) {
    calc_first=calc_row=0;
    calc_column=default_calc_column(&calculations[0]);
    page=CalcHistory;
}

static void handle_calculation_history(int key,bool copy) {
    if (key==eadk_key_up || key==eadk_key_down) {
        if (key==eadk_key_down && calc_row==0) { page=Prompt;return; }
        int row=calc_row+(key==eadk_key_up?1:-1);
        if (row<calc_count) {
            calc_row=row;
            calc_column=default_calc_column(&calculations[calc_row]);
        }
        return;
    }
    const CalcEntry *item=&calculations[calc_row];
    if (key==eadk_key_left || key==eadk_key_right) {
        int step=key==eadk_key_left?-1:1;
        for (int next=calc_column+step;next>=CalcInputColumn && next<=CalcDotsColumn;next+=step) {
            if (!calc_column_available(item,next)) continue;
            calc_column=next;
            break;
        }
        return;
    }
    if (key!=eadk_key_ok && key!=eadk_key_exe && !copy) return;
    if (calc_column==CalcDotsColumn) {
        if (!copy) {
            prepare_calc_extras();
            if (extras_count) page=CalcExtras;
        }
        return;
    }
    char rendered[32];
    const char *value=item->input;
    if (calc_column==CalcExactColumn) value=item->result.exact;
    if (calc_column==CalcDecimalColumn) {
        format_calc_decimal(rendered,sizeof(rendered),item->result.value);
        value=rendered;
    }
    if (copy) snprintf(clipboard,sizeof(clipboard),"%s",value);
    else {
        insert(&prompt,value);
        page=Prompt;
    }
}

static void create_session(void) {
    const char *name = session_name.text;
    size_t length = strlen(name);
    if (!valid_session_name(name, length)) {
        session_error = "Use 1 to 23 letters, digits or _.";
        return;
    }
    for (int i = 0; i < session_count; i++) {
        if (!strcmp(session_names[i], name)) {
            session_error = "That session already exists.";
            return;
        }
    }
    if (session_count == SESSION_LIMIT) {
        session_error = "The four session slots are full.";
        return;
    }
    if (!session_store.records) {
        session_error = "Session storage is unavailable.";
        return;
    }
    if (session_dirty && !save_active_session()) {
        session_error = "Save current session before switching.";
        return;
    }
    {
        char file[SESSION_NAME_SIZE + 11];
        session_filename(file, name);
        size_t position = 0;
        ScriptRecord record;
        while (script_record_next(session_store, &position, &record)) {
            if (strcmp(record.name, file)) continue;
            session_error = "That session file already exists.";
            return;
        }
        if (sizeof(session_script) + strlen(file) + 6 > session_store.capacity - position) {
            session_error = "Session storage is full.";
            return;
        }
    }
    memcpy(session_names[session_count], name, length + 1);
    if (!open_session(session_count)) return;
    session_count++;
    general_active = false;
    session_autosave();
}

static Field *current_field(void) {
    if (page == Search) return &search_query;
    if (page == SessionName) return &session_name;
    if (page == PhysicsForm) return &physics_fields[physics_slot(physics_focus)];
    if (page == UnitValue) return &unit_input;
    if (page == Form || page == ToolForm) return &forms[active_field];
    if (page == Prompt || page == Result) return &prompt;
    return NULL;
}

static bool handle_key(int key, bool shifted, bool alphabetic) {
    pin_notice = NULL;
    if (native_menu) {
        if (key == eadk_key_pageup) native_row = imax(0,native_row-7);
        if (key == eadk_key_pagedown) native_row = (native_row+7 < native_count() ? native_row+7 : native_count()-1);
        if (native_menu == 2 && key == eadk_key_right) native_row = 27;
        if (native_menu == 2 && key == eadk_key_left) native_row = 0;
        if (key == eadk_key_back || key == eadk_key_clear) { native_menu = 0; selecting_text = false; return true; }
        if (key == eadk_key_up && native_row > 0) native_row--;
        if (key == eadk_key_down && native_row + 1 < native_count()) native_row++;
        if (key == eadk_key_ok || key == eadk_key_exe) {
            if (native_menu == 1) {
                int from = selection_start(clipboard_field), to = selection_end(clipboard_field);
                snprintf(clipboard, sizeof(clipboard), "%.*s", to-from, clipboard_field->text+from);
                if (native_row) replace_range(clipboard_field, from, to, "");
                selecting_text = false;
            } else if (native_row == 0) { lowercase_letters = !lowercase_letters; return true; }
            else if (native_field) {
                char letter[2] = {(char)((lowercase_letters ? 'a' : 'A') + native_row - 1),0};
                insert(native_field, native_row <= 26 ? letter : symbol_inputs[native_row - 27]);
            }
            native_menu = 0;
        }
        return true;
    }
    if (selecting_text && current_field() != clipboard_field) selecting_text = false;
    if (selecting_text && (key == eadk_key_ok || key == eadk_key_exe)) {
        native_menu = 1; native_row = 0; return true;
    }
    if (key == eadk_key_back || key == eadk_key_home) selecting_text = false;
    if (key == eadk_key_clear && shifted) { session_autosave(); return false; }
    if (key == eadk_key_variable) {
        native_menu = 2; native_row = 0; native_field = current_field(); return true;
    }
    if (key == eadk_key_settings) {
        native_parent = page; settings_selection = (Selection){0}; page = Settings; return true;
    }
    if (key == eadk_key_format) {
        #if NUMAI_FXCG100
        if (alphabetic && !shifted) { key = eadk_key_ans; alphabetic = false; }
        else if (alphabetic) key = eadk_key_ans;
#else
        if (alphabetic) key = eadk_key_ans;
#endif
        else if (shifted) { key = eadk_key_ans; shifted = false; }
        else {
            if (calc_count && (page == Prompt || page == CalcHistory)) {
                if (page == Prompt) open_calculation_history();
                prepare_calc_extras(); if (extras_count) page = CalcExtras;
            }
            return true;
        }
    }
    if (key == eadk_key_prevtab || key == eadk_key_nexttab) {
        bool next = key == eadk_key_nexttab;
        if (page == Form || page == ToolForm) {
            active_field = (active_field + (next ? 1 : field_count-1)) % field_count;
        } else if (page == PhysicsForm) {
            int count = equation()->count - 1;
            if (count > 0) physics_focus = (physics_focus + (next ? 1 : count-1)) % count;
        } else if (next) { if (page == Prompt) { course_list_selection = (Selection){0}; page = Toolbox; toolbox_parent = Prompt; }
            else if (page == Toolbox) { cas_selection = (Selection){0}; page = CasMenu; cas_parent = Prompt; }
            else page = Prompt;
        } else { if (page == Prompt) { cas_selection = (Selection){0}; page = CasMenu; cas_parent = Prompt; }
            else if (page == CasMenu) { course_list_selection = (Selection){0}; page = Toolbox; toolbox_parent = Prompt; }
            else page = Prompt;
        }
        return true;
    }
    if (key == eadk_key_pageup || key == eadk_key_pagedown) {
        for (int i = 0; i < 6; i++) handle_key(key == eadk_key_pageup ? eadk_key_up : eadk_key_down, false, false);
        return true;
    }
    if (key == eadk_key_ans && alphabetic) {
        if (session_dirty) session_autosave();
        page = Prompt;
        general_active = false;
        shift = false;
        alpha = AlphaOff;
        favourite_origin = equation_from_related = false;
        return true;
    }
    if (key == eadk_key_exe && shifted) {
        if (general_active) {
            page = general_parent;
            general_active = false;
        } else {
            general_parent = page;
            general_active = true;
            general_selection = (Selection){0};
            page = GeneralMenu;
        }
        return true;
    }
    char letter = alphabetic ? alpha_character(key, !lowercase_letters) : '\0';
    bool function = shifted && !alphabetic;
    if (page == Search) {
        if (key == eadk_key_back) back();
        else if (key == eadk_key_up && search_selection.row > 0) search_selection.row--;
        else if (key == eadk_key_down && search_selection.row + 1 < search_count) search_selection.row++;
        else if (key == eadk_key_ok || key == eadk_key_exe) {
            if (search_count) open_search_match(&search_matches[search_selection.row]);
        } else if (key != eadk_key_up && key != eadk_key_down) {
            edit(&search_query, key, shifted, alphabetic, letter);
            refresh_search();
        }
        return true;
    }
    if (key == eadk_key_var && !function && !alphabetic && reading_is_topic()) {
        find_related();
        if (related_count) {
            related_parent = page;
            related_read_content = read_content;
            related_read_title = read_title;
            related_reading_parent = reading_parent;
            related_read_offset = read_offset;
            related_topic = (SearchMatch){course_selection.row,chapter_selection.row,topic_selection.row,false,false};
            related_selection = (Selection){0};
            page = RelatedEquations;
            if (related_count == 1) open_search_match(&related_matches[0]);
        } else pin_notice = "No related equation sheet entries.";
        return true;
    }
    if (!function && !alphabetic &&
        ((key == eadk_key_toolbox && page == Toolbox) ||
         (key == eadk_key_var && (page == CasMenu || page == PhysicsList)))) {
        begin_search(page != Toolbox);
        return true;
    }
    if (page == HistoryResult && (key == eadk_key_exe || key == eadk_key_ok)) {
        reuse_history();
        return true;
    }
    if (page == SessionName) {
        if (key == eadk_key_back) back();
        else if (key == eadk_key_exe || key == eadk_key_ok) create_session();
        else {
            session_error = NULL;
            edit(&session_name, key, shifted, alphabetic, letter);
        }
        return true;
    }
    if (function && key == eadk_key_var && pin_current()) return true;
    if (page == CalcHistory && function && key == eadk_key_var) {
        handle_calculation_history(key,true);
        return true;
    }
    if (page == UnitResult && function && key == eadk_key_var) {
        strcpy(clipboard, unit_number);
        unit_copied = true;
        return true;
    }
    Field *field = page == PhysicsForm ? &physics_fields[physics_slot(physics_focus)] :
                   page == UnitValue ? &unit_input :
                   (page == Form || page == ToolForm) ? &forms[active_field] :
                   (page == Prompt || page == Result) ? &prompt : NULL;
    if (field && (letter || (function && (key <= eadk_key_right || key == eadk_key_xnt ||
                                          key == eadk_key_var || key == eadk_key_toolbox)))) {
        edit(field, key, shifted, alphabetic, letter);
        if (page == PhysicsForm) science_work.answer[0] = 0;
        if (page == UnitValue) unit_input_error = false;
        return true;
    }
    if (letter || (function && (key == eadk_key_var || key == eadk_key_toolbox))) return true;

    if (key == eadk_key_back) {
        if (page == Prompt) {
            if (*prompt.text) set_field(&prompt,"",false);
            else if (!calc_count) return false;
            return true;
        }
        back();
        return true;
    }
    if ((key == eadk_key_toolbox || key == eadk_key_var) &&
        (page == Prompt || page == Result || page == Toolbox || page == CasMenu || page == CalcHistory)) {
        Page target = key == eadk_key_toolbox ? Toolbox : CasMenu;
        if (page == target) back();
        else {
            if (target == CasMenu) {
                cas_selection = (Selection){0};
                cas_parent = Prompt;
            } else {
                course_list_selection = (Selection){0};
                toolbox_parent = Prompt;
            }
            page = target;
        }
        return true;
    }
    if (page == CalcHistory) {
        handle_calculation_history(key,false);
        return true;
    }
    if (page == CalcExtras) {
        if (key == eadk_key_up && extras_row>0) extras_row--;
        else if (key == eadk_key_down && extras_row+1<extras_count) extras_row++;
        else if ((key==eadk_key_ok || key==eadk_key_exe) && *extra_results[extras_row].reuse) {
            insert(&prompt,extra_results[extras_row].reuse);
            page=Prompt;
        }
        return true;
    }
    if (page == Shortcuts) {
        if (key == eadk_key_up && shortcuts_offset > 0) shortcuts_offset--;
        else if (key == eadk_key_down && shortcuts_offset < SHORTCUT_COUNT - SHORTCUT_ROWS) shortcuts_offset++;
        return true;
    }
    Selection *selection = selection_for(page);
    if (selection) {
        int count = count_for(page);
        if (key == eadk_key_up && selection->row > 0) selection->row--;
        else if (key == eadk_key_down && selection->row + 1 < count) selection->row++;
        else if (key == eadk_key_ok || key == eadk_key_right || key == eadk_key_exe) choose();
        else if (key == eadk_key_left) back();
        return true;
    }
    if (page == PhysicsDetail) {
        if (key == eadk_key_up || key == eadk_key_down)
            physics_offset += key == eadk_key_up ? -1 : 1;
        else if (key == eadk_key_toolbox) open_physics_topic();
        else if (key == eadk_key_ok || key == eadk_key_exe) page = PhysicsSubjects;
        return true;
    }
    if (page == PhysicsForm) {
        int count = equation()->count - 1;
        if (key == eadk_key_up && physics_focus > 0) physics_focus--;
        else if (key == eadk_key_down && physics_focus + 1 < count) physics_focus++;
        else if (key == eadk_key_exe || key == eadk_key_ok) {
            const char *values[SCIENCE_VARIABLES] = {0};
            for (int i = 0; i < count; i++) {
                int slot = physics_slot(i);
                finish_parentheses(&physics_fields[slot]);
                values[slot] = physics_fields[slot].text;
            }
            physics_answer_ok = physics_solve(equation(), science_subject(physics_subject.row), values, &science_work);
            Solution worked = {.ok = physics_answer_ok};
            snprintf(worked.steps, sizeof(worked.steps), "%.150s\n%.150s\n%.195s",
                     science_work.conversions, science_work.steps, science_work.substituted);
            snprintf(worked.answer, sizeof(worked.answer), "%s", science_work.answer);
            record(history, &history_count, HISTORY_LIMIT, equation()->title, Calculate, equation()->title, &worked);
            ReuseData *reuse = &history[0].reuse;
            *reuse = (ReuseData){.kind=ReuseScience,.id=physics_selection.row,
                                .subject=physics_subject.row,.course=chemistry_sheet,
                                .count=equation()->count,.degrees=degrees};
            for (int i = 0; i < equation()->count; i++)
                memcpy(reuse->inputs[i], physics_fields[i].text, EXPRESSION_SIZE);
            session_autosave();
            if (*science_work.substituted) {
                science_result_offset = 0;
                page = ScienceResult;
            }
        } else if (key != eadk_key_up && key != eadk_key_down) {
            edit(&physics_fields[physics_slot(physics_focus)], key, shifted, alphabetic, letter);
            if (key != eadk_key_left && key != eadk_key_right) science_work.answer[0] = 0;
        }
        return true;
    }
    if (page == ScienceResult) {
        if (key == eadk_key_up || key == eadk_key_down)
            science_result_offset += key == eadk_key_up ? -1 : 1;
        return true;
    }
    if (page == UnitValue) {
        if (key == eadk_key_exe || key == eadk_key_ok) submit_conversion();
        else {
            edit(&unit_input, key, shifted, alphabetic, letter);
            unit_input_error = false;
        }
        return true;
    }
    if (page == UnitResult) return true;
    if (page == ToolForm) {
        if (key == eadk_key_up && active_field > 0) active_field--;
        else if (key == eadk_key_down && active_field+1 < field_count) active_field++;
        else if (key == eadk_key_ok || key == eadk_key_exe) submit_tool();
        else if (key != eadk_key_up && key != eadk_key_down)
            edit(&forms[active_field],key,shifted,alphabetic,letter);
        return true;
    }
    if (page == ToolOutput || page == HistoryResult) {
        if (key == eadk_key_up || key == eadk_key_down) {
            int *offset = page == ToolOutput ? &tool_offset : &history_offset;
            *offset += key == eadk_key_up ? -1 : 1;
        }
        return true;
    }
    if (page == Reading || page == Result) {
        if (key == eadk_key_up || key == eadk_key_down) {
            read_offset += key == eadk_key_up ? -1 : 1;
            return true;
        }
        if (page == Reading) return true;
    }
    if (page == Form) {
        if (key == eadk_key_up && active_field > 0) active_field--;
        else if (key == eadk_key_down && active_field + 1 < field_count) active_field++;
        else if (key == eadk_key_exe || key == eadk_key_ok) submit_form(false);
        else edit(&forms[active_field], key, shifted, alphabetic, letter);
        return true;
    }
    if (key == eadk_key_exe || key == eadk_key_ok) submit_prompt();
    else if (key == eadk_key_up && page == Prompt && calc_count) open_calculation_history();
    else if (key == eadk_key_up && page == Prompt && has_result) {
        result_parent = Prompt;
        page = Result;
    }
    else edit(&prompt, key, shifted, alphabetic, letter);
    return true;
}

static bool repeats(int key) {
    return (key >= eadk_key_left && key <= eadk_key_right) || key == eadk_key_backspace;
}

int main(void) {
    extern void casio_init(void);
    casio_init();
    load_sessions();
    eadk_keyboard_state_t previous = eadk_keyboard_scan();
    const uint64_t shift_bit = UINT64_C(1) << eadk_key_shift;
    const uint64_t alpha_bit = UINT64_C(1) << eadk_key_alpha;
    int repeat_key = -1, repeat_ticks = 0;
    bool repeat_shift = false, repeat_alpha = false, used_shift = false, used_alpha = false;
    draw();
    for (;;) {
        eadk_keyboard_state_t state = eadk_keyboard_scan();
        eadk_keyboard_state_t pressed = state & ~previous;
        previous = state;
        if (eadk_keyboard_key_down(pressed, eadk_key_home)) return 0;

        bool redraw = false;
        if (used_shift && !(state & shift_bit)) {
            used_shift = shift = false;
            redraw = true;
        }
        if (used_alpha && !(state & alpha_bit)) {
            used_alpha = false;
            if (alpha != AlphaLocked) alpha = AlphaOff;
            redraw = true;
        }
        if (pressed & shift_bit) {
            shift = !shift;
            redraw = true;
        }
        if (pressed & alpha_bit) {
            if (shift || (state & shift_bit)) { alpha = AlphaLocked; shift = false; used_shift = (state & shift_bit) != 0; }
            else alpha = alpha == AlphaOff ? AlphaOnce : AlphaOff;
            redraw = true;
        }
        pressed &= ~(shift_bit | alpha_bit);

        if (repeat_key >= 0 && eadk_keyboard_key_down(state, (eadk_key_t)repeat_key)) {
            if (repeat_shift != (shift || (state & shift_bit)) ||
                repeat_alpha != (alpha != AlphaOff || (state & alpha_bit))) repeat_key = -1;
            else if (++repeat_ticks >= 22 && (repeat_ticks - 22) % 4 == 0) {
                handle_key(repeat_key, repeat_shift, repeat_alpha);
                redraw = true;
            }
        } else repeat_key = -1;

        for (int key = 0; pressed && key <= eadk_key_last; key++) {
            if (!eadk_keyboard_key_down(pressed, (eadk_key_t)key)) continue;
            bool shifted = shift || (state & shift_bit);
            bool alphabetic = alpha != AlphaOff || (state & alpha_bit);
            if (!handle_key(key, shifted, alphabetic)) return 0;
            used_shift = (state & shift_bit) != 0;
            used_alpha = (state & alpha_bit) != 0;
            if (!used_shift) shift = false;
            if (alpha != AlphaLocked && !used_alpha) alpha = AlphaOff;
            if (repeats(key) && !(selection_for(page) && (key == eadk_key_left || key == eadk_key_right))) {
                repeat_key = key;
                repeat_ticks = 0;
                repeat_shift = shifted;
                repeat_alpha = alphabetic;
            }
            redraw = true;
        }
        if (redraw) draw();
        eadk_timing_msleep(15);
    }
}
