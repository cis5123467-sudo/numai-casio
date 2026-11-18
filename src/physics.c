#include "physics.h"
#include "cas.h"
#include "units.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N PhysicsNonnegative
#define P PhysicsPositive
#define E PhysicsEfficiency
#define T PhysicsTurns
#define B PhysicsBothSigns
#define V(s,n,u,f,k) {s,n,u,f,k}
#define EQ(t,h,g,s,f,u,e,...) {t,g,s,f,u,e,h,sizeof((PhysicsVariable[]){__VA_ARGS__})/sizeof(PhysicsVariable),{__VA_ARGS__},NULL}

const PhysicsEquation physics_equations[] = {
    EQ("Kinetic energy",0,"Energy","4.1.1.2","$1=0.5*$2*$3^2",
       "Use for the kinetic store of a moving object. Doubling speed quadruples Ek at fixed mass.",
       "m=2 kg, v=3 m/s: Ek=0.5 x 2 x 3^2=9 J.",
       V("Ek","Kinetic energy","J","0.5*$2*$3^2",N), V("m","Mass","kg","2*$1/$3^2",P), V("v","Speed","m/s","sqrt(2*$1/$2)",N)),
    EQ("Elastic potential energy",0,"Energy","4.1.1.2","$1=0.5*$2*$3^2",
       "Use for a spring obeying Hooke's law. Extension is stretched length minus natural length.",
       "k=200 N/m, e=0.10 m: Ee=0.5 x 200 x 0.10^2=1 J.",
       V("Ee","Elastic energy","J","0.5*$2*$3^2",N), V("k","Spring constant","N/m","2*$1/$3^2",P), V("e","Extension","m","sqrt(2*$1/$2)",N)),
    EQ("Gravitational energy",0,"Energy","4.1.1.2","$1=$2*$3*$4",
       "Use near the surface where gravitational field strength is approximately constant. Take h as the signed change in height for an energy change.",
       "m=3 kg lifted 2 m at 9.8 N/kg: Ep=58.8 J.",
       V("Ep","Gravitational energy change","J","$2*$3*$4",0), V("m","Mass","kg","$1/($3*$4)",P), V("g","Gravitational field strength","N/kg","$1/($2*$4)",N), V("h","Height change","m","$1/($2*$3)",0)),
    EQ("Heating and temperature",0,"Energy","4.1.1.3","$1=$2*$3*$4",
       "Use when temperature changes without a change of state. A difference of 1 degree C equals a difference of 1 K.",
       "0.50 kg of water, c=4200 J/(kg C), warms by 8 C. dE=0.5 x 4200 x 8=16800 J.",
       V("dE","Thermal energy change","J","$2*$3*$4",0), V("m","Mass","kg","$1/($3*$4)",P), V("c","Specific heat capacity","J/(kg C)","$1/($2*$4)",P), V("dT","Temperature change","C or K","$1/($2*$3)",0)),
    EQ("Power from energy",0,"Energy","4.1.1.4","$1=$2/$3",
       "Find an average rate of energy transfer. Convert kJ to J and minutes to seconds.",
       "2400 J transferred in 8 s: P=2400/8=300 W.",
       V("P","Power","W","$2/$3",N), V("E","Energy transferred","J","$1*$3",N), V("t","Time","s","$2/$1",P)),
    EQ("Power from work",0,"Energy","4.1.1.4","$1=$2/$3",
       "Use for a mechanical transfer, for example lifting a load. W here means work and is measured in joules.",
       "A motor does 600 J of work in 4 s. P=150 W.",
       V("P","Power","W","$2/$3",N), V("W","Work done","J","$1*$3",N), V("t","Time","s","$2/$1",P)),
    EQ("Energy efficiency",0,"Energy","4.1.2.2","$1=$2/$3",
       "Enter a ratio from 0 to 1, e.g. 0.80 for 80%. Multiply the result by 100 for a percentage.",
       "Useful energy 360 J from 450 J input: eff=0.8=80%.",
       V("eff","Efficiency ratio","no unit","$2/$3",E), V("Eout","Useful output energy","J","$1*$3",N), V("Ein","Total input energy","J","$2/$1",P)),
    EQ("Power efficiency",0,"Energy","4.1.2.2","$1=$2/$3",
       "Compare input and useful output powers over the same operating conditions. Use the same units for both.",
       "45 W useful from 60 W input: eff=45/60=0.75=75%.",
       V("eff","Efficiency ratio","no unit","$2/$3",E), V("Pout","Useful output power","W","$1*$3",N), V("Pin","Total input power","W","$2/$1",P)),
    EQ("Charge flow",0,"Electricity","4.2.1.2","$1=$2*$3",
       "For constant current, the charge passing a point is current times time. Use current in amperes.",
       "0.25 A for 120 s: Q=0.25 x 120=30 C.",
       V("Q","Charge flow","C","$2*$3",N), V("I","Current","A","$1/$3",N), V("t","Time","s","$1/$2",P)),
    EQ("Potential difference",0,"Electricity","4.2.1.3","$1=$2*$3",
       "Use values for the same component. A filament lamp's resistance can change when the current changes.",
       "I=0.30 A, R=20 ohms: V=6.0 V.",
       V("V","Potential difference","V","$2*$3",N), V("I","Current","A","$1/$3",N), V("R","Resistance","ohm","$1/$2",N)),
    EQ("Electrical power from V and I",0,"Electricity","4.2.4.1","$1=$2*$3",
       "Use current through the component and potential difference across that component.",
       "12 V and 0.50 A: P=6 W.",
       V("P","Power","W","$2*$3",N), V("V","Potential difference","V","$1/$3",N), V("I","Current","A","$1/$2",N)),
    EQ("Electrical power in a resistor",0,"Electricity","4.2.4.1","$1=$2^2*$3",
       "Useful for resistive heating and power lost in transmission cables. Convert mA to A first.",
       "I=2 A, R=3 ohms: P=2^2 x 3=12 W.",
       V("P","Power","W","$2^2*$3",N), V("I","Current magnitude","A","sqrt($1/$3)",N), V("R","Resistance","ohm","$1/$2^2",N)),
    EQ("Electrical energy from power",0,"Electricity","4.2.4.2","$1=$2*$3",
       "Use W and seconds for joules. For electricity billing use kW and hours to obtain kWh.",
       "A 900 W appliance runs for 20 s. E=18000 J.",
       V("E","Energy transferred","J","$2*$3",N), V("P","Power","W","$1/$3",N), V("t","Time","s","$1/$2",P)),
    EQ("Electrical energy from charge",0,"Electricity","4.2.4.2","$1=$2*$3",
       "Potential difference measures energy transferred per coulomb. If given I and t, work out Q first.",
       "20 C moves through 6 V. E=20 x 6=120 J.",
       V("E","Energy transferred","J","$2*$3",N), V("Q","Charge flow","C","$1/$3",N), V("V","Potential difference","V","$1/$2",N)),
    EQ("Density",0,"Particle model","4.3.1.1","$1=$2/$3",
       "For SI units use kg and m^3. To convert g/cm^3 to kg/m^3 multiply by 1000.",
       "0.30 kg occupies 0.00012 m^3. rho=2500 kg/m^3.",
       V("rho","Density","kg/m^3","$2/$3",P), V("m","Mass","kg","$1*$3",P), V("V","Volume","m^3","$2/$1",P)),
    EQ("Specific latent heat",0,"Particle model","4.3.2.3","$1=$2*$3",
       "Use when state changes at constant temperature. Match fusion to melting/freezing and vaporisation to boiling/condensing.",
       "Melting 0.20 kg of ice at L=334000 J/kg requires 66800 J.",
       V("E","Energy for change of state","J","$2*$3",N), V("m","Mass changing state","kg","$1/$3",N), V("L","Specific latent heat","J/kg","$1/$2",P)),
    EQ("Pressure and volume of a gas",0,"Particle model","4.3.3.2","$2*$3=$1",
       "Use for a fixed gas mass at constant temperature. Compute K in state 1, then enter K with the known value for state 2.",
       "p=100000 Pa, V=0.004 m^3: K=400 J. Halve V and p doubles to 200000 Pa.",
       V("K","Pressure-volume constant","Pa m^3","$2*$3",P), V("p","Absolute pressure","Pa","$1/$3",P), V("V","Gas volume","m^3","$1/$2",P)),
    EQ("Weight",0,"Forces","4.5.1.3","$1=$2*$3",
       "Weight is a force; mass is in kg. Near Earth's surface use about 9.8 N/kg unless the question gives another value.",
       "A 5 kg object at 9.8 N/kg weighs 49 N.",
       V("W","Weight","N","$2*$3",N), V("m","Mass","kg","$1/$3",P), V("g","Gravitational field strength","N/kg","$1/$2",N)),
    EQ("Mechanical work",0,"Forces","4.5.2","$1=$2*$3",
       "Use the distance along the force. If force and motion are parallel, use the full distance moved.",
       "A 12 N force pushes an object 4 m along its own line of action: W=48 J.",
       V("W","Work done","J","$2*$3",N), V("F","Force magnitude","N","$1/$3",N), V("s","Distance along force","m","$1/$2",N)),
    EQ("Hooke's law",0,"Forces","4.5.3","$1=$2*$3",
       "Use on the straight proportional part of a force-extension graph. The gradient of F plotted against e is k.",
       "A 12 N force extends a spring by 0.04 m: k=12/0.04=300 N/m.",
       V("F","Applied force","N","$2*$3",N), V("k","Spring constant","N/m","$1/$3",P), V("e","Extension","m","$1/$2",N)),
    EQ("Moment of a force",0,"Forces","4.5.4","$1=$2*$3",
       "Measure from the pivot to the line of action at right angles. For balance, equate clockwise and anticlockwise totals.",
       "30 N applied with a perpendicular arm of 0.40 m gives 12 N m.",
       V("M","Moment magnitude","N m","$2*$3",N), V("F","Force","N","$1/$3",N), V("d","Perpendicular distance","m","$1/$2",N)),
    EQ("Pressure on a surface",0,"Forces","4.5.5.1.1","$1=$2/$3",
       "Normal means perpendicular to the surface. Convert cm^2 to m^2 by dividing by 10000.",
       "600 N over 0.03 m^2: p=20000 Pa.",
       V("p","Pressure","Pa","$2/$3",N), V("F","Normal force","N","$1*$3",N), V("A","Area","m^2","$2/$1",P)),
    EQ("Liquid pressure at depth",1,"Forces","4.5.5.1.2","$1=$2*$3*$4",
       "Gives pressure from the liquid alone. Add atmospheric pressure if absolute pressure is required.",
       "At 2 m depth in water of density 1000 kg/m^3 and g=9.8 N/kg: p=19600 Pa.",
       V("p","Pressure due to liquid","Pa","$2*$3*$4",N), V("h","Vertical depth","m","$1/($3*$4)",N), V("rho","Liquid density","kg/m^3","$1/($2*$4)",P), V("g","Gravitational field strength","N/kg","$1/($2*$3)",N)),
    EQ("Distance, speed and time",0,"Forces and motion","4.5.6.1.2","$1=$2*$3",
       "Use constant speed or the average over the whole interval. Distance is nonnegative.",
       "A cyclist averages 5 m/s for 30 s: s=150 m.",
       V("s","Distance","m","$2*$3",N), V("v","Speed","m/s","$1/$3",N), V("t","Time","s","$1/$2",P)),
    EQ("Average acceleration",0,"Forces and motion","4.5.6.1.5","$1=$2/$3",
       "Use dv = final velocity minus initial velocity and keep direction signs. Negative a can represent braking.",
       "Velocity changes from 12 m/s to 3 m/s in 3 s: dv=-9 m/s, a=-3 m/s^2.",
       V("a","Acceleration","m/s^2","$2/$3",0), V("dv","Velocity change","m/s","$1*$3",0), V("t","Time","s","$2/$1",P)),
    EQ("Velocity and displacement",0,"Forces and motion","4.5.6.1.5","$1^2-$2^2=2*$3*$4",
       "Use for straight-line constant acceleration when time is missing. If finding a velocity, choose its direction from the motion.",
       "u=4 m/s, a=2 m/s^2, s=12 m: v^2=64. Speed is 8 m/s.",
       V("v","Final velocity","m/s","sqrt($2^2+2*$3*$4)",B), V("u","Initial velocity","m/s","sqrt($1^2-2*$3*$4)",B), V("a","Acceleration","m/s^2","($1^2-$2^2)/(2*$4)",0), V("s","Displacement","m","($1^2-$2^2)/(2*$3)",0)),
    EQ("Newton's second law",0,"Forces and motion","4.5.6.2.2","$1=$2*$3",
       "Add forces with direction first, then use the resultant along the chosen direction. Normal and parallel components can be treated separately.",
       "12 N forwards and 4 N backwards on 2 kg: F=8 N, a=4 m/s^2 forwards.",
       V("F","Resultant force","N","$2*$3",0), V("m","Mass","kg","$1/$3",P), V("a","Acceleration","m/s^2","$1/$2",0)),
    EQ("Momentum",1,"Forces and motion","4.5.7.1","$1=$2*$3",
       "Momentum is a vector. Choose a positive direction, including when adding momenta for collisions.",
       "A 4 kg trolley moving at -2 m/s has momentum -8 kg m/s.",
       V("p","Momentum","kg m/s","$2*$3",0), V("m","Mass","kg","$1/$3",P), V("v","Velocity","m/s","$1/$2",0)),
    EQ("Force and momentum change",1,"Forces and motion","4.5.7.3","$1=$2*$3/$4",
       "For constant mass, change in momentum is m x dv. A longer stop time reduces the magnitude of average force for the same change.",
       "A 0.2 kg ball changes from 10 to -5 m/s in 0.03 s. F=0.2 x (-15)/0.03=-100 N.",
       V("F","Mean resultant force","N","$2*$3/$4",0), V("m","Mass","kg","$1*$4/$3",P), V("dv","Velocity change","m/s","$1*$4/$2",0), V("dt","Elapsed time","s","$2*$3/$1",P)),
    EQ("Period and frequency",0,"Waves","4.6.1.2","$1=1/$2",
       "Use period for one cycle. If you time several cycles, divide elapsed time by the number of cycles first.",
       "Frequency 5 Hz gives T=1/5=0.2 s.",
       V("T","Period","s","1/$2",P), V("f","Frequency","Hz","1/$1",P)),
    EQ("Wave speed",0,"Waves","4.6.1.2","$1=$2*$3",
       "For a wave crossing a boundary the source fixes the frequency. If speed changes, wavelength changes.",
       "50 Hz with wavelength 0.20 m gives v=10 m/s.",
       V("v","Wave speed","m/s","$2*$3",P), V("f","Frequency","Hz","$1/$3",P), V("lambda","Wavelength","m","$1/$2",P)),
    EQ("Magnification",0,"Waves and lenses","4.6.2.5","$1=$2/$3",
       "Use heights in the same units. This sheet uses magnitude; describe image orientation separately.",
       "Image 18 mm, object 6 mm: M=3.",
       V("M","Magnification","no unit","$2/$3",N), V("hi","Image height","m","$1*$3",N), V("ho","Object height","m","$2/$1",P)),
    EQ("Magnetic force on a wire",1,"Magnetism","4.7.2.2","$1=$2*$3*$4",
       "Use when the conductor is at right angles to the field. The length is only the part within the field.",
       "0.4 T, 5 A and 0.20 m gives F=0.4 N.",
       V("F","Force magnitude","N","$2*$3*$4",N), V("B","Magnetic flux density","T","$1/($3*$4)",N), V("I","Current","A","$1/($2*$4)",N), V("l","Length in field","m","$1/($2*$3)",P)),
    EQ("Transformer voltage ratio",1,"Magnetism","4.7.3.4","$1/$2=$3/$4",
       "Use for a transformer with alternating input. More turns on the secondary step the voltage up.",
       "Vp=120 V, np=300, ns=600. Vs=120 x 600/300=240 V.",
       V("Vp","Primary voltage","V","$2*$3/$4",P), V("Vs","Secondary voltage","V","$1*$4/$3",P), V("np","Primary coil turns","turns","$1*$4/$2",T), V("ns","Secondary coil turns","turns","$2*$3/$1",T)),
    EQ("Ideal transformer power",1,"Magnetism","4.7.3.4","$1*$2=$3*$4",
       "Use for an ideal or effectively 100% efficient transformer. Increasing voltage decreases current at equal power.",
       "Vp=12 V, Ip=2 A and Vs=48 V. Is=(12 x 2)/48=0.5 A.",
       V("Vp","Primary voltage","V","$3*$4/$2",P), V("Ip","Primary current","A","$3*$4/$1",N), V("Vs","Secondary voltage","V","$1*$2/$4",P), V("Is","Secondary current","A","$1*$2/$3",N))
};

const int physics_equation_count = (int)(sizeof(physics_equations)/sizeof(*physics_equations));

static void add_text(char **output, size_t *space, const char *format, ...) {
    if (*space <= 1) return;
    va_list args;
    va_start(args, format);
    int size = vsnprintf(*output, *space, format, args);
    va_end(args);
    if (size < 0) return;
    size_t used = (size_t)size < *space ? (size_t)size : *space - 1;
    *output += used;
    *space -= used;
}

typedef enum { Calculation, Symbolic, Words, Substituted } EquationFormat;

static void append_formula(const PhysicsEquation *equation, const char *formula,
                           EquationFormat format, const char *const values[SCIENCE_VARIABLES],
                           char **output, size_t *size) {
    const char *start = formula;
    while (*formula) {
        if (*formula == '$') {
            int index = *++formula - '1';
            const PhysicsVariable *v = &equation->variables[index];
            if (values) add_text(output, size, "%s", values[index]);
            else if (format == Words) add_text(output, size, "%s [%s]", v->name, v->unit);
            else add_text(output, size, "%s", v->symbol);
        } else if (*formula == '*' && format != Calculation) {
            if (format != Symbolic || (formula > start && isdigit((unsigned char)formula[-1]) &&
                                       isdigit((unsigned char)formula[1]))) add_text(output, size, " x ");
        } else if (format == Words && *formula == '/') {
            add_text(output, size, " divided by ");
        } else if (format == Words && formula[0] == '^' && formula[1] == '2') {
            add_text(output, size, " squared");
            formula++;
        } else if (format == Words && !strncmp(formula, "sqrt(", 5)) {
            add_text(output, size, "square root of ");
            formula += 3;
        } else if (format == Words && !strncmp(formula, "min(", 4)) {
            add_text(output, size, "the smaller of ");
            formula += 2;
        } else if (format == Words && !strncmp(formula, "abs(", 4)) {
            add_text(output, size, "absolute value of ");
            formula += 2;
        } else if (format == Words && (*formula == '=' || *formula == '+' || *formula == '-')) {
            add_text(output, size, " %c ", *formula);
        } else {
            add_text(output, size, "%c", *formula);
        }
        formula++;
    }
}

static void append_subject(const PhysicsEquation *equation, int subject, EquationFormat format,
                            const char *const values[SCIENCE_VARIABLES], char **output, size_t *size) {
    const PhysicsVariable *v = &equation->variables[subject];
    if (format == Words) add_text(output, size, "%s [%s] = %s", v->name, v->unit,
                                 v->flags & B ? "plus or minus " : "");
    else add_text(output, size, "%s=%s", v->symbol, v->flags & B ? "+/-" : "");
    append_formula(equation, v->formula, format, values, output, size);
}

void physics_word_equation(const PhysicsEquation *equation, char output[SCIENCE_WORD_SIZE]) {
    size_t size = SCIENCE_WORD_SIZE;
    output[0] = 0;
    append_formula(equation, equation->formula, Words, NULL, &output, &size);
}

void physics_subject_equation(const PhysicsEquation *equation, int subject, char *output, size_t size) {
    output[0] = 0;
    append_subject(equation, subject, Symbolic, NULL, &output, &size);
}

static void append_subject_use(const PhysicsEquation *equation, int subject, char **output, size_t *size) {
    add_text(output, size, "Use: Find %s given ", equation->variables[subject].name);
    for (int i = 0, listed = 0; i < equation->count; i++) {
        if (i == subject) continue;
        if (listed > 0) add_text(output, size, listed == equation->count - 2 ? " and " : ", ");
        add_text(output, size, "%s%s", equation->variables[i].name,
                 equation->variables[i].flags & ScienceOptional ? " (if needed)" : "");
        listed++;
    }
    add_text(output, size, ".\n");
}

static const char symbols_heading[] = "Symbols and units";
static const char example_heading[] = "Worked example";
static const char uses_heading[] = "When to use it";
static const char rearrangements_heading[] = "Rearrangements";

bool physics_reference_heading(const char *text) {
    return !strcmp(text, symbols_heading) || !strcmp(text, example_heading) ||
           !strcmp(text, uses_heading) || !strcmp(text, rearrangements_heading);
}

static const char *unit_name(const char *symbol) {
    static const struct { const char *symbol, *name; } units[] = {
        {"A", "ampere"},
        {"C", "coulomb"},
        {"C or K", "degree Celsius or kelvin"},
        {"Hz", "hertz"},
        {"J", "joule"},
        {"J/(kg C)", "joule per kilogram per degree Celsius"},
        {"J/kg", "joule per kilogram"},
        {"kJ/mol", "kilojoule per mole"},
        {"g/mol", "gram per mole"},
        {"mol", "mole"},
        {"mol/dm^3", "mole per cubic decimetre"},
        {"g/dm^3", "gram per cubic decimetre"},
        {"g", "gram"},
        {"cm", "centimetre"},
        {"cm^3", "cubic centimetre"},
        {"dm^3", "cubic decimetre"},
        {"g/s", "gram per second"},
        {"cm^3/s", "cubic centimetre per second"},
        {"mol/s", "mole per second"},
        {"%", "percent"},
        {"N", "newton"},
        {"N m", "newton metre"},
        {"N/kg", "newton per kilogram"},
        {"N/m", "newton per metre"},
        {"Pa", "pascal"},
        {"Pa m^3", "pascal cubic metre"},
        {"T", "tesla"},
        {"V", "volt"},
        {"W", "watt"},
        {"kg", "kilogram"},
        {"kg m/s", "kilogram metre per second"},
        {"kg/m^3", "kilogram per cubic metre"},
        {"m", "metre"},
        {"m/s", "metre per second"},
        {"m/s^2", "metre per second squared"},
        {"m^2", "square metre"},
        {"m^3", "cubic metre"},
        {"no unit", "dimensionless"},
        {"ohm", "ohm"},
        {"s", "second"},
        {"turns", "number of turns"}
    };
    for (size_t i = 0; i < sizeof(units)/sizeof(*units); i++)
        if (!strcmp(symbol, units[i].symbol)) return units[i].name;
    return symbol;
}

void physics_reference(const PhysicsEquation *equation, char output[SCIENCE_REFERENCE_SIZE]) {
    char *next = output;
    size_t remaining = SCIENCE_REFERENCE_SIZE;
    output[0] = 0;
    append_formula(equation, equation->formula, Symbolic, NULL, &next, &remaining);
    add_text(&next, &remaining, "\n");
    append_formula(equation, equation->formula, Words, NULL, &next, &remaining);
    add_text(&next, &remaining, "\n\n%s\n", symbols_heading);
    for (int i = 0; i < equation->count; i++) {
        const PhysicsVariable *v = &equation->variables[i];
        add_text(&next, &remaining, "- %s: %s [%s]\n  %s\n", v->symbol, v->name, v->unit, unit_name(v->unit));
    }
    add_text(&next, &remaining, "\n%s\n%s\n\n%s\n%s\n\n%s\n",
             example_heading, equation->example, uses_heading, equation->uses, rearrangements_heading);
    bool previous = false;
    for (int i = 0; i < equation->count; i++) {
        if (!equation->variables[i].formula) continue;
        if (previous) add_text(&next, &remaining, "\n");
        previous = true;
        append_subject(equation, i, Symbolic, NULL, &next, &remaining);
        add_text(&next, &remaining, "\n");
        append_subject(equation, i, Words, NULL, &next, &remaining);
        add_text(&next, &remaining, "\n");
        append_subject_use(equation, i, &next, &remaining);
    }
}

static bool valid(double value, unsigned flags) {
    if (flags & E) return value >= 0 && value <= 1;
    if (flags & T) return value > 0 && fabs(value-round(value)) <= 1e-9;
    if (flags & ScienceWhole) return value >= 0 && fabs(value-round(value)) <= 1e-9;
    if (flags & SciencePercent) return value >= 0 && value <= 100;
    if (flags & P) return value > 0;
    return !(flags & N) || value >= 0;
}

bool physics_solve(const PhysicsEquation *equation, int subject,
                   const char *const values[SCIENCE_VARIABLES], ScienceWorking *working) {
    char numeric[SCIENCE_VARIABLES][32], readable[SCIENCE_VARIABLES][28], formula[200] = "";
    const char *evaluated[SCIENCE_VARIABLES] = {0}, *shown[SCIENCE_VARIABLES] = {0};
    double numbers[SCIENCE_VARIABLES] = {0};
    char *output = working->answer;
    size_t size = sizeof(working->answer);
    char *converted = working->conversions;
    size_t space = sizeof(working->conversions);
    working->substituted[0] = working->conversions[0] = working->steps[0] = 0;
    for (int i = 0; i < equation->count; i++) {
        if (i == subject) continue;
        double value = 0;
        char conversion[80] = "";
        const PhysicsVariable *v = &equation->variables[i];
        bool omitted = v->flags & ScienceOptional && !*values[i];
        if ((!omitted && !quantity_read(values[i], v->unit, &value, conversion, sizeof(conversion))) ||
            !valid(value, v->flags)) {
            snprintf(output, size, "Check %s [%s].", v->name, v->unit);
            return false;
        }
        numbers[i] = value;
        if (*conversion) add_text(&converted, &space, "%s\n", conversion);
        snprintf(numeric[i], sizeof(numeric[i]), "(%.17g)", value);
        char number[24];
        int precision = 15;
        do {
            snprintf(number, sizeof(number), "%.*g", precision++, value == 0 ? 0 : value);
        } while (precision <= 17 && strtod(number, NULL) != value);
        snprintf(readable[i], sizeof(readable[i]), value < 0 ? "(%s)" : "%s", number);
        evaluated[i] = numeric[i];
        shown[i] = readable[i];
    }
    const PhysicsVariable *target = &equation->variables[subject];
    if (!target->formula) {
        snprintf(output, size, "Choose a solvable unknown.");
        return false;
    }
    char *next = formula;
    size_t remaining = sizeof(formula);
    append_formula(equation, target->formula, Calculation, evaluated, &next, &remaining);
    next = working->substituted;
    remaining = sizeof(working->substituted);
    append_subject(equation, subject, Substituted, shown, &next, &remaining);
    double result;
    if (!cas_read_number(formula, &result) || !valid(result, target->flags)) {
        snprintf(output, size, "No valid result. Check signs and units.");
        return false;
    }
    bool unitless = !strcmp(target->unit, "no unit");
    snprintf(output, size, "%s = %s%.10g %s", target->symbol,
             target->flags & B && result > 0 ? "+/- " : "", result == 0 ? 0 : result,
             unitless ? "(no unit)" : target->unit);
    numbers[subject] = result;
    if (equation->steps) equation->steps(subject, numbers, working->steps, sizeof(working->steps));
    return true;
}
