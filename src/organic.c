#include "organic.h"

enum { AlkaneCount = 5, AlkeneCount = 4, AlcoholCount = 4, AcidCount = 4, EsterCount = 1 };
enum { AlkeneFirst = AlkaneCount, AlcoholFirst = AlkeneFirst + AlkeneCount,
       AcidFirst = AlcoholFirst + AlcoholCount, EsterFirst = AcidFirst + AcidCount };

const OrganicMolecule organic_molecules[] = {
    {"Methane",       "CH_{4}",        "4.7.1.1", "C",      0, 0, 0},
    {"Ethane",        "C_{2}H_{6}",    "4.7.1.1", "CC",     0, 0, 0},
    {"Propane",       "C_{3}H_{8}",    "4.7.1.1", "CCC",    0, 0, 0},
    [OrganicButane] =
    {"Butane",        "C_{4}H_{10}",   "4.7.1.1", "CCCC",   0, 0, 0},
    [OrganicMethylpropane] =
    {"Methylpropane", "C_{4}H_{10}",   "4.7.1.1", "CCC",    0, 2, 'C'},

    {"Ethene",        "C_{2}H_{4}",    "4.7.2.1", "CC",     1, 0, 0},
    {"Propene",       "C_{3}H_{6}",    "4.7.2.1", "CCC",    1, 0, 0},
    {"But-1-ene",     "C_{4}H_{8}",    "4.7.2.1", "CCCC",   1, 0, 0},
    {"Pent-1-ene",    "C_{5}H_{10}",   "4.7.2.1", "CCCCC",  1, 0, 0},

    {"Methanol",       "CH_{4}O",       "4.7.2.3", "COH",    0, 0, 0},
    {"Ethanol",        "C_{2}H_{6}O",   "4.7.2.3", "CCOH",   0, 0, 0},
    {"Propan-1-ol",    "C_{3}H_{8}O",   "4.7.2.3", "CCCOH",  0, 0, 0},
    {"Butan-1-ol",     "C_{4}H_{10}O",  "4.7.2.3", "CCCCOH", 0, 0, 0},

    {"Methanoic acid", "CH_{2}O_{2}",      "4.7.2.4", "COH",    0, 1, 'O'},
    {"Ethanoic acid",  "C_{2}H_{4}O_{2}",  "4.7.2.4", "CCOH",   0, 2, 'O'},
    {"Propanoic acid", "C_{3}H_{6}O_{2}",  "4.7.2.4", "CCCOH",  0, 3, 'O'},
    {"Butanoic acid",  "C_{4}H_{8}O_{2}",  "4.7.2.4", "CCCCOH", 0, 4, 'O'},

    {"Ethyl ethanoate","C_{4}H_{8}O_{2}",  "4.7.2.4", "CCOCC",  0, 2, 'O'},
};

const OrganicFamily organic_families[] = {
    {"Alkanes",          0,            AlkaneCount},
    {"Alkenes",          AlkeneFirst,  AlkeneCount},
    {"Alcohols",         AlcoholFirst, AlcoholCount},
    {"Carboxylic acids", AcidFirst,    AcidCount},
    {"Esters",           EsterFirst,   EsterCount},
};

const int organic_family_count = sizeof(organic_families) / sizeof(*organic_families);
