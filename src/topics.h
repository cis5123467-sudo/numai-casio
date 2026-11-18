#ifndef NUMAI_TOPICS_H
#define NUMAI_TOPICS_H
#include "cas.h"

#define MAX_FIELDS 4
#define EXTRA_EXAMPLES 2

typedef struct { const char *title, *working; } WorkedExample;
typedef struct { const char *notes; WorkedExample examples[EXTRA_EXAMPLES]; } MathsDetail;
typedef struct {
    const char *title, *course, *method, *example;
    Operation operation;
    const char *formula;
    const char *labels[MAX_FIELDS], *values[MAX_FIELDS];
    const MathsDetail *detail;
} Topic;

typedef struct { const char *title; const Topic *topics; int count; } Chapter;
typedef struct { const char *title, *code; const Chapter *chapters; int count; } Course;

extern const Course courses[];
extern const int course_count;
#endif
