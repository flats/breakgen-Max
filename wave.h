//
//  wave.h
//  
//
//  Created by Robador Mobile on 11/17/14.
//
//

#ifndef _wave_h
#define _wave_h

#ifndef M_PI
#define M_PI (3.1415926535897932)
#endif
#define TWOPI (2.0 * M_PI)

typedef struct t_oscil {
    double twopiovrsr;
    double curfreq;
    double curphase;
    double incr;
} OSCIL;

typedef double (*tickfunc) (OSCIL* osc, double freq);

OSCIL* new_oscil(double srate);
double sinetick(OSCIL* p_osc, double freq);
double sqtick(OSCIL* p_osc, double freq);
double sawdtick(OSCIL* p_osc, double freq);
double sawutick(OSCIL* p_osc, double freq);
double tritick(OSCIL* p_osc, double freq);
double pwmtick(OSCIL* p_osc, double freq, double pwmod);

#endif