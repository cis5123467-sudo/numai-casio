static void begin_read(const char *title, const char *content);
static void open_equation(void);
static void set_field(Field *field, const char *value, bool selected);
static bool reading_is_topic(void);

static bool contains_folded(const char *haystack, const char *needle, size_t length) {
    for (; *haystack; haystack++) {
        size_t i = 0;
        while (i < length && haystack[i] &&
               tolower((unsigned char)haystack[i]) == tolower((unsigned char)needle[i])) i++;
        if (i == length) return true;
    }
    return length == 0;
}

static bool matches_query(const char *const *texts, int count) {
    const char *word = search_query.text;
    while (*word) {
        while (isspace((unsigned char)*word)) word++;
        size_t length = strcspn(word, " \t");
        if (!length) break;
        bool found = false;
        for (int i = 0; i < count && !found; i++)
            found = texts[i] && contains_folded(texts[i], word, length);
        if (!found) return false;
        word += length;
    }
    return true;
}

static const PhysicsEquation *match_equation(const SearchMatch *match) {
    return &(match->chemistry ? chemistry_equations : physics_equations)[match->row];
}

static const char *match_title(const SearchMatch *match) {
    return match->equation ? match_equation(match)->title :
           courses[match->course].chapters[match->chapter].topics[match->row].title;
}

static void add_search_match(SearchMatch match) {
    if (search_count < SEARCH_LIMIT) search_matches[search_count++] = match;
    search_total++;
}

static void refresh_search(void) {
    search_count = search_total = 0;
    search_selection = (Selection){0};
    if (!equation_search) {
        for (int i = 0; i < course_count; i++)
            for (int j = 0; j < courses[i].count; j++) {
                const Chapter *chapter = &courses[i].chapters[j];
                for (int k = 0; k < chapter->count; k++) {
                    const Topic *item = &chapter->topics[k];
                    const char *texts[] = {courses[i].title, courses[i].code, chapter->title,
                                           item->title, item->course, item->method,
                                           item->detail ? item->detail->notes : item->example};
                    if (matches_query(texts, 7)) add_search_match((SearchMatch){i,j,k,false,false});
                }
            }
        return;
    }
    for (int sheet = 0; sheet < 2; sheet++) {
        const PhysicsEquation *items = sheet ? chemistry_equations : physics_equations;
        int count = sheet ? chemistry_equation_count : physics_equation_count;
        for (int row = 0; row < count; row++) {
            const PhysicsEquation *item = &items[row];
            const char *texts[6 + 3*SCIENCE_VARIABLES] = {
                sheet ? "Chemistry 8462" : "Physics 8463",
                item->title, item->topic, item->section, item->uses, item->higher ? "higher only" : ""
            };
            int used = 6;
            for (int i = 0; i < item->count; i++) {
                texts[used++] = item->variables[i].symbol;
                texts[used++] = item->variables[i].name;
                texts[used++] = item->variables[i].unit;
            }
            if (matches_query(texts, used)) add_search_match((SearchMatch){.row=row,.equation=true,.chemistry=sheet});
        }
    }
}

static void begin_search(bool equations) {
    search_parent = page;
    equation_search = equations;
    search_query = (Field){0};
    refresh_search();
    page = Search;
}

static void open_search_match(const SearchMatch *match) {
    if (match->equation) {
        equation_parent = page;
        equation_from_related = page == RelatedEquations;
        chemistry_sheet = match->chemistry;
        favourite_origin = false;
        physics_selection = (Selection){match->row,0};
        physics_list_selection = (Selection){match->row+1,0};
        open_equation();
        return;
    }
    course_selection = (Selection){match->course,0};
    chapter_selection = (Selection){match->chapter,0};
    topic_selection = (Selection){match->row,0};
    const Topic *item = topic();
    if (page == RelatedEquations) begin_read(item->title, item->method ? item->method : item->course);
    else begin_read(item->title, item->detail ? item->detail->notes : item->course);
}

static bool reading_is_topic(void) {
    if (page != Reading) return false;
    const Topic *item = topic();
    return read_content == item->course || (item->detail && read_content == item->detail->notes) ||
           read_content == item->method;
}

static void find_related(void) {
    related_count = 0;
    const Topic *item = topic();
    const char *code = course()->code;
    int subject = !strcmp(code, "8463") ? 0 : !strcmp(code, "8462") ? 1 : -1;
    if (subject >= 0) {
        const PhysicsEquation *items = subject ? chemistry_equations : physics_equations;
        int count = subject ? chemistry_equation_count : physics_equation_count;
        size_t length = strcspn(item->course, "\n");
        for (int i = 0; i < count && related_count < SEARCH_LIMIT; i++)
            if ((strlen(items[i].section) == length && !strncmp(item->course, items[i].section, length)) ||
                (!subject && strstr(item->title, "Density") && !strcmp(items[i].title, "Density")))
                related_matches[related_count++] = (SearchMatch){.row=i,.equation=true,.chemistry=subject};
    } else if (!strcmp(code, "8461")) {
        const char *name = item->title;
        const char *wanted = strstr(name, "Microscopy") ? "Magnification" : NULL;
        if (wanted) {
            for (int i = 0; i < physics_equation_count; i++)
                if (!strcmp(physics_equations[i].title, wanted))
                    related_matches[related_count++] = (SearchMatch){.row=i,.equation=true};
        }
    } else if (item->method) {
        related_matches[related_count++] = (SearchMatch){course_selection.row,chapter_selection.row,
                                                       topic_selection.row,false,false};
    }
}

static void wrap_topic_reading(void) {
    if (!reading_is_topic()) {
        wrap(read_content, TEXT_WIDTH, false, &read_length);
        return;
    }
    const Topic *item = topic();
    find_related();
    bool science = !strncmp(course()->code, "846", 3);
    if (science) {
        size_t length = strcspn(read_content, "\n");
        if (length < 16) {
            wrapped[read_length++] = (WrappedLine){(int)length,false,read_content};
            if (related_count) {
                wrap("Related equations (TOOLS)", TEXT_WIDTH, true, &read_length);
                for (int i = 0; i < related_count; i++) wrap(match_title(&related_matches[i]), TEXT_WIDTH, false, &read_length);
            }
            const char *notes = read_content + length;
            while (*notes == '\n') notes++;
            wrap("\n", TEXT_WIDTH, false, &read_length);
            wrap(notes, TEXT_WIDTH, false, &read_length);
        } else wrap(read_content, TEXT_WIDTH, false, &read_length);
        if (item->example && !item->method) wrap(item->example, TEXT_WIDTH, false, &read_length);
    } else {
        if (related_count) {
            wrap("Related formulas (TOOLS)", TEXT_WIDTH, true, &read_length);
            for (int i = 0; i < related_count; i++) wrap(match_title(&related_matches[i]), TEXT_WIDTH, false, &read_length);
        }
        wrap(read_content, TEXT_WIDTH, false, &read_length);
    }
}

static void draw_search(void) {
    header(equation_search ? "Search equations" : "Search topics", NULL, true);
    field_entry(7, 27, EADK_SCREEN_WIDTH - 14, &search_query, "Type words, symbols or a spec number", true);
    char info[TEXT_WIDTH + 1];
    snprintf(info, sizeof(info), "%d matches%s", search_total,
             search_total > SEARCH_LIMIT ? " (first 64; refine search)" : "");
    string_at(8, 49, info, Grey, White);
    const int height = 28, top = 66, rows = (FOOTER - top) / height;
    if (search_selection.row < search_selection.first) search_selection.first = search_selection.row;
    if (search_selection.row >= search_selection.first + rows) search_selection.first = search_selection.row - rows + 1;
    for (int row = 0; row < rows && row + search_selection.first < search_count; row++) {
        int i = row + search_selection.first, y = top + row*height;
        const SearchMatch *match = &search_matches[i];
        bool selected = i == search_selection.row;
        eadk_color_t paper = selected ? PaleGold : White;
        rectangle(4, y, EADK_SCREEN_WIDTH - 9, height-1, paper);
        char label[96];
        if (match->equation && match_equation(match)->higher)
            snprintf(label, sizeof(label), "%s (higher only)", match_title(match));
        else snprintf(label, sizeof(label), "%s", match_title(match));
        title_with_tier(8, y, label, TEXT_WIDTH, selected ? Blue : Ink, paper);
        const char *context = match->equation ? (match->chemistry ? "AQA Chemistry" : "AQA Physics") :
                              courses[match->course].title;
        clipped(8, y+14, context, TEXT_WIDTH, Grey, paper);
    }
    if (!search_count) string_at(8, 75, "No matches. Try fewer words.", Grey, White);
    scrollbar(search_selection.first, search_count, rows, top, rows*height);
    footer("ALPHA: type   UP/DOWN: select   OK");
}
