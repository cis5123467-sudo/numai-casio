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
        int direct_count = 0;
        for (int i = 0; i < course_count; i++)
            for (int j = 0; j < courses[i].count; j++) {
                const Chapter *chapter = &courses[i].chapters[j];
                for (int k = 0; k < chapter->count; k++) {
                    const Topic *item = &chapter->topics[k];
                    const char *texts[] = {courses[i].title, courses[i].code, chapter->title,
                                           item->title, item->course, item->method,
                                           item->detail ? item->detail->notes : item->example};
                    SearchMatch match = {i,j,k,false,false};
                    if (matches_query(texts, 4)) {
                        /* Prefer topic names to mentions in chapter summaries. */
                        if (direct_count < SEARCH_LIMIT) {
                            int retained = search_count < SEARCH_LIMIT ? search_count : SEARCH_LIMIT - 1;
                            memmove(search_matches + direct_count + 1, search_matches + direct_count,
                                    (size_t)(retained - direct_count) * sizeof(*search_matches));
                            search_matches[direct_count++] = match;
                            if (search_count < SEARCH_LIMIT) search_count++;
                        }
                        search_total++;
                    } else if (matches_query(texts, 7)) add_search_match(match);
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

static bool is_key_ideas(const char *title) {
    return !strcmp(title, "Key Ideas");
}

static bool section_matches(const char *parent, size_t length, const char *section) {
    return !strncmp(parent, section, length) &&
           (section[length] == '\0' || section[length] == '.');
}

/* References are scoped by the destination course. The sheet reference can
 * point to a whole subsection or a single card within that subsection. */
static bool summary_cross_link(const char *course_code, const char *reference, size_t length,
                               bool chemistry, const PhysicsEquation *equation) {
    static const struct {
        const char *course_code, *summary, *equation_section, *title;
        bool chemistry;
    } links[] = {
        {"8461", "4.1", "4.6.2.5", NULL, false}, /* Microscopy. */
        {"8461", "4.4", "4.6.1.1", "Mean rate from gas volume", true},
        {"8461", "RP", "4.6.2.5", NULL, false},
        {"8461", "RP", "4.6.1.1", "Mean rate from gas volume", true},
        {"8463", "4.1", "4.5.1.3", NULL, false}, /* Weight, work and springs. */
        {"8463", "4.1", "4.5.2", NULL, false},
        {"8463", "4.1", "4.5.3", NULL, false},
        {"8463", "4.2", "4.7.3.4", "Ideal transformer power", false},
        {"8463", "4.3", "4.1.1.3", NULL, false},
        {"8463", "4.4", "4.1.1.5", "Neutron number", true},
        {"8463", "4.5", "4.1.1.2", NULL, false},
        {"8463", "4.9", "4.1.1.2", NULL, false},
        {"8463", "4.9", "4.2.1.2", NULL, false},
        {"8463", "4.9", "4.5.6.2.2", NULL, false},
        {"8463", "4.9", "4.6.1.2", NULL, false},
        {"8463", "RP", "4.1.1.3", NULL, false},
        {"8463", "RP", "4.2.1.3", NULL, false},
        {"8463", "RP", "4.2.4.2", NULL, false},
        {"8463", "RP", "4.3.1.1", NULL, false},
        {"8463", "RP", "4.5.3", NULL, false},
        {"8463", "RP", "4.5.6.2.2", NULL, false},
        {"8463", "RP", "4.6.1.2", NULL, false},
        {"8462", "4.4", "4.3.4", NULL, true},
        {"8462", "4.10", "4.3.2.5", NULL, true},
        {"8462", "4.11", "4.3.1.1", NULL, true},
        {"8462", "4.11", "4.3.2.1", "Moles, mass and molar mass", true},
        {"8462", "4.11", "4.5.1.3", NULL, true},
        {"8462", "RP", "4.4.2.5", NULL, true},
        {"8462", "RP", "4.3.2.5", NULL, true},
        {"8462", "RP", "4.6.1.1", NULL, true},
        {"8462", "RP", "4.8.1.3", NULL, true},
    };
    if (chemistry && length == 1 && reference[0] == '3' &&
        !strcmp(equation->title, "Uncertainty from repeats")) return true;
    for (unsigned i = 0; i < sizeof(links) / sizeof(*links); i++) {
        if (links[i].chemistry == chemistry && !strcmp(links[i].course_code, course_code) &&
            strlen(links[i].summary) == length && !strncmp(reference, links[i].summary, length) &&
            !strcmp(equation->section, links[i].equation_section) &&
            (!links[i].title || !strcmp(equation->title, links[i].title)))
            return true;
    }
    return false;
}

static void find_related(void) {
    related_count = 0;
    const Topic *item = topic();
    const char *code = course()->code;
    int subject = !strcmp(code, "8463") ? 0 : !strcmp(code, "8462") ? 1 : -1;
    if (is_key_ideas(item->title) && !strncmp(code, "846", 3)) {
        size_t length = strcspn(item->course, "\n");
        for (int pass = 0; pass < 2; pass++) {
            bool chemistry = subject == 1 ? pass == 0 : pass == 1;
            const PhysicsEquation *items = chemistry ? chemistry_equations : physics_equations;
            int count = chemistry ? chemistry_equation_count : physics_equation_count;
            for (int i = 0; i < count && related_count < SEARCH_LIMIT; i++) {
                bool direct = subject >= 0 && chemistry == (subject == 1) &&
                              section_matches(item->course, length, items[i].section);
                if (direct || summary_cross_link(code, item->course, length, chemistry, &items[i]))
                    related_matches[related_count++] = (SearchMatch){.row=i,.equation=true,.chemistry=chemistry};
            }
        }
    } else if (subject >= 0) {
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

static void wrap_organic_examples(const Topic *item) {
    if (strcmp(course()->code, "8462")) return;
    size_t section_len = strcspn(item->course, "\n");
    bool cracking = !strcmp(item->title, "Cracking and alkenes");
    bool combustion = !strcmp(item->title, "Hydrocarbon trends and burning");
    bool alkene_reactions = !strcmp(item->title, "Alkene reactions");
    bool addition = !strcmp(item->title, "Addition polymers");
    bool weak_acid = !strcmp(item->title, "Carboxylic acid ionisation (higher only)");
    for (int f = 0; f < organic_family_count; f++) {
        const OrganicFamily *family = &organic_families[f];
        for (int m = family->first; m < family->first + family->count; m++) {
            const OrganicMolecule *molecule = &organic_molecules[m];
            bool matches = strlen(molecule->section) == section_len &&
                           !strncmp(item->course, molecule->section, section_len);
            if (weak_acid) matches = !strcmp(molecule->name, "Ethanoic acid");
            if ((cracking || alkene_reactions || addition) && !strcmp(molecule->name, "Ethene"))
                matches = true;
            if (combustion && !strcmp(molecule->name, "Propane")) matches = true;
            if (m == OrganicMethylpropane) continue; /* Shown beside butane in these notes. */
            if (matches && read_length < WRAP_LIMIT)
                wrapped[read_length++] = (WrappedLine){.length=m == OrganicButane ? OrganicIsomerComparison : m};
        }
    }
    if (!strcmp(item->title, "Crude oil and alkanes"))
        wrap("Butane and methylpropane share C4H10. Butane has a straight chain and methylpropane has a branch.",
             TEXT_WIDTH, false, &read_length);
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
            wrapped[read_length++] = (WrappedLine){.length=(int)length,.source=read_content};
            if (related_count) {
                wrap("Related equations (TOOLS)", TEXT_WIDTH, true, &read_length);
                for (int i = 0; i < related_count && read_length < WRAP_LIMIT; i++) {
                    const PhysicsEquation *equation = match_equation(&related_matches[i]);
                    if (equation->higher) {
                        wrapped[read_length++] = (WrappedLine){.higher=true,.source=equation->title};
                    } else wrap(equation->title, TEXT_WIDTH, false, &read_length);
                }
            }
            const char *notes = read_content + length;
            while (*notes == '\n') notes++;
            wrap("\n", TEXT_WIDTH, false, &read_length);
            wrap(notes, TEXT_WIDTH, false, &read_length);
        } else wrap(read_content, TEXT_WIDTH, false, &read_length);
        wrap_organic_examples(item);
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
