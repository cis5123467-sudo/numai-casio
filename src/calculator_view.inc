/* The editor remains text-backed. The history and complete draft expressions
 * are laid out as two-dimensional maths while preserving the stored input. */
enum { CalcInputColumn, CalcExactColumn, CalcDecimalColumn, CalcDotsColumn };
enum { CalcTop=21, CalcBottom=EADK_SCREEN_HEIGHT };

static void math_text(int x,int y,const char *text,uint16_t ink,uint16_t paper,bool small) {
    casio_text(x,y,text,ink,paper,small,false,false);
}

static void large_math_text(int x,int y,const char *text,uint16_t ink,uint16_t paper,bool small) {
    casio_text(x,y,text,ink,paper,small,true,false);
}

static int imax(int a,int b) { return a>b?a:b; }

static void format_calc_decimal(char *text,size_t size,double value) {
    if (fabs(value)>=1e14) {
        snprintf(text,size,"%.*e",decimal_places,value);
        char *exponent=strchr(text,'e');
        if (exponent) {
            char *end=exponent;
            while (end>text && end[-1]=='0') end--;
            if (end>text && end[-1]=='.') end--;
            memmove(end,exponent,strlen(exponent)+1);
        }
        return;
    }
    snprintf(text,size,"%.*f",decimal_places,value);
    char *dot=strchr(text,'.');
    if (dot) {
        char *end=text+strlen(text);
        while (end>dot && end[-1]=='0') end--;
        if (end==dot+1) end=dot;
        *end=0;
    }
    if (!strcmp(text,"-0")) strcpy(text,"0");
}

static bool decimal_is_exact(const CalculationValue *value) {
    if (!value->denominator || value->radicand!=1) return false;
    int d=value->denominator, twos=0,fives=0;
    while (d%2==0) { d/=2; twos++; }
    while (d%5==0) { d/=5; fives++; }
    return d==1 && imax(twos,fives)<=decimal_places;
}

static bool has_decimal(const CalculationValue *value) {
    return value->numeric && (!*value->exact || value->denominator!=1 || value->radicand!=1);
}

static bool has_extras(const CalculationValue *value) {
    return value->numeric;
}

static bool calc_column_available(const CalcEntry *item,int column) {
    return column==CalcInputColumn ||
           (column==CalcExactColumn && *item->result.exact) ||
           (column==CalcDecimalColumn && has_decimal(&item->result)) ||
           (column==CalcDotsColumn && has_extras(&item->result));
}

static int default_calc_column(const CalcEntry *item) {
    return has_decimal(&item->result)?CalcDecimalColumn:CalcExactColumn;
}

typedef struct {
    MathBox input,exact,approx;
    char decimal[32];
    bool show_exact,show_approx,separate;
    int above,below,height,right;
} CalcFace;

static CalcFace calculation_face(const CalcEntry *item,bool selected) {
    CalcFace face={0};
    face.right=selected?EADK_SCREEN_WIDTH-36:EADK_SCREEN_WIDTH-9;
    face.show_approx=has_decimal(&item->result);
    face.show_exact=*item->result.exact && (selected || !face.show_approx ||
                     strcmp(item->input,item->result.exact));
    if (face.show_approx) format_calc_decimal(face.decimal,sizeof(face.decimal),item->result.value);
    face.input=measure_calculation(item->input,EADK_SCREEN_WIDTH - 20);
    if (face.show_exact) face.exact=measure_calculation(item->result.exact,160);
    if (face.show_approx) face.approx=measure_calculation(face.decimal,198);
    int right_width=face.exact.width+face.approx.width+(*item->result.exact&&face.show_approx?19:0);
    face.separate=face.input.width+right_width+29>face.right;
    if (face.separate) {
        face.above=imax(face.exact.above,face.approx.above);
        face.below=imax(face.exact.below,face.approx.below);
        face.height=face.input.above+face.input.below+face.above+face.below+21;
    } else {
        face.above=imax(face.input.above,imax(face.exact.above,face.approx.above));
        face.below=imax(face.input.below,imax(face.exact.below,face.approx.below));
        face.height=face.above+face.below+17;
    }
    if (face.height>164) face.height=164;
    return face;
}

static void calculation_part(const char *text,int limit,MathBox box,int x,int mid,
                             eadk_color_t ink,eadk_color_t paper,bool focused) {
    eadk_color_t background=focused?FocusTint:paper;
    if (focused) rectangle(x-2,mid-box.above-1,box.width+4,box.above+box.below+2,background);
    MathCanvas canvas={math_text,rectangle,ink,background};
    paint_math(text,limit,x,mid,&canvas);
}

static void large_calculation_part(const char *text,int limit,MathBox box,int x,int mid,
                                   eadk_color_t ink,eadk_color_t paper,bool focused) {
    eadk_color_t background = focused ? FocusTint : paper;
    if (focused) rectangle(x-2,mid-box.above-1,box.width+4,box.above+box.below+2,background);
    MathCanvas canvas = {large_math_text,rectangle,ink,background};
    paint_calculation(text,limit,x,mid,&canvas);
}

static void draw_calculation_row(int row,int top,CalcFace face,bool selected) {
    const CalcEntry *item=&calculations[row];
    eadk_color_t paper=row%2?HistoryTint:White;
    int column=selected?calc_column:-1;
    rectangle(0,top,EADK_SCREEN_WIDTH,face.height,paper);
    int mid=top+face.above+8, input_mid=mid;
    if (face.separate) {
        input_mid=top+face.input.above+6;
        mid=top+face.input.above+face.input.below+12+face.above;
    }
    large_calculation_part(item->input,EADK_SCREEN_WIDTH - 20,face.input,7,input_mid,Ink,paper,column==CalcInputColumn);
    int right=face.right;
    if (face.show_approx) {
        right-=face.approx.width;
        large_calculation_part(face.decimal,198,face.approx,right,mid,face.show_exact?Grey:Ink,paper,
                         column==CalcDecimalColumn);
        if (face.show_exact || *item->result.exact) {
            char sign[2]={decimal_is_exact(&item->result)?'=':MathApprox,0};
            string_at(right-13,mid-7,sign,face.show_exact?Grey:Ink,paper);
            right-=19;
        }
    }
    if (face.show_exact) {
        right-=face.exact.width;
        large_calculation_part(item->result.exact,160,face.exact,right,mid,Ink,paper,column==CalcExactColumn);
    }
    if (selected && has_extras(&item->result)) {
        eadk_color_t focus=column==CalcDotsColumn?FocusTint:paper;
        rectangle(EADK_SCREEN_WIDTH - 29,mid-8,23,16,focus);
        string_at(EADK_SCREEN_WIDTH - 28,mid-8,"...",Grey,focus);
    }
}

static void draw_calculator(void) {
    home_header();
    bool selecting=page==CalcHistory || page==CalcExtras;
    int edit_height=selecting ? 30 : expression_height(&prompt,EADK_SCREEN_WIDTH - 8,70,true);
    int editor=CalcBottom-edit_height-(pin_notice?15:0);
    rectangle(0,CalcTop,EADK_SCREEN_WIDTH,editor-CalcTop,HistoryTint);
    if (calc_count) {
        if (!selecting) calc_first=0;
        if (selecting && calc_row<calc_first) calc_first=calc_row;
        for (;;) {
            int bottom=editor, last=calc_first-1;
            for (int row=calc_first;row<calc_count;row++) {
                CalcFace face=calculation_face(&calculations[row],selecting&&row==calc_row);
                int top=bottom-face.height;
                if (top<CalcTop) break;
                draw_calculation_row(row,top,face,selecting&&row==calc_row);
                bottom=top;
                last=row;
            }
            if (!selecting || calc_row<=last || calc_first>=calc_row) break;
            calc_first++;
            rectangle(0,CalcTop,EADK_SCREEN_WIDTH,editor-CalcTop,HistoryTint);
        }
    }
    rectangle(0,editor,EADK_SCREEN_WIDTH,edit_height,White);
    rectangle(0,editor,EADK_SCREEN_WIDTH,1,Line);
    if (!selecting) expression_entry(4,editor+1,EADK_SCREEN_WIDTH - 8,edit_height-2,&prompt,"Type a calculation",true,true);
    else clipped(8,editor+7,prompt.text,TEXT_WIDTH,Grey,White);
    if (pin_notice) footer(pin_notice);
}

static void add_extra(const char *label,const char *text,const char *reuse) {
    if (extras_count>=EXTRA_LIMIT) return;
    ExtraResult *item=&extra_results[extras_count++];
    item->label=label;
    snprintf(item->text,sizeof(item->text),"%s",text);
    snprintf(item->reuse,sizeof(item->reuse),"%s",reuse?reuse:text);
}

static void multiple_pi(char text[64],int n,int d) {
    if (!n) strcpy(text,"0");
    else if (d==1) {
        if (abs(n)==1) snprintf(text,64,"%spi",n<0?"-":"");
        else snprintf(text,64,"%d*pi",n);
    } else if (abs(n)==1) snprintf(text,64,"%spi/%d",n<0?"-":"",d);
    else snprintf(text,64,"%d*pi/%d",n,d);
}

static void build_trig_extras(const CalculationValue *value) {
    const double pi=3.14159265358979323846;
    double rad=value->degrees?value->argument*(pi/180):value->argument;
    double deg=value->degrees?value->argument:value->argument*(180/pi);
    char exact[64],dec[32],input[96],shown[EXPRESSION_SIZE],argument[64];
    if (value->argument_rad==0 && value->argument_d && !value->degrees)
        multiple_pi(exact,value->argument_n,value->argument_d);
    else if (value->degrees && value->argument_d && value->argument_rad==1 &&
             fabs(value->argument)<=3600000) {
        // Find a small exact multiple of pi for the common school angles.
        int turns=(int)round(value->argument*12/180);
        if (fabs(value->argument-turns*15.0)<=1e-12) {
            int g=12,x=abs(turns);
            while (x) { int t=g%x; g=x; x=t; }
            multiple_pi(exact,turns/g,12/g);
        } else format_calc_decimal(exact,sizeof(exact),rad);
    } else format_calc_decimal(exact,sizeof(exact),rad);
    add_extra("Angle in radians",exact,exact);
    if (isfinite(deg)) {
        format_calc_decimal(dec,sizeof(dec),deg);
        add_extra("Angle in degrees",dec,dec);
    } else add_extra("Angle in degrees","Out of range","");
    if (!value->degrees && value->argument_rad==0 && value->argument_d)
        multiple_pi(argument,value->argument_n,value->argument_d);
    else snprintf(argument,sizeof(argument),"%.17g",value->argument);
    static const char *const trig[]={"sin","cos","tan"};
    for (int i=0;i<3;i++) {
        CalculationValue result;
        snprintf(input,sizeof(input),"%s(%s)",trig[i],argument);
        if (!cas_calculation(input,value->degrees,&result)) {
            add_extra(trig[i],"Undefined", "");
            continue;
        }
        format_calc_decimal(dec,sizeof(dec),result.value);
        if (*result.exact && has_decimal(&result)) {
            snprintf(shown,sizeof(shown),"%s %c %s",result.exact,
                     decimal_is_exact(&result)?'=':MathApprox,dec);
            add_extra(trig[i],shown,result.exact);
        } else add_extra(trig[i],*result.exact?result.exact:dec,*result.exact?result.exact:dec);
    }
}

static void prepare_calc_extras(void) {
    const CalculationValue *value=&calculations[calc_row].result;
    extras_count=extras_first=extras_row=0;
    if (value->kind>=ExtraSin) {
        build_trig_extras(value);
        return;
    }
    if (value->kind==ExtraRoot && value->argument>=0) {
        add_extra("Curve equation","y=sqrt(x)","sqrt(x)");
        return;
    }
    char scientific[36], shown[EXPRESSION_SIZE], reuse[EXPRESSION_SIZE];
    snprintf(scientific,sizeof(scientific),"%.*e",decimal_places,value->value);
    char *exponent=strchr(scientific,'e');
    if (exponent) {
        int e=atoi(exponent+1);
        char *end=exponent;
        while (end>scientific && end[-1]=='0') end--;
        if (end>scientific && end[-1]=='.') end--;
        *end=0;
        snprintf(shown,sizeof(shown),"%s*10^(%d)",scientific,e);
        add_extra("Scientific notation",shown,shown);
    }
    if (value->radicand!=1 || !value->denominator) return;
    int n=value->numerator,d=value->denominator;
    if (d>1) {
        int absolute=abs(n);
        snprintf(shown,sizeof(shown),"%s(%d+%d/%d)",n<0?"-":"",absolute/d,absolute%d,d);
        add_extra("Mixed fraction",shown,value->exact);
        int q=n/d,r=n%d;
        if (r<0) { q--; r+=d; }
        snprintf(shown,sizeof(shown),"%d=%d*(%d)+%d",n,d,q,r);
        add_extra("Euclidean division",shown,value->exact);
        return;
    }
    snprintf(shown,sizeof(shown),"%d",n);
    add_extra("Decimal",shown,shown);
    snprintf(shown,sizeof(shown),"%s0x%X",n<0?"-":"",(unsigned)abs(n));
    add_extra("Hexadecimal",shown,shown);
    unsigned number=(unsigned)abs(n);
    char bits[32];
    int count=0;
    do { bits[count++]='0'+(number&1u);number>>=1; } while (number);
    strcpy(shown,n<0?"-0b":"0b");
    int length=(int)strlen(shown);
    while (count) shown[length++]=bits[--count];
    shown[length]=0;
    add_extra("Binary",shown,shown);
    if (abs(n)>1) {
        int remaining=abs(n);
        strcpy(shown,n<0?"-1":"");
        for (int p=2;p<=remaining/p;p++) {
            int power=0;
            while (remaining%p==0) { remaining/=p;power++; }
            if (!power) continue;
            size_t size=strlen(shown);
            if (power>1) snprintf(shown+size,sizeof(shown)-size,"%s%d^%d",size?"*":"",p,power);
            else snprintf(shown+size,sizeof(shown)-size,"%s%d",size?"*":"",p);
        }
        if (remaining>1) {
            size_t size=strlen(shown);
            snprintf(shown+size,sizeof(shown)-size,"%s%d",size?"*":"",remaining);
        }
        snprintf(reuse,sizeof(reuse),"%s",shown);
        add_extra("Prime factors",shown,reuse);
    }
}

static void plot_line(int x,int y,int end_x,int end_y,eadk_color_t ink) {
    int dx=abs(end_x-x),step_x=x<end_x?1:-1;
    int dy=-abs(end_y-y),step_y=y<end_y?1:-1;
    int error=dx+dy;
    for (;;) {
        rectangle(x,y,1,1,ink);
        if (x==end_x && y==end_y) return;
        int e=2*error;
        if (e>=dy) { error+=dy; x+=step_x; }
        if (e<=dx) { error+=dx; y+=step_y; }
    }
}

static void plot_dashes(int x,int y,int finish,bool horizontal) {
    int start=horizontal?x:y;
    for (int p=start;p<=finish;p+=4) {
        if (horizontal) rectangle(p,y,1,1,PlotRed);
        else rectangle(x,p,1,1,PlotRed);
    }
}

static void draw_extra_plot(const CalculationValue *v,int y) {
    const double pi=3.14159265358979323846;
    const int x0=11,width=EADK_SCREEN_WIDTH - 22,height=80;
    rectangle(x0,y,width,height,White);
    if (v->kind==ExtraRoot) {
        int base=y+height-13,left=x0+13,span=width-30;
        double end=fmax(v->argument,1)*1.15;
        if (!isfinite(end)) end=v->argument;
        double scale=fmax(1,sqrt(end));
        int lift=height-22;
        rectangle(left,y+2,1,height-13,Ink);
        rectangle(left,base,span+4,1,Ink);
        int previous=base;
        for (int i=1;i<=span;i++) {
            int next=base-(int)round(lift*sqrt(end*((double)i/span))/scale);
            plot_line(left+i-1,previous,left+i,next,PlotRed);
            previous=next;
        }
        int px=left+(int)round(span*(v->argument/end));
        int py=base-(int)round(lift*sqrt(v->argument)/scale);
        plot_dashes(left,py,px,true);
        plot_dashes(px,py,base,false);
        rectangle(px-1,py-1,3,3,PlotRed);
        char label[30];
        snprintf(label,sizeof(label),"(%.4g, %.4g)",v->argument,v->value);
        string_at(x0 + 3,base-1,label,PlotRed,White);
    } else {
        int cx=x0+width/2,cy=y+height/2,r=33;
        rectangle(x0+5,cy,width-10,1,Line);
        rectangle(cx,y+3,1,height-6,Line);
        for (int i=0;i<160;i++) {
            double a=2*pi*i/160;
            rectangle(cx+(int)round(r*cos(a)),cy+(int)round(r*sin(a)),1,1,Ink);
        }
        double angle=v->degrees?v->argument*(pi/180):v->argument;
        int px=cx+(int)round(r*cos(angle)),py=cy-(int)round(r*sin(angle));
        plot_line(cx,cy,px,py,PlotRed);
        plot_dashes(px,py<cy?py:cy,py>cy?py:cy,false);
        plot_dashes(px<cx?px:cx,py,px>cx?px:cx,true);
        rectangle(px-1,py-1,3,3,PlotRed);
        string_at(x0+9,y+4,"Unit circle",Grey,White);
    }
}

static void draw_calc_extras(void) {
    const CalculationValue *value=&calculations[calc_row].result;
    const int y0=25,bottom=FOOTER - 3;
    rectangle(6,y0,EADK_SCREEN_WIDTH - 12,bottom-y0,ModalBar);
    rectangle(7,y0+21,EADK_SCREEN_WIDTH - 14,bottom-y0-22,White);
    string_at((EADK_SCREEN_WIDTH - casio_width("ADDITIONAL RESULTS",-1,false,false))/2,y0+3,"ADDITIONAL RESULTS",White,ModalBar);
    bool graph=value->kind!=ExtraNone;
    if (extras_row<extras_first) extras_first=extras_row;
    for (;;) {
        int y=y0+22+(graph&&extras_first==0?80:0), last=extras_first-1;
        for (int i=extras_first;i<extras_count;i++) {
            const ExtraResult *row=&extra_results[i];
            MathBox box=measure_math(row->text,EADK_SCREEN_WIDTH - 40);
            int h=box.above+box.below+18;
            if (y+h>bottom-1) break;
            y+=h;
            last=i;
        }
        if (extras_row<=last || extras_first>=extras_row) break;
        extras_first++;
    }
    int y=y0+22;
    if (graph && extras_first==0) {
        draw_extra_plot(value,y);
        y+=80;
    }
    for (int i=extras_first;i<extras_count;i++) {
        const ExtraResult *row=&extra_results[i];
        MathBox box=measure_math(row->text,EADK_SCREEN_WIDTH - 40);
        int h=box.above+box.below+18;
        bool mixed=!strcmp(row->label,"Mixed fraction");
        if (mixed) h=52;
        if (y+h>bottom-1 && i!=extras_first) break;
        if (y+h>bottom-1) h=bottom-y-1;
        eadk_color_t paper=i==extras_row?FocusTint:White;
        rectangle(8,y,EADK_SCREEN_WIDTH - 16,h,paper);
        int mid=y+box.above+2;
        if (mixed) {
            char whole[20],fraction[32];
            int n=abs(value->numerator),d=value->denominator;
            snprintf(whole,sizeof(whole),"%s%d",value->numerator<0?"-":"",n/d);
            snprintf(fraction,sizeof(fraction),"%d/%d",n%d,d);
            string_at(16,y+14,whole,Ink,paper);
            MathBox frac=measure_math(fraction,100);
            calculation_part(fraction,100,frac,16+casio_width(whole,-1,false,false)+3,y+19,Ink,paper,false);
        } else if (box.above+box.below+2<h) calculation_part(row->text,EADK_SCREEN_WIDTH - 40,box,16,mid,Ink,paper,false);
        else clipped(16,y+2,row->text,TEXT_WIDTH,Ink,paper);
        draw_menu_label(i, 16, y+h-15, Blue, paper);
        string_at(29,y+h-15,row->label,Grey,paper);
        rectangle(8,y+h-1,EADK_SCREEN_WIDTH - 16,1,Line);
        y+=h;
        if (y>=bottom-1) break;
    }
    rectangle(0,FOOTER,EADK_SCREEN_WIDTH,14,Light);
    string_at(5,FOOTER,"UP/DOWN: move   OK: insert   BACK",Grey,Light);
}
