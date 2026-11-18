/* Independent, unmodified content reference from the requested NumWorks tag. */
#include "topics.h"
#define COUNT(a) ((int)(sizeof(a)/sizeof(*(a))))
#define CH(t,a) {t,a,COUNT(a)}
#include "../data/aqa_catalog_numworks_0.1.2-r1.inc"
const Course pinned_sciences[] = {
    {"AQA Physics","8463",aqa_physics,COUNT(aqa_physics)},
    {"AQA Biology","8461",aqa_biology,COUNT(aqa_biology)},
    {"AQA Chemistry","8462",aqa_chemistry,COUNT(aqa_chemistry)}
};
