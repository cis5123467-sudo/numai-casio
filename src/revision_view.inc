static void math_text(int x, int y, const char *text, uint16_t ink, uint16_t paper, bool small);

// Only these subject-specific symbols carry indices. The underlying formula and
// solver continue to use the published ASCII identifiers.
static const struct { const char *symbol, *base, *index; } physics_indices[] = {
    {"Eout","E","out"}, {"Ein","E","in"}, {"Ek","E","k"}, {"Ee","E","e"}, {"Ep","E","p"},
    {"Pout","P","out"}, {"Pin","P","in"}, {"Vp","V","p"}, {"Vs","V","s"},
    {"Ip","I","p"}, {"Is","I","s"}, {"np","n","p"}, {"ns","n","s"},
    {"hi","h","i"}, {"ho","h","o"}
};

static bool physics_notation(void) {
    return (!chemistry_sheet && (page == PhysicsDetail || page == ScienceResult || page == PhysicsForm ||
                                 page == PhysicsSubjects)) ||
           (page == Reading && (reading_parent == Topics || reading_parent == PhysicsDetail ||
                                reading_parent == Favourites) &&
            !strcmp(courses[course_selection.row].code, "8463"));
}

static bool math_word(const char *word, size_t length) {
    if (length <= 2) return true;
    static const char *const symbols[] = {
        "sin", "cos", "tan", "asin", "acos", "atan", "sqrt", "log", "exp", "abs", "min",
        "rho", "lambda", "eff", "Eout", "Ein", "Pout", "Pin", "mol", "rad", "deg",
        "hrs", "ohm", "lim"
    };
    for (unsigned i = 0; i < sizeof(symbols) / sizeof(*symbols); i++)
        if (strlen(symbols[i]) == length && !memcmp(word, symbols[i], length)) return true;
    return false;
}

static const char *math_token_end(const char *first) {
    static const char punctuation[] = "=<>+-*/^().!_%[],{}";
    size_t token_length = strcspn(first, " :;");
    bool symbolic = memchr(first, '=', token_length) != NULL;
    const char *p = first;
    while (*p && *p != ' ' && *p != ':' && *p != ';') {
        if (isalpha((unsigned char)*p)) {
            const char *word = p++;
            while (isalpha((unsigned char)*p)) p++;
            if (!symbolic && !math_word(word, (size_t)(p - word))) return first;
        } else if (isdigit((unsigned char)*p) || strchr(punctuation, *p)) p++;
        else break;
    }
    if (p > first && p[-1] == '.') p--;
    return p;
}

static bool math_token_start(char c) {
    return isalnum((unsigned char)c) || c == '(' || c == '+' || c == '-';
}

static bool format_formula(const char *first, const char *end, bool physics, bool units,
                           char *out, size_t capacity) {
    bool structured = false;
    size_t n = 0;
    for (const char *p = first; p < end; p++) {
        if (physics && (p == first || !isalpha((unsigned char)p[-1]))) {
            bool indexed = false;
            for (unsigned i = 0; i < sizeof(physics_indices) / sizeof(*physics_indices); i++) {
                size_t len = strlen(physics_indices[i].symbol);
                if ((size_t)(end - p) < len || memcmp(p, physics_indices[i].symbol, len) ||
                    (p + len != end && isalpha((unsigned char)p[len]))) continue;
                if (capacity - n < 9) return false;
                int added = snprintf(out + n, capacity - n, "%s_{%s}",
                                     physics_indices[i].base, physics_indices[i].index);
                n += (size_t)added;
                p += len - 1;
                indexed = structured = true;
                break;
            }
            if (indexed) continue;
        }
        if (*p == ' ') continue;
        if (n + 1 >= capacity) return false;
        if (*p == 'x' && p - first >= 2 && p + 2 < end && p[-1] == ' ' && p[1] == ' ' &&
            (isalnum((unsigned char)p[-2]) || p[-2] == ')') &&
            (isalnum((unsigned char)p[2]) || p[2] == '(')) out[n++] = '*';
        else out[n++] = *p == '/' && units ? MathLiteralSlash : *p;
        if (*p == '^' || (*p == '/' && !units && (p == first || p[-1] != '+')) ||
            (end - p >= 5 && !memcmp(p, "sqrt(", 5))) structured = true;
    }
    out[n] = 0;
    return structured;
}

static bool joined_math_token(const char *start, const char *end) {
    if (end == start) return false;
    if (end == start + 1 && strchr("=<>+-*/x", *start)) return true;
    return strcspn(start, "=<>+-*/^") < (size_t)(end - start);
}

static bool token_is_unit(const char *text, const char *first) {
    if (first > text && first[-1] == '[') return true;
    if (first - text < 2 || first[-1] != ' ' || !isdigit((unsigned char)first[-2])) return false;
    static const char *const units[] = {
        "m", "cm", "mm", "dm", "km", "g", "kg", "mg", "mol", "s", "ms", "h",
        "A", "mA", "V", "mV", "W", "kW", "J", "kJ", "K", "C", "N", "Pa", "Hz",
        "mL", "cL", "L", "ohm"
    };
    const char *last = first;
    while (isalpha((unsigned char)*last)) last++;
    for (unsigned i = 0; i < sizeof(units) / sizeof(*units); i++)
        if (strlen(units[i]) == (size_t)(last - first) && !memcmp(first, units[i], (size_t)(last - first)))
            return true;
    return false;
}

// A wrapped paragraph can contain prose and multiple independent expressions.
// Keep each expression inline, with a common baseline for the whole line.
static MathBox revision_line(const char *text, int x, int mid, eadk_color_t ink, eadk_color_t paper,
                             bool draw) {
    MathBox total = {0, 7, 7};
    MathCanvas canvas = {math_text, rectangle, ink, paper};
    const char *plain = text;
    bool physics = physics_notation();
    for (const char *p = text; *p;) {
        if (!math_token_start(*p) || (p > text && isalnum((unsigned char)p[-1]))) {
            p++;
            continue;
        }
        const char *end = math_token_end(p);
        if (end <= p) {
            const char *word = p;
            while (isalnum((unsigned char)*p)) p++;
            if (p == word) p++;
            continue;
        }
        bool units = token_is_unit(text, p);
        const char *next = end;
        while (!units && *next == ' ' && !token_is_unit(text, next + 1) &&
               (math_token_start(next[1]) || (next[1] && strchr("=<>*/", next[1])))) {
            const char *after = math_token_end(next + 1);
            if (after <= next + 1) break;
            bool connection = joined_math_token(next + 1, after) ||
                              (end > p && strchr("=<>+-*/", end[-1])) ||
                              (end - p >= 2 && end[-2] == ' ' && end[-1] == 'x');
            if (!connection) break;
            end = next = after;
        }
        char formula[TEXT_WIDTH * 2 + 1];
        int preceding = (int)(p - plain);
        int prefix_width = styled_width(plain, preceding);
        int remaining = EADK_SCREEN_WIDTH - 28 - total.width - prefix_width;
        if (remaining >= 14 && format_formula(p, end, physics && !units, units, formula, sizeof(formula))) {
            if (draw && preceding) {
                char prefix[TEXT_WIDTH + 1];
                snprintf(prefix, sizeof(prefix), "%.*s", preceding, plain);
                string_at(x + total.width, mid - 7, prefix, ink, paper);
            }
            total.width += prefix_width;
            MathBox box = measure_math(formula, remaining);
            if (draw) paint_math(formula, remaining, x + total.width, mid, &canvas);
            total.width += box.width;
            if (box.above > total.above) total.above = box.above;
            if (box.below > total.below) total.below = box.below;
            plain = end;
        }
        p = end;
    }
    if (draw && *plain) string_at(x + total.width, mid - 7, plain, ink, paper);
    total.width += styled_width(plain, -1);
    return total;
}

static void wrapped_text(int row, char text[TEXT_WIDTH + 1]) {
    const WrappedLine *line = &wrapped[row];
    memcpy(text, line->source, (size_t)line->length);
    text[line->length] = 0;
}

static MathBox measure_wrapped_line(int row) {
    char text[TEXT_WIDTH + 1];
    wrapped_text(row, text);
    return revision_line(text, 0, 0, Ink, White, false);
}

static void draw_wrapped_line(int row, int y, MathBox box) {
    const WrappedLine *line = &wrapped[row];
    char text[TEXT_WIDTH + 1];
    wrapped_text(row, text);
    int height = box.above + box.below + 2;
    eadk_color_t paper = line->highlight ? PaleGold : White;
    if (line->highlight) {
        rectangle(5, y, EADK_SCREEN_WIDTH - 10, height, PaleGold);
        rectangle(5, y, 3, height, Gold);
    }
    if (page == PhysicsDetail && physics_reference_heading(text)) {
        draw_text(11, y + 1, text, Ink, paper, true);
        rectangle(11, y + 15, casio_width(text, -1, false, true), 1, Ink);
    } else revision_line(text, 11, y + box.above + 1, Ink, paper, true);
}

static void reader(int top, int bottom) {
    int first_at_end = read_length;
    int available = bottom - top;
    if (read_offset > read_length - available / 16) {
        for (int height = 0; first_at_end > 0;) {
            MathBox box = measure_wrapped_line(first_at_end - 1);
            height += box.above + box.below + 2;
            if (height > available) break;
            first_at_end--;
        }
        if (read_offset > first_at_end) read_offset = first_at_end;
    }
    if (read_offset < 0) read_offset = 0;
    int y = top, visible = 0;
    for (int i = read_offset; i < read_length; i++) {
        MathBox box = measure_wrapped_line(i);
        int height = box.above + box.below + 2;
        if (y + height > bottom) break;
        draw_wrapped_line(i, y, box);
        y += height;
        visible++;
    }
    if (visible) scrollbar(read_offset, read_length, visible, top, available);
}
