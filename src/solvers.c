#include "solvers.h"

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265358979323846

static void add(char *buffer, size_t size, const char *format, ...) {
    size_t used = strlen(buffer);
    if (used >= size - 1) return;
    va_list args;
    va_start(args, format);
    vsnprintf(buffer + used, size - used, format, args);
    va_end(args);
}

typedef struct { double sides[3], angles[3]; } Triangle;

static bool complete_angles(Triangle *t, int a, int b, int c) {
    t->angles[c] = PI - t->angles[a] - t->angles[b];
    return t->angles[c] > 1e-12;
}

static bool complete_sides(Triangle *t, int side) {
    double scale = t->sides[side]/sin(t->angles[side]);
    for (int i = 0; i < 3; i++) t->sides[i] = scale*sin(t->angles[i]);
    return isfinite(t->sides[0]) && isfinite(t->sides[1]) && isfinite(t->sides[2]);
}

static bool angles_from_sides(Triangle *t) {
    double max = fmax(t->sides[0], fmax(t->sides[1], t->sides[2]));
    if (!isfinite(max) || max <= 0) return false;
    double s[3];
    for (int i = 0; i < 3; i++) s[i] = t->sides[i]/max;
    for (int i = 0; i < 3; i++) {
        double a = s[i], b = s[(i+1)%3], c = s[(i+2)%3];
        if (b+c <= a || a <= fabs(b-c)) return false;
        double cosine = (b*b+c*c-a*a)/(2*b*c);
        t->angles[i] = acos(fmax(-1,fmin(1,cosine)));
        if (t->angles[i] <= 0 || t->angles[i] >= PI) return false;
    }
    return true;
}

static bool agrees(const Triangle *a, const Triangle *given) {
    for (int i = 0; i < 3; i++) {
        if (given->sides[i] && fabs(a->sides[i]/given->sides[i] - 1) > 1e-8) return false;
        if (given->angles[i] && fabs(a->angles[i]-given->angles[i]) > 1e-8) return false;
    }
    return true;
}

void solve_triangle(const char *const inputs[6], bool degrees, Solution *solution) {
    *solution = (Solution){0};
    Triangle given = {0}, candidates[2] = {0};
    int na = 0, ns = 0, side = -1, ang = -1, included = -1, opposite = -1;
    double ratio = degrees ? PI/180 : 1;
    for (int i = 0; i < 6; i++) {
        const char *input = inputs[i];
        while (isspace((unsigned char)*input)) input++;
        if (!*input) continue;
        double value;
        if (!cas_read_number(input, &value) || value <= 0 || (i >= 3 && value*ratio >= PI)) {
            snprintf(solution->answer, sizeof(solution->answer), "Check %s %c.",
                     i < 3 ? "side" : "angle", i < 3 ? 'a'+i : 'A'+i-3);
            return;
        }
        if (i < 3) { given.sides[i] = value; ns++; side = i; }
        else { given.angles[i-3] = value*ratio; na++; ang = i-3; }
    }
    if (!ns || ns+na < 3) {
        strcpy(solution->answer, "Enter at least three values, including a side.");
        return;
    }
    for (int i = 0; i < 3; i++) {
        if (given.angles[i] && given.sides[i]) opposite = i;
        if (given.angles[i] && !given.sides[i]) included = i;
    }
    int count = 0;
    Triangle t = given;
    if (ns == 3) {
        snprintf(solution->steps, sizeof(solution->steps),
                 "SSS: use the cosine rule.\ncos(A) = (b^2+c^2-a^2)/(2bc).\nRepeat for B and C.");
        if (angles_from_sides(&t)) candidates[count++] = t;
    } else if (na >= 2) {
        int a = ang, b = (a+1)%3;
        if (!given.angles[b]) b = (a+2)%3;
        int c = 3-a-b;
        snprintf(solution->steps, sizeof(solution->steps),
                 "Two angles and a side.\n%c = %s - %c - %c.\nUse a/sin(A) = b/sin(B) = c/sin(C) for the remaining sides.",
                 'A'+c, degrees ? "180 deg" : "pi", 'A'+a, 'A'+b);
        if (complete_angles(&t,a,b,c) && complete_sides(&t,side)) candidates[count++] = t;
    } else if (included >= 0) {
        int i = included, j = (i+1)%3, k = (i+2)%3;
        double a = t.sides[j], b = t.sides[k], angle = t.angles[i];
        if (fabs(angle-PI/2) < 1e-12) {
            snprintf(solution->steps, sizeof(solution->steps),
                     "Right triangle: Pythagoras.\n%c^2 = %c^2 + %c^2.\nFind each acute angle using trigonometry.",
                     'a'+i, 'a'+j, 'a'+k);
            t.sides[i] = hypot(a,b);
        } else {
            snprintf(solution->steps, sizeof(solution->steps),
                     "SAS: use the cosine rule.\n%c^2 = %c^2 + %c^2 - 2%c%c cos(%c).\nApply the cosine rule again to get the other angles.",
                     'a'+i,'a'+j,'a'+k,'a'+j,'a'+k,'A'+i);
            double scale = fmax(a,b), x = a/scale, y = b/scale;
            t.sides[i] = scale*hypot(x-y, 2*sqrt(x*y)*sin(angle/2));
        }
        if (angles_from_sides(&t)) candidates[count++] = t;
    } else if (opposite >= 0) {
        int i = opposite, j = (i+1)%3;
        if (!given.sides[j]) j = (i+2)%3;
        int k = 3-i-j;
        double sine = t.sides[j]/t.sides[i]*sin(t.angles[i]);
        snprintf(solution->steps, sizeof(solution->steps),
                 "SSA: use the sine rule.\nsin(%c) = %c sin(%c)/%c = %.10g.\nTry the inverse-sine angle and its supplement. Keep only positive third angles.",
                 'A'+j,'a'+j,'A'+i,'a'+i,sine);
        if (sine > 0 && sine <= 1+1e-12) {
            double first = asin(fmin(1,sine));
            for (int n = 0; n < 2; n++) {
                t.angles[j] = n ? PI-first : first;
                if (n && fabs(t.angles[j]-first) < 1e-10) continue;
                if (complete_angles(&t,i,j,k) && complete_sides(&t,i)) candidates[count++] = t;
            }
        }
    }
    int answers = 0;
    for (int i = 0; i < count; i++) {
        if (!agrees(&candidates[i], &given)) continue;
        Triangle *t = &candidates[i];
        if (ns == 3)
            add(solution->steps,sizeof(solution->steps),"\nA = acos((%.6g^2+%.6g^2-%.6g^2)/(2 x %.6g x %.6g)).\n",
                t->sides[1],t->sides[2],t->sides[0],t->sides[1],t->sides[2]);
        else if (included >= 0 && na == 1) {
            int j=(included+1)%3,k=(included+2)%3;
            add(solution->steps,sizeof(solution->steps),
                "\nSubstitute %.6g and %.6g at %.8g %s.\n%c = %.10g.\n",
                t->sides[j],t->sides[k],t->angles[included]/ratio,degrees?"deg":"rad",'a'+included,t->sides[included]);
        }
        add(solution->answer, sizeof(solution->answer),
            "%sTriangle %d\na=%.10g   b=%.10g   c=%.10g\nA=%.10g   B=%.10g   C=%.10g %s\n",
            answers ? "\n" : "", answers+1, t->sides[0], t->sides[1], t->sides[2],
            t->angles[0]/ratio,t->angles[1]/ratio,t->angles[2]/ratio,degrees ? "deg" : "rad");
        answers++;
    }
    solution->ok = answers > 0;
    if (!answers) strcpy(solution->answer, "No triangle fits the supplied values.");
}

enum { FormulaLimit = 160 };
typedef enum { Literal, Symbol, Plus, Minus, Times, Over, Power, Root, FSin, FCos, FTan,
               FAsin, FAcos, FAtan, FLn, FExp, TwoSigns } FormulaKind;
typedef struct { FormulaKind kind; int a,b; char token[20]; } Formula;
typedef struct { const char *at; bool error; } FormulaParser;
static Formula formulas[FormulaLimit];
static int formula_count;
static bool formula_overflow;

static int formula_node(FormulaKind kind, int a, int b, const char *token, int length) {
    if (formula_count == FormulaLimit-1 || length >= (int)sizeof(formulas[0].token)) {
        formula_overflow = true;
        return 0;
    }
    int id = ++formula_count;
    formulas[id] = (Formula){.kind=kind,.a=a,.b=b};
    if (length) memcpy(formulas[id].token, token, (size_t)length);
    return id;
}

static int literal(const char *text) { return formula_node(Literal,0,0,text,(int)strlen(text)); }

static bool equal_formula(int a, int b) {
    if (a == b) return true;
    if (!a || !b) return false;
    const Formula *x = &formulas[a], *y = &formulas[b];
    return x->kind == y->kind && !strcmp(x->token, y->token) &&
           equal_formula(x->a,y->a) && equal_formula(x->b,y->b);
}

static bool is_literal(int id, const char *text) {
    return id && formulas[id].kind == Literal && !strcmp(formulas[id].token,text);
}

static int operation(FormulaKind kind, int a, int b) {
    if (!a || !b) return 0;
    if (kind == Minus && equal_formula(a,b)) return literal("0");
    if ((kind == Plus || kind == Minus) && is_literal(b,"0")) return a;
    if (kind == Plus && is_literal(a,"0")) return b;
    if (kind == Times) {
        if (is_literal(a,"0") || is_literal(b,"0")) return literal("0");
        if (is_literal(a,"1")) return b;
        if (is_literal(b,"1")) return a;
        if (formulas[a].kind != Literal && formulas[b].kind == Literal) {
            int swap=a;
            a=b;
            b=swap;
        }
    }
    if ((kind == Over || kind == Power) && is_literal(b,"1")) return a;
    if (kind == Over && is_literal(a,"0") && !is_literal(b,"0")) return a;
    if (kind == Over && is_literal(b,"0")) return 0;
    if (kind == Over && formulas[a].kind == Over) {
        Formula fraction = formulas[a];
        bool put_first = formulas[b].kind == Literal && formulas[fraction.b].kind != Literal;
        return operation(Over,fraction.a,operation(Times,put_first?b:fraction.b,put_first?fraction.b:b));
    }
    return formula_node(kind,a,b,NULL,0);
}

static void formula_space(FormulaParser *p) {
    while (isspace((unsigned char)*p->at)) p->at++;
}

static bool formula_take(FormulaParser *p, char ch) {
    formula_space(p);
    if (*p->at != ch) return false;
    p->at++;
    return true;
}

static int formula_sum(FormulaParser *p);

static int formula_atom(FormulaParser *p) {
    formula_space(p);
    if (formula_take(p,'(')) {
        int inside = formula_sum(p);
        if (!formula_take(p,')')) p->error = true;
        return inside;
    }
    if (formula_take(p,'[')) {
        const char *start = p->at;
        while (isalnum((unsigned char)*p->at) || *p->at == '_') p->at++;
        int length = (int)(p->at-start);
        if (!formula_take(p,']') || !length || !isalpha((unsigned char)*start)) p->error = true;
        return formula_node(Symbol,0,0,start,length);
    }
    const char *start = p->at;
    if (isdigit((unsigned char)*start) || *start == '.') {
        char *end;
        double number = strtod(start,&end);
        if (end != start && isfinite(number)) {
            p->at = end;
            return formula_node(Literal,0,0,start,(int)(end-start));
        }
    }
    static const struct { const char *name; FormulaKind kind; } calls[] = {
        {"sqrt",Root},{"sin",FSin},{"cos",FCos},{"tan",FTan},{"ln",FLn},{"exp",FExp}
    };
    for (size_t i = 0; i < sizeof(calls)/sizeof(*calls); i++) {
        size_t n = strlen(calls[i].name);
        if (strncmp(start,calls[i].name,n) || start[n] != '(') continue;
        p->at += n+1;
        int argument = formula_sum(p);
        if (!formula_take(p,')')) p->error = true;
        return formula_node(calls[i].kind,argument,0,NULL,0);
    }
    if (isalpha((unsigned char)*start)) {
        static const char *const names[] = {
            "lambda","theta","rho","delta","pi","Ek","Ep","Ee","dE","dT","dv","dt","Vp","Vs","Ip","Is"
        };
        size_t length = 1;
        for (size_t i = 0; i < sizeof(names)/sizeof(*names); i++) {
            size_t n = strlen(names[i]);
            if (!strncmp(start,names[i],n) && n > length) length = n;
        }
        while (isdigit((unsigned char)start[length])) length++;
        if (start[length] == '_') {
            length++;
            while (isalnum((unsigned char)start[length]) || start[length]=='_') length++;
        }
        p->at += length;
        return formula_node(Symbol,0,0,start,(int)length);
    }
    p->error = true;
    return 0;
}

static int formula_unary(FormulaParser *p) {
    if (formula_take(p,'+')) return formula_unary(p);
    if (formula_take(p,'-')) return operation(Minus,literal("0"),formula_unary(p));
    int a = formula_atom(p);
    if (formula_take(p,'^')) return operation(Power,a,formula_unary(p));
    return a;
}

static int formula_product(FormulaParser *p) {
    int a = formula_unary(p);
    while (!p->error && !formula_overflow) {
        formula_space(p);
        FormulaKind kind;
        if (formula_take(p,'*')) kind = Times;
        else if (formula_take(p,'/')) kind = Over;
        else if (*p->at == '(' || *p->at == '[' || isalpha((unsigned char)*p->at)) kind = Times;
        else break;
        a = operation(kind,a,formula_unary(p));
    }
    return a;
}

static int formula_sum(FormulaParser *p) {
    int a = formula_product(p);
    while (!p->error && !formula_overflow) {
        FormulaKind kind;
        if (formula_take(p,'+')) kind = Plus;
        else if (formula_take(p,'-')) kind = Minus;
        else break;
        a = operation(kind,a,formula_product(p));
    }
    return a;
}

static int occurrences(int id, const char *subject) {
    if (!id) return 0;
    const Formula *f = &formulas[id];
    if (f->kind == Symbol) return !strcmp(f->token,subject);
    return occurrences(f->a,subject)+occurrences(f->b,subject);
}

static int formula_precedence(FormulaKind kind) {
    if (kind == Plus || kind == Minus || kind == TwoSigns) return 1;
    if (kind == Times || kind == Over) return 2;
    if (kind == Power) return 3;
    return 4;
}

static void formula_text(int id, int level, char *text, size_t size) {
    if (!id) return;
    const Formula *f = &formulas[id];
    int precedence = formula_precedence(f->kind);
    if (precedence < level) add(text,size,"(");
    if (f->kind == Literal || f->kind == Symbol) add(text,size,"%s",f->token);
    else if (f->kind >= Root && f->kind <= FExp) {
        static const char *const names[] = {"sqrt","sin","cos","tan","asin","acos","atan","ln","exp"};
        add(text,size,"%s(",names[f->kind-Root]);
        formula_text(f->a,0,text,size);
        add(text,size,")");
    } else if (f->kind == TwoSigns) {
        add(text,size,"+/-");
        formula_text(f->a,precedence+1,text,size);
    } else {
        static const char *const symbols[] = {" + "," - ","*","/","^"};
        bool negative = f->kind == Minus && is_literal(f->a,"0");
        if (!negative) formula_text(f->a,precedence + (f->kind == Power),text,size);
        add(text,size,"%s",negative ? "-" : symbols[f->kind-Plus]);
        formula_text(f->b,precedence+(f->kind == Minus || f->kind == Over ||
                                     (f->kind == Times && formulas[f->b].kind == Over)),text,size);
    }
    if (precedence < level) add(text,size,")");
}

static void log_equation(Solution *s, int left, int right) {
    if (strlen(s->steps) >= sizeof(s->steps) - 40) return;
    formula_text(left,0,s->steps,sizeof(s->steps));
    add(s->steps,sizeof(s->steps)," = ");
    formula_text(right,0,s->steps,sizeof(s->steps));
    add(s->steps,sizeof(s->steps),"\n");
}

typedef struct { int coefficient, offset; } Linear;

static bool linear_in(int id, const char *subject, Linear *result) {
    if (!id) return false;
    if (!occurrences(id,subject)) {
        *result = (Linear){literal("0"),id};
        return true;
    }
    Formula f = formulas[id];
    if (f.kind == Symbol) {
        *result = (Linear){literal("1"),literal("0")};
        return true;
    }
    if (f.kind < Plus || f.kind > Over) return false;
    Linear a,b;
    if (!linear_in(f.a,subject,&a) || !linear_in(f.b,subject,&b)) return false;
    if (f.kind == Plus || f.kind == Minus) {
        *result = (Linear){operation(f.kind,a.coefficient,b.coefficient),operation(f.kind,a.offset,b.offset)};
    } else if (f.kind == Over && is_literal(b.coefficient,"0")) {
        *result = (Linear){operation(Over,a.coefficient,b.offset),operation(Over,a.offset,b.offset)};
    } else if (f.kind == Times && (is_literal(a.coefficient,"0") || is_literal(b.coefficient,"0"))) {
        int coefficient = is_literal(a.coefficient,"0") ? operation(Times,a.offset,b.coefficient) :
                                                          operation(Times,a.coefficient,b.offset);
        *result = (Linear){coefficient,operation(Times,a.offset,b.offset)};
    } else return false;
    return result->coefficient && result->offset && !formula_overflow;
}

void rearrange_physics(const char *equation, const char *subject, Solution *solution) {
    *solution = (Solution){0};
    while (isspace((unsigned char)*subject)) subject++;
    size_t len = strcspn(subject," \t\r\n");
    if (!len || len >= sizeof(formulas[0].token) || !isalpha((unsigned char)*subject)) {
        strcpy(solution->answer,"Enter the symbol to isolate, such as a.");
        return;
    }
    char name[20];
    memcpy(name,subject,len);
    name[len] = 0;
    for (size_t i = 0; i < len; i++) if (!isalnum((unsigned char)name[i]) && name[i]!='_') {
        strcpy(solution->answer,"Enter one symbol to isolate.");
        return;
    }
    const char *end = subject+len;
    while (isspace((unsigned char)*end)) end++;
    if (*end) { strcpy(solution->answer,"Enter one symbol to isolate."); return; }

    int depth = 0, operators = 0;
    for (const char *c = equation; *c; c++) {
        if (*c == '(') depth++;
        if (*c == ')') depth--;
        if (depth > 16 || (strchr("+-*/^(",*c) && ++operators > 36)) {
            strcpy(solution->answer,"The formula is too deeply nested.");
            return;
        }
    }
    formula_count = 0;
    formula_overflow = false;
    FormulaParser p = {equation,false};
    int left = formula_sum(&p);
    if (!formula_take(&p,'=')) p.error = true;
    int right = formula_sum(&p);
    formula_space(&p);
    if (*p.at || p.error || !left || !right || formula_overflow) {
        strcpy(solution->answer,"Enter a physics equation with one = sign. Use [name] for multi-letter symbols.");
        return;
    }
    int l = occurrences(left,name), r = occurrences(right,name);
    if (!l && !r) {
        strcpy(solution->answer,"The subject does not occur in the equation.");
        return;
    }
    if (!l) { int swap=left;left=right;right=swap; }
    if (l+r > 1) {
        Linear a,b;
        if (!linear_in(left,name,&a) || !linear_in(right,name,&b)) goto unsupported;
        int coefficient = operation(Minus,a.coefficient,b.coefficient);
        int rest = operation(Minus,b.offset,a.offset);
        if (!coefficient || is_literal(coefficient,"0")) goto unsupported;
        log_equation(solution,left,right);
        add(solution->steps,sizeof(solution->steps),"Collect all terms containing %s.\n",name);
        left = formula_node(Symbol,0,0,name,(int)len);
        log_equation(solution,operation(Times,coefficient,left),rest);
        add(solution->steps,sizeof(solution->steps),"Divide by its coefficient. It must be nonzero.\n");
        right = operation(Over,rest,coefficient);
    } else {
        log_equation(solution,left,right);
        while (left && formulas[left].kind != Symbol) {
            Formula f = formulas[left];
            bool in_a = occurrences(f.a,name) > 0;
            int other = in_a ? f.b : f.a;
            const char *step = NULL;
            switch (f.kind) {
                case Plus:
                    right = operation(Minus,right,other);
                    step = "Subtract the term without the subject.\n";
                    break;
                case Minus:
                    right = in_a ? operation(Plus,right,other) : operation(Minus,other,right);
                    step = in_a ? "Add the subtracted term.\n" : "Isolate the subtracted term.\n";
                    break;
                case Times:
                    right = operation(Over,right,other);
                    step = "Divide by the other factor (nonzero).\n";
                    break;
                case Over:
                    right = in_a ? operation(Times,right,other) : operation(Over,other,right);
                    step = in_a ? "Multiply by the denominator (nonzero).\n" :
                                  "Isolate the denominator. Check both divisors.\n";
                    break;
                case Power:
                    if (in_a) {
                        if (formulas[other].kind != Literal) goto unsupported;
                        char *finish;
                        double exponent = strtod(formulas[other].token,&finish);
                        if (*finish || exponent == 0 || exponent != trunc(exponent) || fabs(exponent) > 31)
                            goto unsupported;
                        if (exponent == 2) right = formula_node(Root,right,0,NULL,0);
                        else {
                            int magnitude = literal(formulas[other].token);
                            right = operation(Power,right,operation(Over,literal("1"),magnitude));
                        }
                        if ((int)exponent % 2 == 0) {
                            right = formula_node(TwoSigns,right,0,NULL,0);
                            step = "Take the root. Choose the sign from the physical context.\n";
                        } else step = "Raise both sides to the reciprocal power.\n";
                    } else {
                        right = operation(Over,formula_node(FLn,right,0,NULL,0),
                                          formula_node(FLn,other,0,NULL,0));
                        step = "Take logarithms. Use a positive base other than 1.\n";
                    }
                    break;
                case Root:
                    right = operation(Power,right,literal("2"));
                    step = "Square both sides. The original root must be nonnegative.\n";
                    break;
                case FSin: case FCos: case FTan:
                    right = formula_node((FormulaKind)(FAsin+f.kind-FSin),right,0,NULL,0);
                    step = "Take the principal inverse trig value. Check the physical angle range.\n";
                    break;
                case FExp: case FLn:
                    right = formula_node(f.kind==FExp?FLn:FExp,right,0,NULL,0);
                    step = f.kind==FExp ? "Take the natural logarithm of both sides (positive).\n" :
                                          "Take the exponential of both sides.\n";
                    break;
                default: goto unsupported;
            }
            if (!right || formula_overflow) goto unsupported;
            left = in_a ? f.a : f.b;
            add(solution->steps,sizeof(solution->steps),"%s",step);
            log_equation(solution,left,right);
        }
    }
    if (!left || !right || formula_overflow) goto unsupported;
    add(solution->answer,sizeof(solution->answer),"%s = ",name);
    formula_text(right,0,solution->answer,sizeof(solution->answer));
    if (strlen(solution->answer) >= sizeof(solution->answer)-1) goto unsupported;
    solution->ok = true;
    return;

unsupported:
    strcpy(solution->answer,"This formula cannot be isolated with these operations.");
    solution->steps[0] = 0;
}
