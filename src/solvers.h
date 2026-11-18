#ifndef NUMAI_SOLVERS_H
#define NUMAI_SOLVERS_H

#include "cas.h"

void solve_triangle(const char *const inputs[6], bool degrees, Solution *solution);
void rearrange_physics(const char *equation, const char *subject, Solution *solution);

#endif
