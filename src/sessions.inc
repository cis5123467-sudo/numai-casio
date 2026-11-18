enum { SessionScriptSize = 10240 };
static const char session_owner[] = "# NumAI session 1\n";
static ScriptStore session_store;
static unsigned session_sequence;
static bool session_dirty;
static Session session_buffer;
static char session_script[SessionScriptSize];

typedef struct {
    char *cursor, *end;
    bool valid;
} SessionWriter;

static void write_session_bytes(SessionWriter *out, const char *text, size_t length) {
    if (!out->valid || length > (size_t)(out->end - out->cursor)) {
        out->valid = false;
        return;
    }
    memcpy(out->cursor, text, length);
    out->cursor += length;
}

static void write_session_string(SessionWriter *out, const char *text, char separator) {
    for (; out->valid && *text; text++) {
        if (*text == '\n' || *text == '|' || *text == '\\') {
            const char escaped[] = {'\\', *text == '\n' ? 'n' : *text};
            write_session_bytes(out, escaped, sizeof(escaped));
        } else write_session_bytes(out, text, 1);
    }
    write_session_bytes(out, &separator, 1);
}

static bool encode_session(unsigned sequence) {
    SessionWriter out = {session_script, session_script + sizeof(session_script) - 1, true};
    char numbers[144];
    unsigned preferences = (unsigned)degrees | (unsigned)decimal << 1 | (unsigned)show_steps << 2;
    int length = snprintf(numbers, sizeof(numbers), "# %u|%u|%d|%d|%d\n# ", sequence,
                          preferences, decimal_places, calc_count, history_count);
    write_session_bytes(&out, session_owner, sizeof(session_owner) - 1);
    write_session_bytes(&out, numbers, (size_t)length);
    write_session_string(&out, ans, '\n');

    for (int i = 0; i < calc_count; i++) {
        const CalcEntry *entry = &calculations[i];
        const CalculationValue *value = &entry->result;
        length = snprintf(numbers, sizeof(numbers), "# %.17g|%.17g|%d|%d|%d|%d|%d|%d|%d|%d|",
                          value->value, value->argument, value->numerator, value->denominator,
                          value->radicand, value->argument_n, value->argument_d, value->argument_rad,
                          value->kind, value->degrees);
        if (length < 0 || (size_t)length >= sizeof(numbers)) return false;
        write_session_bytes(&out, numbers, (size_t)length);
        write_session_string(&out, entry->input, '|');
        write_session_string(&out, value->exact, '\n');
    }
    for (int i = 0; i < history_count; i++) {
        const HistoryEntry *entry = &history[i];
        length = snprintf(numbers, sizeof(numbers), "# %d|%d|", entry->operation, entry->solution.ok);
        write_session_bytes(&out, numbers, (size_t)length);
        write_session_string(&out, entry->title, '|');
        write_session_string(&out, entry->question, '|');
        write_session_string(&out, entry->solution.steps, '|');
        write_session_string(&out, entry->solution.answer, '\n');
    }
    CasVariables variables;
    cas_get_variables(&variables);
    for (unsigned i = 0; i < CAS_VARIABLE_COUNT; i++) {
        if (!variables.set[i]) continue;
        length = snprintf(numbers, sizeof(numbers), "# %u|%.17g\n", i, variables.value[i]);
        write_session_bytes(&out, numbers, (size_t)length);
    }
    // Optional tagged records keep v0.1.1 sessions readable by this version.
    for (int i = 0; i < history_count; i++) {
        const ReuseData *reuse = &history[i].reuse;
        if (reuse->kind == ReuseNone) continue;
        length = snprintf(numbers, sizeof(numbers), "# R|%d|%d|%d|%d|%d|%d|%d|%d|%d",
                          i, reuse->kind, reuse->id, reuse->subject, reuse->course,
                          reuse->chapter, reuse->topic, reuse->degrees, reuse->count);
        write_session_bytes(&out, numbers, (size_t)length);
        write_session_bytes(&out, "|", 1);
        for (int j = 0; j < reuse->count; j++)
            write_session_string(&out, reuse->inputs[j], j + 1 == reuse->count ? '\n' : '|');
    }
    write_session_bytes(&out, "# End\n", 6);
    if (!out.valid) return false;
    // Padding keeps subsequent writes in place without relocating other scripts.
    while (out.cursor < out.end) {
        char *line = out.cursor;
        *out.cursor++ = '#';
        while (out.cursor < out.end && out.cursor - line < 72) *out.cursor++ = ' ';
        if (out.cursor < out.end) *out.cursor++ = '\n';
    }
    *out.end = 0;
    return true;
}

static bool read_session_string(const char **cursor, const char *end, char *text, size_t size,
                                char separator) {
    size_t length = 0;
    while (*cursor < end) {
        char c = *(*cursor)++;
        if (c == separator) {
            text[length] = 0;
            return true;
        }
        if (!c || c == '\n' || length + 1 >= size) return false;
        if (c == '\\') {
            if (*cursor == end) return false;
            c = *(*cursor)++;
            if (c == 'n') c = '\n';
            else if (c != '\\' && c != '|') return false;
        }
        text[length++] = c;
    }
    return false;
}

static bool read_session_int(const char **cursor, const char *end, int *value, char separator) {
    char text[18], *tail;
    if (!read_session_string(cursor, end, text, sizeof(text), separator) || !*text) return false;
    long parsed = strtol(text, &tail, 10);
    if (*tail || parsed < INT32_MIN || parsed > INT32_MAX) return false;
    *value = (int)parsed;
    return true;
}

static bool read_session_double(const char **cursor, const char *end, double *value, char separator) {
    char text[36], *tail;
    if (!read_session_string(cursor, end, text, sizeof(text), separator) || !*text) return false;
    double parsed = strtod(text, &tail);
    if (*tail || !isfinite(parsed)) return false;
    *value = parsed;
    return true;
}

static bool session_label(const char **cursor, const char *end) {
    if (end - *cursor < 2 || (*cursor)[0] != '#' || (*cursor)[1] != ' ') return false;
    *cursor += 2;
    return true;
}

static bool decode_session(const ScriptRecord *record, Session *session) {
    if (record->size != SessionScriptSize || record->source[record->size - 1] ||
        strncmp(record->source, session_owner, sizeof(session_owner) - 1)) return false;
    const char *cursor = record->source + sizeof(session_owner) - 1;
    const char *end = record->source + record->size;
    int sequence, flags, decimals, calcs, entries;
    if (!session_label(&cursor, end) ||
        !read_session_int(&cursor, end, &sequence, '|') || sequence <= 0 ||
        !read_session_int(&cursor, end, &flags, '|') || flags < 0 || flags > 7 ||
        !read_session_int(&cursor, end, &decimals, '|') || decimals < 0 || decimals > 10 ||
        !read_session_int(&cursor, end, &calcs, '|') || calcs < 0 || calcs > CALCULATION_LIMIT ||
        !read_session_int(&cursor, end, &entries, '\n') || entries < 0 || entries > HISTORY_LIMIT ||
        !session_label(&cursor, end) ||
        !read_session_string(&cursor, end, session->ans, sizeof(session->ans), '\n')) return false;

    for (int i = 0; i < calcs; i++) {
        CalcEntry *entry = &session->calculations[i];
        CalculationValue *value = &entry->result;
        int kind, angle;
        if (!session_label(&cursor, end) ||
            !read_session_double(&cursor, end, &value->value, '|') ||
            !read_session_double(&cursor, end, &value->argument, '|') ||
            !read_session_int(&cursor, end, &value->numerator, '|') ||
            !read_session_int(&cursor, end, &value->denominator, '|') ||
            !read_session_int(&cursor, end, &value->radicand, '|') ||
            !read_session_int(&cursor, end, &value->argument_n, '|') ||
            !read_session_int(&cursor, end, &value->argument_d, '|') ||
            !read_session_int(&cursor, end, &value->argument_rad, '|') ||
            !read_session_int(&cursor, end, &kind, '|') || kind < ExtraNone || kind > ExtraTan ||
            !read_session_int(&cursor, end, &angle, '|') || (angle != 0 && angle != 1) ||
            !read_session_string(&cursor, end, entry->input, sizeof(entry->input), '|') ||
            !read_session_string(&cursor, end, value->exact, sizeof(value->exact), '\n')) return false;
        if (value->numerator == INT32_MIN || value->denominator < 0 ||
            value->argument_n == INT32_MIN || value->argument_d < 0 ||
            value->radicand < 0 || value->argument_rad < 0) return false;
        value->kind = (CalculationKind)kind;
        value->degrees = angle;
        value->numeric = true;
    }
    for (int i = 0; i < entries; i++) {
        HistoryEntry *entry = &session->history[i];
        int operation, ok;
        if (!session_label(&cursor, end) ||
            !read_session_int(&cursor, end, &operation, '|') || operation < 0 || operation >= OperationCount ||
            !read_session_int(&cursor, end, &ok, '|') || (ok != 0 && ok != 1) ||
            !read_session_string(&cursor, end, entry->title, sizeof(entry->title), '|') ||
            !read_session_string(&cursor, end, entry->question, sizeof(entry->question), '|') ||
            !read_session_string(&cursor, end, entry->solution.steps, sizeof(entry->solution.steps), '|') ||
            !read_session_string(&cursor, end, entry->solution.answer, sizeof(entry->solution.answer), '\n')) return false;
        entry->operation = (Operation)operation;
        entry->solution.ok = ok;
    }
    while (end - cursor >= 6 && memcmp(cursor, "# End\n", 6)) {
        if (end - cursor >= 4 && !memcmp(cursor, "# R|", 4)) {
            cursor += 4;
            int index, kind, angle, id, subject, course, chapter, topic, count;
            if (!read_session_int(&cursor, end, &index, '|') || index < 0 || index >= entries ||
                !read_session_int(&cursor, end, &kind, '|') || kind <= ReuseNone || kind > ReuseUnit ||
                !read_session_int(&cursor, end, &id, '|') ||
                !read_session_int(&cursor, end, &subject, '|') ||
                !read_session_int(&cursor, end, &course, '|') ||
                !read_session_int(&cursor, end, &chapter, '|') ||
                !read_session_int(&cursor, end, &topic, '|') ||
                !read_session_int(&cursor, end, &angle, '|') || (angle != 0 && angle != 1) ||
                !read_session_int(&cursor, end, &count, '|') || count < 1 || count > SCIENCE_VARIABLES) return false;
            ReuseData *reuse = &session->history[index].reuse;
            *reuse = (ReuseData){.kind=(ReuseKind)kind,.id=id,.subject=subject,.course=course,
                                .chapter=chapter,.topic=topic,.count=count,.degrees=angle};
            for (int j = 0; j < count; j++)
                if (!read_session_string(&cursor, end, reuse->inputs[j], EXPRESSION_SIZE,
                                         j + 1 == count ? '\n' : '|')) return false;
            if (!valid_reuse(reuse)) return false;
            continue;
        }
        int index;
        if (!session_label(&cursor, end) ||
            !read_session_int(&cursor, end, &index, '|') || index < 0 || index >= CAS_VARIABLE_COUNT ||
            !read_session_double(&cursor, end, &session->variables.value[index], '\n')) return false;
        session->variables.set[index] = true;
    }
    if (end - cursor < 6) return false;
    session->calc_count = calcs;
    session->history_count = entries;
    session->sequence = (unsigned)sequence;
    session->preferences = flags;
    session->decimal_places = decimals;
    return true;
}

static bool valid_session_name(const char *name, size_t length) {
    return length && length < SESSION_NAME_SIZE &&
           strspn(name, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") == length;
}

static void session_filename(char output[SESSION_NAME_SIZE + 11], const char *name) {
    snprintf(output, SESSION_NAME_SIZE + 11, "session_%.*s.py", SESSION_NAME_SIZE - 1, name);
}

static bool save_active_session(void) {
    if (!session_store.records) return false;
    char file[SESSION_NAME_SIZE + 11];
    session_filename(file, session_names[active_session]);
    unsigned sequence = session_sequence + 1;
    if (sequence > INT32_MAX || !encode_session(sequence) ||
        !script_record_save(session_store, file, session_owner, session_script, sizeof(session_script))) {
        return false;
    }
    session_sequence = sequence;
    session_exists[active_session] = true;
    session_dirty = false;
    return true;
}

static void session_autosave(void) {
    if (!session_store.records) return;
    session_dirty = true;
    if (!save_active_session()) pin_notice = "Session unsaved: check USB storage.";
}

static bool read_session_file(int index) {
    memset(&session_buffer, 0, sizeof(session_buffer));
    if (!session_exists[index]) return true;
    char name[SESSION_NAME_SIZE + 11];
    session_filename(name, session_names[index]);
    size_t position = 0;
    ScriptRecord record;
    while (script_record_next(session_store, &position, &record))
        if (!strcmp(record.name, name)) return decode_session(&record, &session_buffer);
    return false;
}

static bool open_session(int index) {
    if (session_dirty && !save_active_session()) {
        pin_notice = "Session unsaved: check USB storage.";
        return false;
    }
    // Reopening the active session can simply return to its calculation screen.
    if (index != active_session) {
        if (!read_session_file(index)) {
            pin_notice = "Unable to read that session.";
            return false;
        }
        restore_session(&session_buffer);
        active_session = index;
    }
    page = Prompt;
    return true;
}

static void load_sessions(void) {
    session_store = calculator_script_store();
    active_session = 0;
    session_sequence = 0;
    session_dirty = false;
    memset(session_exists, 0, sizeof(session_exists));
    size_t position = 0;
    ScriptRecord record;
    session_count = 0;
    while (session_count < SESSION_LIMIT && script_record_next(session_store, &position, &record)) {
        if (strncmp(record.name, "session_", 8)) continue;
        const char *name = record.name + 8;
        size_t length = strlen(name);
        if (length <= 3 || length - 3 >= SESSION_NAME_SIZE || strcmp(name + length - 3, ".py")) continue;
        char *destination = session_names[session_count];
        memcpy(destination, name, length - 3);
        destination[length - 3] = 0;
        memset(&session_buffer, 0, sizeof(session_buffer));
        if (!valid_session_name(destination, length - 3) || !decode_session(&record, &session_buffer)) continue;
        if (session_buffer.sequence >= session_sequence) {
            active_session = session_count;
            session_sequence = session_buffer.sequence;
        }
        session_exists[session_count++] = true;
    }
    if (!session_count) {
        strcpy(session_names[0], "default");
        session_count = 1;
    }
    if (!read_session_file(active_session) || !session_exists[active_session]) {
        memset(&session_buffer, 0, sizeof(session_buffer));
        session_buffer.decimal_places = 5;
        session_buffer.preferences = 5;
    }
    decimal_places = session_buffer.decimal_places;
    degrees = (session_buffer.preferences & 1) != 0;
    decimal = (session_buffer.preferences & 2) != 0;
    show_steps = (session_buffer.preferences & 4) != 0;
    restore_session(&session_buffer);
}
