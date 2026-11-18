static void capture_form_reuse(ReuseKind kind, int id) {
    ReuseData *reuse = &history[0].reuse;
    *reuse = (ReuseData){.kind=kind,.id=id,.count=field_count,.degrees=degrees,
                        .course=course_selection.row,.chapter=chapter_selection.row,.topic=topic_selection.row};
    for (int i = 0; i < field_count; i++)
        memcpy(reuse->inputs[i], forms[i].text, EXPRESSION_SIZE);
}

static void form_for(Operation operation, const Topic *item, Page parent);
static void open_tool(ExtraTool selection);
static void open_equation(void);

static bool valid_reuse(const ReuseData *reuse) {
    if (reuse->kind == ReuseNone) return true;
    if (reuse->count < 1 || reuse->count > SCIENCE_VARIABLES) return false;
    switch (reuse->kind) {
        case ReuseCas:
            return reuse->id >= 0 && reuse->id < OperationCount &&
                   reuse->count == ((reuse->id == Definite || reuse->id == FindRoot) ? 3 :
                                    reuse->id == Substitute ? 2 : 1);
        case ReuseTopic: {
            if (reuse->course < 0 || reuse->course >= course_count) return false;
            const Course *course = &courses[reuse->course];
            if (reuse->chapter < 0 || reuse->chapter >= course->count) return false;
            const Chapter *chapter = &course->chapters[reuse->chapter];
            if (reuse->topic < 0 || reuse->topic >= chapter->count) return false;
            const Topic *topic = &chapter->topics[reuse->topic];
            int count = 0;
            while (count < MAX_FIELDS && topic->labels[count]) count++;
            return topic->method && count == reuse->count;
        }
        case ReuseScience: {
            if (reuse->course < 0 || reuse->course > 1 || reuse->id < 0 ||
                reuse->id >= (reuse->course ? chemistry_equation_count : physics_equation_count)) return false;
            const PhysicsEquation *item = &(reuse->course ? chemistry_equations : physics_equations)[reuse->id];
            int subjects = 0;
            for (int i = 0; i < item->count; i++) subjects += item->variables[i].formula != NULL;
            return reuse->subject >= 0 && reuse->subject < subjects && reuse->count == item->count;
        }
        case ReuseExtra:
            return reuse->id >= 0 && reuse->id < ExtraToolCount &&
                   reuse->count == (reuse->id == TriangleSolver ? 6 : reuse->id == TrigSolver ? 3 : 2);
        case ReuseUnit:
            return reuse->id >= 0 && reuse->id < unit_group_count && reuse->count == 1 &&
                   reuse->subject >= 0 && reuse->subject < unit_groups[reuse->id].count &&
                   reuse->topic >= 0 && reuse->topic < unit_groups[reuse->id].count;
        default: return false;
    }
}

static void reuse_history(void) {
    const ReuseData *reuse = &history[history_selection.row].reuse;
    if (reuse->kind == ReuseNone || !valid_reuse(reuse)) {
        pin_notice = "This older entry has no saved inputs.";
        return;
    }
    degrees = reuse->degrees;
    switch (reuse->kind) {
        case ReuseCas:
            form_for((Operation)reuse->id, NULL, HistoryResult);
            break;
        case ReuseTopic:
            course_selection = (Selection){reuse->course,0};
            chapter_selection = (Selection){reuse->chapter,0};
            topic_selection = (Selection){reuse->topic,0};
            form_for(topic()->operation, topic(), HistoryResult);
            break;
        case ReuseScience:
            chemistry_sheet = reuse->course != 0;
            physics_selection = (Selection){reuse->id,0};
            open_equation();
            equation_parent = HistoryResult;
            favourite_origin = equation_from_related = false;
            physics_subject = (Selection){reuse->subject,0};
            for (int i = 0; i < reuse->count; i++) set_field(&physics_fields[i], reuse->inputs[i], false);
            physics_focus = physics_first = 0;
            science_work.answer[0] = 0;
            page = PhysicsForm;
            return;
        case ReuseExtra:
            open_tool((ExtraTool)reuse->id);
            tool_parent = HistoryResult;
            break;
        case ReuseUnit:
            unit_group = (Selection){reuse->id,0};
            unit_from = (Selection){reuse->subject,0};
            unit_to = (Selection){reuse->topic,0};
            set_field(&unit_input, reuse->inputs[0], false);
            unit_input_error = false;
            page = UnitValue;
            return;
        default: return;
    }
    for (int i = 0; i < reuse->count; i++) set_field(&forms[i], reuse->inputs[i], false);
    active_field = form_first = tool_first = 0;
}
