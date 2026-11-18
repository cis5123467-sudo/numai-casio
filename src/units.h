#ifndef NUMAI_UNITS_H
#define NUMAI_UNITS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    const char *symbol;
    double scale, offset;
} Unit;

typedef struct {
    const char *name;
    const Unit *units;
    int count;
} UnitGroup;

extern const UnitGroup unit_groups[];
extern const int unit_group_count;

bool unit_convert(double value, const Unit *from, const Unit *to, double *result);
void unit_working(char *output, size_t size, double value, const Unit *from,
                  const Unit *to, double result);
bool quantity_read(const char *input, const char *expected, double *value,
                   char *working, size_t size);
#endif
