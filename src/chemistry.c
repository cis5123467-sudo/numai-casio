#include "physics.h"

#include <stdio.h>

#define N PhysicsNonnegative
#define P PhysicsPositive
#define I ScienceWhole
#define C PhysicsTurns
#define E SciencePercent
#define O ScienceOptional
#define V(symbol,name,unit,formula,flags) {symbol,name,unit,formula,flags}
#define CARD(t,h,g,s,f,u,e,work,...) \
    {t,g,s,f,u,e,h,sizeof((PhysicsVariable[]){__VA_ARGS__})/sizeof(PhysicsVariable),{__VA_ARGS__},work}
#define EQ(t,h,g,s,f,u,e,...) CARD(t,h,g,s,f,u,e,NULL,__VA_ARGS__)

static void titration_steps(int subject, const double v[SCIENCE_VARIABLES], char *output, size_t size) {
    bool find_a = subject == 0 || subject == 2 || subject == 4;
    double known = find_a ? v[1]*v[3] : v[0]*v[2];
    double numerator = find_a ? v[4] : v[5];
    double denominator = find_a ? v[5] : v[4];
    char from = find_a ? 'B' : 'A', to = find_a ? 'A' : 'B';
    snprintf(output, size, "Moles of %c = %.10g x %.10g = %.10g mol\n"
             "Mole ratio %c:%c = %.10g:%.10g\n"
             "Moles of %c = %.10g x %.10g/%.10g = %.10g mol",
             from, find_a ? v[1] : v[0], find_a ? v[3] : v[2], known,
             from, to, denominator, numerator, to, known, numerator, denominator,
             known*numerator/denominator);
}

static void reacting_mass_steps(int subject, const double v[SCIENCE_VARIABLES], char *output, size_t size) {
    bool find_product = subject == 0 || subject == 3 || subject == 5;
    double moles = find_product ? v[1]/v[2] : v[0]/v[3];
    double from = find_product ? v[4] : v[5], to = find_product ? v[5] : v[4];
    snprintf(output, size, "Known amount = %.10g mol\n"
             "Mole ratio known:unknown = %.10g:%.10g\nUnknown amount = %.10g mol",
             moles, from, to, moles*to/from);
}

static void limiting_steps(int subject, const double v[SCIENCE_VARIABLES], char *output, size_t size) {
    (void)subject;
    double a = v[1]/v[3], b = v[2]/v[4];
    const char *limiting = a < b ? "A limits the reaction." : b < a ? "B limits the reaction." :
                           "Both are used up in the given ratio.";
    snprintf(output, size, "A allows %.10g mol of reaction.\nB allows %.10g mol of reaction.\n%s",
             a, b, limiting);
}

const PhysicsEquation chemistry_equations[] = {
    EQ("Neutron number",0,"Atomic structure","4.1.1.5","$1=$2-$3",
       "Use the mass number for the isotope and the atomic number of the element. An ion has the same nucleus as the corresponding atom.",
       "Sodium-23 has atomic number 11. Neutrons = 23 - 11 = 12.",
       V("N","Neutron number","no unit","$2-$3",I),V("A","Mass number","no unit","$1+$3",C),V("Z","Atomic number","no unit","$2-$1",C)),
    EQ("Relative atomic mass",0,"Atomic structure","4.1.1.6","$1=($2*$4+$3*(100-$4))/100",
       "For two isotopes, enter the percentage for isotope 1. Isotope 2 accounts for the remaining percentage. For more isotopes, calculate each contribution and add them.",
       "75% chlorine-35 and 25% chlorine-37 give Ar = (35 x 75 + 37 x 25)/100 = 35.5.",
       V("Ar","Relative atomic mass","no unit","($2*$4+$3*(100-$4))/100",P),V("A1","Isotope 1 mass","no unit","(100*$1-$3*(100-$4))/$4",P),
       V("A2","Isotope 2 mass","no unit","(100*$1-$2*$4)/(100-$4)",P),V("p","Isotope 1 abundance","%","100*($1-$3)/($2-$3)",E)),
    EQ("Isotope contribution",0,"Atomic structure","4.1.1.6","$1=$2*$3/100",
       "For any number of isotopes, calculate one contribution for each isotope and add all contributions. The abundances must total 100%.",
       "An isotope with mass 24 and abundance 79% contributes 18.96 to Ar.",
       V("a","Contribution to Ar","no unit","$2*$3/100",N),V("A","Isotope mass","no unit","100*$1/$3",P),V("p","Isotope abundance","%","100*$1/$2",E)),
    EQ("Element contribution to Mr",0,"Quantitative chemistry","4.3.1.2","$1=$2*$3",
       "Multiply Ar by the number of atoms of the element in the formula. Expand brackets first, then add all element contributions to find Mr.",
       "In Ca(OH)2 there are two oxygen atoms. Oxygen contributes 2 x 16 = 32 to Mr.",
       V("S","Element contribution","no unit","$2*$3",P),V("Ar","Relative atomic mass","no unit","$1/$3",P),
       V("k","Number of atoms","no unit","$1/$2",C)),
    EQ("Relative formula mass",0,"Quantitative chemistry","4.3.1.2","$1=$2+$3+$4+$5+$6",
       "Enter each element's Ar multiplied by its subscript, or a subtotal already worked out. Leave unused subtotals blank. Mr has no unit.",
       "Ca(OH)2 gives calcium 40, oxygen 32 and hydrogen 2. Mr = 74.",
       V("Mr","Relative formula mass","no unit","$2+$3+$4+$5+$6",P),V("S1","Subtotal 1","no unit","$1-$3-$4-$5-$6",N),
       V("S2","Subtotal 2","no unit","$1-$2-$4-$5-$6",N|O),V("S3","Subtotal 3","no unit","$1-$2-$3-$5-$6",N|O),
       V("S4","Subtotal 4","no unit","$1-$2-$3-$4-$6",N|O),V("S5","Subtotal 5","no unit","$1-$2-$3-$4-$5",N|O)),
    EQ("Percentage by mass",0,"Quantitative chemistry","4.3.1.2","$1=100*$2/$3",
       "Use the combined Ar of every atom of the selected element in one formula unit and divide by the compound's Mr.",
       "Oxygen contributes 32 to CO2, which has Mr 44. Percentage oxygen = 72.7%.",
       V("p","Percentage by mass","%","100*$2/$3",E),V("S","Element contribution","no unit","$1*$3/100",N),
       V("Mr","Relative formula mass","no unit","100*$2/$1",P)),
    EQ("Conservation of mass",0,"Quantitative chemistry","4.3.1.1","$1=$2+$3",
       "In a closed system the total mass of products equals the total mass of reactants. Include escaped or absorbed gas where applicable.",
       "25 g of reactants gives 19 g of solid plus 6 g of gas.",
       V("mt","Total mass","g","$2+$3",N),V("m1","First mass","g","$1-$3",N),V("m2","Second mass","g","$1-$2",N)),
    EQ("Uncertainty from repeats",0,"Quantitative chemistry","4.3.1.4","$1=($2-$3)/2",
       "Estimate uncertainty as half the range of repeated readings. Use the largest and smallest retained readings in the same unit.",
       "Readings of 20, 21 and 22 cm^3 give an estimated uncertainty of +/- 1 cm^3.",
       V("u","Half-range uncertainty","cm^3","($2-$3)/2",N),V("hi","Largest repeat","cm^3","$3+2*$1",N),
       V("lo","Smallest repeat","cm^3","$2-2*$1",N)),
    EQ("Mass concentration",0,"Quantitative chemistry","4.3.2.5","$1=$2/$3",
       "Use mass of solute in grams and total volume of solution in dm^3. To find solute mass, multiply the concentration by the solution volume.",
       "5.0 g in 250 cm^3 is 5.0/0.250 = 20 g/dm^3.",
       V("c","Mass concentration","g/dm^3","$2/$3",N),V("m","Solute mass","g","$1*$3",N),V("V","Solution volume","dm^3","$2/$1",P)),
    EQ("Percentage yield",0,"Quantitative chemistry","4.3.3.1","$1=100*$2/$3",
       "Use actual and theoretical masses in the same unit. Losses and incomplete reaction lower yield. An apparent result over 100% suggests wet or impure product or a measurement error.",
       "Actual mass 6 g, theoretical mass 8 g. Yield = 75%.",
       V("Y","Percentage yield","%","100*$2/$3",N),V("ma","Actual product mass","g","$1*$3/100",N),
       V("mt","Theoretical product mass","g","100*$2/$1",P)),
    EQ("Atom economy",0,"Quantitative chemistry","4.3.3.2","$1=100*$2/$3",
       "Use the balanced equation. Multiply the desired product's Mr by its coefficient. Add coefficient times Mr for every reactant to get the denominator.",
       "2Mg + O2 -> 2MgO. Desired total = 2 x 40; reactant total = 2 x 24 + 32. Atom economy = 100%.",
       V("AE","Atom economy","%","100*$2/$3",E),V("D","Weighted desired product Mr","no unit","$1*$3/100",N),
       V("T","Weighted total reactant Mr","no unit","100*$2/$1",P)),
    EQ("Moles, mass and molar mass",1,"Quantitative chemistry","4.3.2.1","$1=$2/$3",
       "Molar mass in g/mol is numerically equal to Ar or Mr. Use grams for the mass. Mr has no unit.",
       "9.0 g of water at 18 g/mol gives 0.50 mol.",
       V("n","Amount of substance","mol","$2/$3",N),V("m","Mass","g","$1*$3",N),V("M","Molar mass","g/mol","$2/$1",P)),
    EQ("Particles and moles",1,"Quantitative chemistry","4.3.2.1","$1=(6.02*10^23)*$2",
       "Use the AQA value 6.02 x 10^23 particles per mole. Name the particles. A mole of molecules can contain several moles of particular atoms.",
       "0.25 mol of molecules contains 1.505 x 10^23 molecules.",
       V("N","Particle count","no unit","(6.02*10^23)*$2",N),V("n","Amount of substance","mol","$1/(6.02*10^23)",N)),
    EQ("Balanced equation mole ratio",1,"Quantitative chemistry","4.3.2.2","$1=$2*$3/$4",
       "Read the coefficients from the balanced equation. For A -> 2B, coefficient of A is 1 and coefficient of B is 2.",
       "2H2 + O2 -> 2H2O. From 0.30 mol O2 in excess H2, make 0.60 mol H2O.",
       V("nB","Amount of B","mol","$2*$3/$4",N),V("nA","Amount of A","mol","$1*$4/$3",N),
       V("b","Coefficient of B","no unit","$1*$4/$2",C),V("a","Coefficient of A","no unit","$2*$3/$1",C)),
    EQ("Simplest mole ratio",1,"Quantitative chemistry","4.3.2.3","$1=$2/$3",
       "Convert the masses to moles first. Divide each amount by the smallest. If a ratio is fractional, multiply every ratio by the same small whole number.",
       "Amounts 0.20 and 0.30 mol give 1 and 1.5. Doubling both gives 2:3.",
       V("r","Relative mole ratio","no unit","$2/$3",P),V("n","Amount for this substance","mol","$1*$3",P),
       V("ns","Smallest amount","mol","$2/$1",P)),
    CARD("Limiting reactant",1,"Quantitative chemistry","4.3.2.4","$1=min($2/$4,$3/$5)",
       "Compare each available amount divided by its balanced coefficient. The smaller value limits the reaction. Multiply that extent by a product's coefficient to get maximum product moles.",
       "With 3 mol A and 2 mol B in 2A + B -> products, A allows 1.5 mol of reaction and limits the yield.",
       limiting_steps,V("x","Maximum reaction extent","mol","min($2/$4,$3/$5)",N),
       V("nA","Available A","mol",NULL,N),V("nB","Available B","mol",NULL,N),
       V("a","Coefficient of A","no unit",NULL,C),V("b","Coefficient of B","no unit",NULL,C)),
    CARD("Theoretical product mass",1,"Quantitative chemistry","4.3.3.1","$1=($2/$3)*($6/$5)*$4",
       "Enter the mass of the limiting reactant. Convert it to moles, apply the product-to-reactant coefficient ratio, then multiply by the product molar mass.",
       "CaCO3 -> CaO + CO2. From 10 g CaCO3 (100 g/mol), expect 0.10 mol CaO, which is 5.6 g.",
       reacting_mass_steps,V("mp","Theoretical product mass","g","($2/$3)*($6/$5)*$4",N),
       V("mr","Limiting reactant mass","g","($1/$4)*($5/$6)*$3",N),V("Mr","Reactant molar mass","g/mol","($2/$1)*($6/$5)*$4",P),
       V("Mp","Product molar mass","g/mol","$1*$3*$5/($2*$6)",P),V("a","Reactant coefficient","no unit","$2*$6*$4/($1*$3)",C),
       V("b","Product coefficient","no unit","$1*$3*$5/($2*$4)",C)),
    EQ("Molar concentration",1,"Quantitative chemistry","4.3.4","$1=$2/$3",
       "Use moles of solute and the total solution volume in dm^3. To get the volume from cm^3, divide by 1000.",
       "0.025 mol in 250 cm^3 gives 0.025/0.250 = 0.10 mol/dm^3.",
       V("c","Molar concentration","mol/dm^3","$2/$3",N),V("n","Solute amount","mol","$1*$3",N),
       V("V","Solution volume","dm^3","$2/$1",P)),
    EQ("Mass and molar concentration",1,"Quantitative chemistry","4.3.4","$1=$2*$3",
       "Multiply mol/dm^3 by the solute's molar mass to get g/dm^3. Divide by molar mass to go the other way.",
       "0.20 mol/dm^3 NaOH x 40 g/mol = 8.0 g/dm^3.",
       V("cm","Mass concentration","g/dm^3","$2*$3",N),V("c","Molar concentration","mol/dm^3","$1/$3",N),
       V("M","Molar mass","g/mol","$1/$2",P)),
    CARD("Titration with mole ratios",1,"Chemical changes","4.4.2.5","$1*$3/$5=$2*$4/$6",
       "Use volume in dm^3 and the coefficients for A and B in the balanced equation. Enter the mean concordant titre. You can calculate a concentration or reacting volume.",
       "H2SO4 + 2NaOH. 20.0 cm^3 of 0.100 mol/dm^3 NaOH neutralises 25.0 cm^3 acid. The acid concentration is 0.0400 mol/dm^3.",
       titration_steps,V("cA","Concentration A","mol/dm^3","$2*$4*$5/($3*$6)",P),
       V("cB","Concentration B","mol/dm^3","$1*$3*$6/($4*$5)",P),V("VA","Volume A","dm^3","$2*$4*$5/($1*$6)",P),
       V("VB","Volume B","dm^3","$1*$3*$6/($2*$5)",P),
       V("a","Coefficient of A","no unit","$1*$3*$6/($2*$4)",C),V("b","Coefficient of B","no unit","$2*$4*$5/($1*$3)",C)),
    EQ("Molar gas volume at RTP",1,"Quantitative chemistry","4.3.5","$1=24*$2",
       "Use 24 dm^3 per mole at room temperature and pressure (20 C and 1 atmosphere). This is 24,000 cm^3 per mole.",
       "0.125 mol of gas occupies 3.0 dm^3 at RTP.",
       V("V","Gas volume","dm^3","24*$2",N),V("n","Gas amount","mol","$1/24",N)),
    EQ("Reacting gas volumes",1,"Quantitative chemistry","4.3.5","$1=$2*$3/$4",
       "At the same temperature and pressure, gas volumes are proportional to balanced equation coefficients. Use matching volume units.",
       "N2 + 3H2 -> 2NH3. 15 dm^3 H2 in excess N2 produces 10 dm^3 NH3.",
       V("VB","Gas volume B","dm^3","$2*$3/$4",N),V("VA","Gas volume A","dm^3","$1*$4/$3",N),
       V("b","Coefficient of gas B","no unit","$1*$4/$2",C),V("a","Coefficient of gas A","no unit","$2*$3/$1",C)),
    EQ("Mean rate from mass",0,"Rates","4.6.1.1","$1=$2/$3",
       "Divide mass of reactant used or product formed by elapsed time. Use a positive change for the amount consumed.",
       "A loss of 1.8 g in 30 s gives 0.06 g/s.",
       V("r","Mean rate","g/s","$2/$3",N),V("m","Mass change magnitude","g","$1*$3",N),V("t","Elapsed time","s","$2/$1",P)),
    EQ("Mean rate from gas volume",0,"Rates","4.6.1.1","$1=$2/$3",
       "Use gas volume collected or consumed over the full time interval.",
       "48 cm^3 of gas in 24 s gives 2 cm^3/s.",
       V("r","Mean rate","cm^3/s","$2/$3",N),V("V","Gas volume change","cm^3","$1*$3",N),V("t","Elapsed time","s","$2/$1",P)),
    EQ("Mean rate in mol/s",1,"Rates","4.6.1.1","$1=$2/$3",
       "Use moles consumed or formed over a time interval. Convert mass to amount first if the question gives grams.",
       "0.030 mol in 15 s gives 0.0020 mol/s.",
       V("r","Mean rate","mol/s","$2/$3",N),V("n","Amount changed","mol","$1*$3",N),V("t","Elapsed time","s","$2/$1",P)),
    EQ("Instantaneous reaction rate",1,"Rates","4.6.1.1","$1=abs($2)/$3",
       "Draw a tangent at the time of interest. Take two clearly separated points on the tangent and divide vertical change by horizontal change. This card uses volume; for masses or moles use the matching rate card with the tangent changes.",
       "A tangent rises by 30 cm^3 over 20 s, so the instantaneous rate is 1.5 cm^3/s.",
       V("r","Instantaneous rate","cm^3/s","abs($2)/$3",N),V("dV","Tangent rise magnitude","cm^3","$1*$3",N),V("dt","Tangent time difference","s","abs($2)/$1",P)),
    EQ("Chromatography Rf",0,"Chemical analysis","4.8.1.3","$1=$2/$3",
       "Measure from the baseline to the centre of the spot and to the solvent front. Use the same length units. An Rf of 0 to 1 has no unit.",
       "Spot 2.8 cm and front 7.0 cm. Rf = 0.40.",
       V("Rf","Rf ratio","no unit","$2/$3",PhysicsEfficiency),V("ds","Spot distance","cm","$1*$3",N),V("df","Solvent front distance","cm","$2/$1",P)),
    EQ("Energy change from bonds",1,"Energy changes","4.5.1.3","$1=$2-$3",
       "Multiply each bond energy by the number of those bonds broken or formed, using the balanced reaction. A negative energy change is exothermic.",
       "Breaking 1300 kJ/mol and forming 1650 kJ/mol gives an energy change of -350 kJ/mol.",
       V("dE","Energy change","kJ/mol","$2-$3",0),V("Eb","Total for bonds broken","kJ/mol","$1+$3",N),V("Ef","Total for bonds formed","kJ/mol","$2-$1",N)),
    EQ("pH change and ion ratio",1,"Chemical changes","4.4.2.6","$1=10^($2-$3)",
       "A decrease of 1 pH unit multiplies hydrogen ion concentration by ten. The ratio here is final concentration divided by initial concentration.",
       "From pH 5 to pH 3, the concentration becomes 10^(5-3) = 100 times higher.",
       V("r","Final to initial ion ratio","no unit","10^($2-$3)",P),V("p1","Initial pH","no unit","$3+log($1)",0),
       V("p2","Final pH","no unit","$2-log($1)",0))
};

const int chemistry_equation_count = sizeof(chemistry_equations)/sizeof(*chemistry_equations);
