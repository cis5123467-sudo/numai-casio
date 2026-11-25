/* Backbone atoms sit on one horizontal line. Remaining valences are filled
 * explicitly with H, using unused positions around each carbon. */
enum { OrganicDiagramHeight = 122, AtomHalfWidth = 6, AtomHalfHeight = 8 };

static void organic_atom(int x, int y, char symbol, eadk_color_t paper) {
    char label[] = {symbol, '\0'};
    draw_text(x - casio_width(label, -1, false, true)/2, y - 5, label, Ink, paper, true);
}

static void organic_horizontal(int left, int right, int y, bool double_bond) {
    int width = right - left - 2 * AtomHalfWidth;
    rectangle(left + AtomHalfWidth, y - (double_bond ? 2 : 0), width, 1, Ink);
    if (double_bond) rectangle(left + AtomHalfWidth, y + 2, width, 1, Ink);
}

static void organic_vertical(int x, int top, int bottom, bool double_bond) {
    int height = bottom - top - 2 * AtomHalfHeight;
    rectangle(x - (double_bond ? 2 : 0), top + AtomHalfHeight, 1, height, Ink);
    if (double_bond) rectangle(x + 2, top + AtomHalfHeight, 1, height, Ink);
}

static void draw_organic_structure(const OrganicMolecule *molecule, int centre, int top,
                                   bool compact, eadk_color_t paper) {
    int spacing = compact ? 28 : 56;
    int hydrogen_gap = compact ? 22 : 24;
    int count = (int)strlen(molecule->backbone);
    int start = centre - (count - 1) * spacing / 2;
    int y = top + 84;

    for (int i = 0; i < count; i++) {
        int x = start + i * spacing;
        bool branch = molecule->branch_atom == i + 1;
        if (i + 1 < count)
            organic_horizontal(x, x + spacing, y, molecule->double_bond == i + 1);
        organic_atom(x, y, molecule->backbone[i], paper);
        if (molecule->backbone[i] != 'C') continue;

        int hydrogen = 4 - (i > 0) - (i + 1 < count);
        if (molecule->double_bond && (molecule->double_bond == i || molecule->double_bond == i + 1))
            hydrogen--;
        if (branch) {
            int branch_y = y - (compact ? 40 : 30);
            organic_vertical(x, branch_y, y, molecule->branch == 'O');
            organic_atom(x, branch_y, molecule->branch, paper);
            hydrogen -= molecule->branch == 'O' ? 2 : 1;
            if (molecule->branch == 'C') {
                organic_vertical(x, branch_y - hydrogen_gap, branch_y, false);
                organic_horizontal(x - hydrogen_gap, x, branch_y, false);
                organic_horizontal(x, x + hydrogen_gap, branch_y, false);
                organic_atom(x, branch_y - hydrogen_gap, 'H', paper);
                organic_atom(x - hydrogen_gap, branch_y, 'H', paper);
                organic_atom(x + hydrogen_gap, branch_y, 'H', paper);
            }
        } else if (hydrogen > 0) {
            organic_vertical(x, y - hydrogen_gap, y, false);
            organic_atom(x, y - hydrogen_gap, 'H', paper);
            hydrogen--;
        }
        if (hydrogen > 0) {
            organic_vertical(x, y, y + hydrogen_gap, false);
            organic_atom(x, y + hydrogen_gap, 'H', paper);
            hydrogen--;
        }
        if (hydrogen > 0 && i == 0) {
            organic_horizontal(x - hydrogen_gap, x, y, false);
            organic_atom(x - hydrogen_gap, y, 'H', paper);
            hydrogen--;
        }
        if (hydrogen > 0 && i == count - 1) {
            organic_horizontal(x, x + hydrogen_gap, y, false);
            organic_atom(x + hydrogen_gap, y, 'H', paper);
        }
    }
}

static void draw_organic_diagram(const OrganicMolecule *molecule, int top, eadk_color_t paper) {
    draw_text(11, top + 2, molecule->name, Blue, paper, true);
    MathCanvas canvas = {math_text, rectangle, Ink, paper};
    paint_math(molecule->formula, 110, EADK_SCREEN_WIDTH - 115, top + 10, &canvas);
    draw_organic_structure(molecule, EADK_SCREEN_WIDTH / 2, top, false, paper);
}

static void draw_organic_comparison(int top) {
    const OrganicMolecule *butane = &organic_molecules[OrganicButane];
    const OrganicMolecule *methylpropane = &organic_molecules[OrganicMethylpropane];
    draw_text(11, top + 2, butane->name, Blue, White, true);
    draw_text(EADK_SCREEN_WIDTH / 2 + 9, top + 2, methylpropane->name, Blue, White, true);
    rectangle(EADK_SCREEN_WIDTH / 2, top + 19, 1, OrganicDiagramHeight - 25, Line);
    draw_organic_structure(butane, EADK_SCREEN_WIDTH / 4, top, true, White);
    draw_organic_structure(methylpropane, EADK_SCREEN_WIDTH * 3 / 4, top, true, White);
}

static void draw_organic_detail(void) {
    const OrganicFamily *family = &organic_families[organic_family.row];
    int index = family->first + organic_choice.row;
    const OrganicMolecule *molecule = &organic_molecules[index];
    header("Displayed formula", NULL, false);
    draw_organic_diagram(molecule, 29, White);
    clipped(11, 155, family->name, TEXT_WIDTH, Grey, White);
    if (index == OrganicButane || index == OrganicMethylpropane) {
        string_at(11, 173, "Butane and methylpropane share a", Ink, White);
        string_at(11, 188, "formula and have different structures.", Ink, White);
    }
    footer("OK / CATALOG: topic notes   BACK");
}
