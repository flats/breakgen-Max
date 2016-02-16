//
//  wave.c
//
//  Copyright (c) 2009 Richard Dobson
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "wave.h"

/* local typing-saving macro for tick functions */
#define OSC_WRAPPHASE  if(p_osc->curphase >= TWOPI) p_osc->curphase -= TWOPI;	\
if(p_osc->curphase < 0.0) p_osc->curphase += TWOPI

OSCIL* new_oscil(double srate) {
    OSCIL* p_osc;
    
    p_osc = (OSCIL*) malloc(sizeof(OSCIL));
    if (p_osc == NULL) {
        return NULL;
    }
    p_osc->twopiovrsr = TWOPI / (double) srate;
    p_osc->curfreq = 0.0;
    p_osc->curphase = 0.0;
    p_osc->incr = 0.0;
    
    return p_osc;
}

double sinetick(OSCIL* p_osc, double freq) {
    double val;
    
    val = sin(p_osc->curphase);
    if (p_osc->curfreq != freq) {
        p_osc->curfreq = freq;
        p_osc->incr = freq * p_osc->twopiovrsr;
    }
    p_osc->curphase += p_osc->incr;
    OSC_WRAPPHASE;
    return val;
}

double sqtick(OSCIL* p_osc, double freq) {
	double val;
    
	if(p_osc->curfreq != freq){
		p_osc->curfreq = freq;
		p_osc->incr = p_osc->twopiovrsr * freq;
	}
    
	if(p_osc->curphase <= M_PI)
		val = 1.0;
	else
		val = -1;
	p_osc->curphase += p_osc->incr;
	OSC_WRAPPHASE;
	return val;
}

double pwmtick(OSCIL* p_osc, double freq, double pwmod) {
	double val;
    
	if(p_osc->curfreq != freq){
		p_osc->curfreq = freq;
		p_osc->incr = p_osc->twopiovrsr * freq;
	}

    pwmod *= 0.99;
    if (pwmod < 0.0) {
        pwmod *= -1.0;
    }
    if (pwmod < 0.01) {
        pwmod += 0.01;
    }
//    pwmod = (pwmod * 0.5) + 0.25;
    
	if(p_osc->curphase <= (TWOPI * pwmod))
		val = 1.0;
	else
		val = -1;
	p_osc->curphase += p_osc->incr;
	OSC_WRAPPHASE;
	return val;
}

double sawdtick(OSCIL* p_osc, double freq) {
	double val;
    
	if(p_osc->curfreq != freq){
		p_osc->curfreq = freq;
		p_osc->incr = p_osc->twopiovrsr * freq;
	}
	val =  1.0 - 2.0 * (p_osc->curphase * (1.0 / TWOPI));
	p_osc->curphase += p_osc->incr;
	OSC_WRAPPHASE;
	return val;
}

double sawutick(OSCIL* p_osc, double freq) {
	double val;
    
	if(p_osc->curfreq != freq){
		p_osc->curfreq = freq;
		p_osc->incr = p_osc->twopiovrsr * freq;
	}
	val =  (2.0 * (p_osc->curphase * (1.0 / TWOPI) )) - 1.0;
	p_osc->curphase += p_osc->incr;
	OSC_WRAPPHASE;
	return val;
}

double tritick(OSCIL* p_osc, double freq) {
	double val;
    
	if(p_osc->curfreq != freq){
		p_osc->curfreq = freq;
		p_osc->incr = p_osc->twopiovrsr * freq;
	}
	if(p_osc->curphase <= M_PI)	{
		val = (4.0 * (p_osc->curphase * (1.0 / TWOPI))) - 1.0;
	}
	else {
		val = 3.0 - 4.0 * (p_osc->curphase * (1.0 / TWOPI));
	}
	p_osc->curphase += p_osc->incr;
	OSC_WRAPPHASE;
	return val;
}