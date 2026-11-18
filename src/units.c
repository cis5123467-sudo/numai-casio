#include "units.h"
#include "cas.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define U(symbol, scale) {symbol, scale, 0}
#define GROUP(name, array) {name, array, sizeof(array)/sizeof(*(array))}

static const Unit length[] = {U("nm",1e-9),U("um",1e-6),U("mm",0.001),U("cm",0.01),U("dm",0.1),U("m",1),U("km",1000)};
static const Unit area[] = {U("mm^2",1e-6),U("cm^2",1e-4),U("dm^2",0.01),U("m^2",1),U("km^2",1e6)};
static const Unit volume[] = {U("mm^3",1e-9),U("cm^3",1e-6),U("dm^3",0.001),U("m^3",1),
                              U("uL",1e-9),U("mL",1e-6),U("cL",1e-5),U("dL",1e-4),U("L",0.001)};
static const Unit mass[] = {U("ug",1e-9),U("mg",1e-6),U("g",0.001),U("kg",1),U("t",1000)};
static const Unit time_units[] = {U("us",1e-6),U("ms",0.001),U("s",1),U("min",60),U("h",3600),U("days",86400)};
static const Unit speed[] = {U("cm/s",0.01),U("m/s",1),U("km/h",1.0/3.6)};
static const Unit acceleration[] = {U("cm/s^2",0.01),U("m/s^2",1),U("N/kg",1)};
static const Unit pressure[] = {U("Pa",1),U("kPa",1000),U("MPa",1e6),U("bar",1e5),U("atm",101325)};
static const Unit energy[] = {U("mJ",0.001),U("J",1),U("kJ",1000),U("MJ",1e6),U("Wh",3600),U("kWh",3.6e6)};
static const Unit temperature[] = {{"degC",1,273.15}, U("K",1), {"degF",5.0/9.0,255.37222222222222}};
static const Unit temperature_change[] = {U("C or K",1),U("dC",1),U("dK",1),U("dF",5.0/9.0)};
static const Unit current[] = {U("uA",1e-6),U("mA",0.001),U("A",1)};
static const Unit voltage[] = {U("mV",0.001),U("V",1),U("kV",1000)};
static const Unit charge[] = {U("uC",1e-6),U("mC",0.001),U("C",1),U("Ah",3600),U("mAh",3.6)};
static const Unit resistance[] = {U("ohm",1),U("kohm",1000),U("Mohm",1e6)};
static const Unit power[] = {U("mW",0.001),U("W",1),U("kW",1000),U("MW",1e6)};
static const Unit force[] = {U("mN",0.001),U("N",1),U("kN",1000)};
static const Unit frequency[] = {U("Hz",1),U("kHz",1000),U("MHz",1e6),U("GHz",1e9)};
static const Unit density[] = {U("kg/m^3",1),U("g/cm^3",1000),U("g/mL",1000),U("kg/dm^3",1000)};
static const Unit amount[] = {U("umol",1e-6),U("mmol",0.001),U("mol",1)};
static const Unit molar_mass[] = {U("mg/mol",0.001),U("g/mol",1),U("kg/mol",1000)};
static const Unit mass_concentration[] = {U("mg/mL",1),U("mg/L",0.001),U("g/L",1),
                                          U("g/dm^3",1),U("g/cm^3",1000),U("kg/m^3",1)};
static const Unit molar_concentration[] = {U("mol/dm^3",1),U("mol/L",1),U("mmol/dm^3",0.001),
                                           U("mmol/L",0.001),U("mol/m^3",0.001)};
static const Unit molar_energy[] = {U("J/mol",1),U("kJ/mol",1000)};
static const Unit mass_rate[] = {U("mg/s",0.001),U("g/s",1),U("g/min",1.0/60),U("kg/s",1000)};
static const Unit volume_rate[] = {U("cm^3/s",1),U("mL/s",1),U("cm^3/min",1.0/60),U("dm^3/s",1000)};
static const Unit molar_rate[] = {U("mmol/s",0.001),U("mol/s",1),U("mol/min",1.0/60)};
static const Unit flux[] = {U("uT",1e-6),U("mT",0.001),U("T",1)};
static const Unit moment[] = {U("N cm",0.01),U("N m",1)};
static const Unit spring[] = {U("N/cm",100),U("N/m",1)};
static const Unit momentum[] = {U("g m/s",0.001),U("kg m/s",1),U("N s",1)};
static const Unit latent_heat[] = {U("J/kg",1),U("kJ/kg",1000),U("J/g",1000)};
static const Unit heat_capacity[] = {U("J/(kg C)",1),U("J/(kg K)",1),U("kJ/(kg C)",1000),U("J/(g C)",1000)};
static const Unit pressure_volume[] = {U("Pa m^3",1),U("kPa dm^3",1),U("Pa dm^3",0.001)};
static const Unit ratio[] = {U("no unit",1),U("%",0.01)};
static const Unit angle[] = {U("deg",0.017453292519943295),U("rad",1)};
static const Unit turns[] = {U("turns",1)};

const UnitGroup unit_groups[] = {
    GROUP("Length",length),GROUP("Area",area),GROUP("Volume",volume),GROUP("Mass",mass),GROUP("Time",time_units),
    GROUP("Speed",speed),GROUP("Acceleration and field strength",acceleration),GROUP("Pressure",pressure),GROUP("Energy",energy),
    GROUP("Temperature",temperature),GROUP("Temperature change",temperature_change),
    GROUP("Current",current),GROUP("Voltage",voltage),GROUP("Charge",charge),GROUP("Resistance",resistance),
    GROUP("Power",power),GROUP("Force",force),GROUP("Frequency",frequency),GROUP("Density",density),
    GROUP("Amount of substance",amount),GROUP("Molar mass",molar_mass),GROUP("Mass concentration",mass_concentration),
    GROUP("Molar concentration",molar_concentration),GROUP("Energy per mole",molar_energy),
    GROUP("Mass reaction rate",mass_rate),GROUP("Gas volume reaction rate",volume_rate),GROUP("Molar reaction rate",molar_rate),
    GROUP("Magnetic flux density",flux),GROUP("Moment",moment),GROUP("Spring constant",spring),GROUP("Momentum",momentum),
    GROUP("Specific latent heat",latent_heat),
    GROUP("Specific heat capacity",heat_capacity),GROUP("Pressure-volume product",pressure_volume),
    GROUP("Ratios and percentages",ratio),GROUP("Angle",angle)
};
const int unit_group_count = sizeof(unit_groups)/sizeof(*unit_groups);

bool unit_convert(double value, const Unit *from, const Unit *to, double *result) {
    double factor = from->scale/to->scale;
    double offset = (from->offset-to->offset)/to->scale;
    *result = value*factor + offset;
    if (*result == 0) *result = 0;
    return isfinite(*result);
}

void unit_working(char *output, size_t size, double value, const Unit *from,
                  const Unit *to, double result) {
    double factor = from->scale/to->scale;
    double offset = (from->offset-to->offset)/to->scale;
    if (offset)
        snprintf(output, size, "%.12g x %.12g %c %.12g = %.12g %s",
                 value, factor, offset < 0 ? '-' : '+', fabs(offset), result, to->symbol);
    else
        snprintf(output, size, "%.12g x %.12g = %.12g %s", value, factor, result, to->symbol);
}

static bool same_unit(const char *input, const char *symbol, bool fold_case) {
    for (;;) {
        while (isspace((unsigned char)*input) || *input == '^') input++;
        while (isspace((unsigned char)*symbol) || *symbol == '^') symbol++;
        unsigned char a = (unsigned char)*input++, b = (unsigned char)*symbol++;
        if (fold_case ? tolower(a) != tolower(b) : a != b) return false;
        if (!a) return true;
    }
}

static const Unit *find_unit(const Unit *units, int count, const char *symbol, bool fold_case) {
    const Unit *found = NULL;
    for (int i = 0; i < count; i++) {
        if (!same_unit(symbol, units[i].symbol, fold_case)) continue;
        if (found && found->scale != units[i].scale) return NULL;
        found = &units[i];
    }
    return found;
}

static const Unit *input_unit(const UnitGroup *group, const char *suffix) {
    const Unit *unit = find_unit(group->units, group->count, suffix, false);
    if (unit) return unit;
    if (group->units == temperature_change) {
        if (same_unit(suffix,"degC",true) || same_unit(suffix,"C",true) ||
            same_unit(suffix,"K",true)) return &temperature_change[0];
    }
    if (group->units == temperature && same_unit(suffix,"C",true)) return &temperature[0];
    return find_unit(group->units, group->count, suffix, true);
}

bool quantity_read(const char *input, const char *expected, double *value,
                   char *working, size_t size) {
    if (size) working[0] = 0;

    const UnitGroup *group = NULL;
    const Unit *target = NULL;
    for (int i = 0; i < unit_group_count; i++) {
        target = find_unit(unit_groups[i].units, unit_groups[i].count, expected, false);
        if (target) { group = &unit_groups[i]; break; }
    }
    if (!group && !strcmp(expected,"turns")) {
        static const UnitGroup turn_group = GROUP("Turns",turns);
        group = &turn_group;
        target = &turns[0];
    }
    char expression[EXPRESSION_SIZE];
    size_t length = strlen(input);
    for (size_t i = 1; group && i < length && i < sizeof(expression); i++) {
        if (!isalpha((unsigned char)input[i]) && input[i] != '%') continue;
        const Unit *from = input_unit(group, input+i);
        if (!from) continue;
        memcpy(expression, input, i);
        expression[i] = 0;
        double original;
        if (!cas_read_number(expression, &original)) continue;
        if (!unit_convert(original, from, target, value)) return false;
        if (size && from != target)
            snprintf(working, size, "%.12g %s = %.12g %s", original, from->symbol, *value, target->symbol);
        return true;
    }
    return cas_read_number(input, value);
}
