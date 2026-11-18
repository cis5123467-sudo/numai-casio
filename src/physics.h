#ifndef NUMAI_PHYSICS_H
#define NUMAI_PHYSICS_H

#include <stdbool.h>
#include <stddef.h>

#define SCIENCE_VARIABLES 6
#define SCIENCE_REFERENCE_SIZE 4096
#define SCIENCE_WORD_SIZE 432
#define SCIENCE_SUBSTITUTION_SIZE 220
#define SCIENCE_CONVERSION_SIZE 400
#define SCIENCE_STEPS_SIZE 300

enum {
    PhysicsNonnegative = 1, PhysicsPositive = 2, PhysicsEfficiency = 4,
    PhysicsTurns = 8, PhysicsBothSigns = 16, ScienceWhole = 32,
    SciencePercent = 64, ScienceOptional = 128
};

typedef struct {
    const char *symbol, *name, *unit, *formula;
    unsigned flags;
} PhysicsVariable;

typedef struct {
    const char *title, *topic, *section, *formula, *uses, *example;
    bool higher;
    int count;
    PhysicsVariable variables[SCIENCE_VARIABLES];
    void (*steps)(int subject, const double values[SCIENCE_VARIABLES], char *output, size_t size);
} PhysicsEquation;

typedef struct {
    char answer[112];
    char substituted[SCIENCE_SUBSTITUTION_SIZE];
    char conversions[SCIENCE_CONVERSION_SIZE];
    char steps[SCIENCE_STEPS_SIZE];
} ScienceWorking;

extern const PhysicsEquation physics_equations[];
extern const int physics_equation_count;
extern const PhysicsEquation chemistry_equations[];
extern const int chemistry_equation_count;

void physics_word_equation(const PhysicsEquation *equation, char output[SCIENCE_WORD_SIZE]);
void physics_subject_equation(const PhysicsEquation *equation, int subject, char *output, size_t size);
void physics_reference(const PhysicsEquation *equation, char output[SCIENCE_REFERENCE_SIZE]);
bool physics_reference_heading(const char *text);
bool physics_solve(const PhysicsEquation *equation, int subject,
                   const char *const values[SCIENCE_VARIABLES], ScienceWorking *working);
#endif
