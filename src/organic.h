#ifndef NUMAI_ORGANIC_H
#define NUMAI_ORGANIC_H

typedef struct {
    const char *name;
    const char *formula;
    const char *section;
    const char *backbone;
    int double_bond; /* One-based bond index. Zero means all single. */
    int branch_atom; /* One-based atom index above which to draw the branch. */
    char branch;     /* C for methyl, O for a double-bonded oxygen. */
} OrganicMolecule;

typedef struct {
    const char *name;
    int first, count;
} OrganicFamily;

enum { OrganicButane = 3, OrganicMethylpropane = 4, OrganicIsomerComparison = -1 };

extern const OrganicMolecule organic_molecules[];
extern const OrganicFamily organic_families[];
extern const int organic_family_count;

#endif
