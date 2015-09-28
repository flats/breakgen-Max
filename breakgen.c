/**
	@file
	breakgen - an object for generating breakpoint files for modmetro~
	jeremy bernstein - jeremy@bootsquad.com

	@ingroup	examples	
*/

#include "ext.h"							// standard Max include, always required
#include "buffer.h"
#include "ext_atomic.h"
#include "ext_obex.h"						// required for new style Max object
#include "wave.h"

typedef struct t_rando {
    short       mode; /* mode of random/roughing */
    double      intensity; /* intensity factor for random/roughing - less than 1 */
    double      current; /* current random value */
    double      prev; /* previous random for calculating interpolated random */
    short       count; /* number of steps along interpolation */
    short       interval; /* total number of interpolating steps */
} RANDO;

typedef double (*randfunc) (RANDO* rando_gen, double val);

////////////////////////// object struct
typedef struct _breakgen 
{
	t_object	ob;
	t_atom		val;
	t_symbol	*name;
	void		*out;
    tickfunc    tick;
    float       sr; /* current sampling rate */
    OSCIL       *osc;
    float       freq;
    short       constsig; /* signal for the const wavetype */
    double      constval;
    RANDO       *rando_gen;
    randfunc    rando_func;
    t_bool      buffy_mod;
    t_buffer_ref *buffy;
} t_breakgen;

RANDO* new_rando();

double no_rando(RANDO* rando_gen, double val);
double rando_replace(RANDO* rando_gen, double val);
double rando_multi(RANDO* rando_gen, double val);

///////////////////////// function prototypes
//// standard set
void *breakgen_new(t_symbol *s, long argc, t_atom *argv);
void breakgen_free(t_breakgen *x);
void breakgen_assist(t_breakgen *x, void *b, long m, long a, char *s);

void breakgen_bang(t_breakgen *x);
void breakgen_identify(t_breakgen *x);
void breakgen_dblclick(t_breakgen *x);
void breakgen_acant(t_breakgen *x);

void breakgen_getrand(t_breakgen *x);

void breakgen_setter(t_breakgen *x, t_symbol *s, long argc, t_atom *argv);
void breakgen_wavetype(t_breakgen *x, long n);
void breakgen_setfreq(t_breakgen *x, double f);
void breakgen_setconstsig(t_breakgen *x, double f);
void breakgen_setsr(t_breakgen *x, double f);
void breakgen_writebuf(t_breakgen *x, t_symbol *s, long argc, t_atom *argv);
void breakgen_writefile(t_breakgen *x, t_symbol *s, long argc, t_atom *argv);

t_max_err breakgen_notify(t_breakgen *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
double output_val(t_breakgen *x);

static t_symbol *buffy_modified;
//////////////////////// global class pointer variable
void *breakgen_class;


int C74_EXPORT main(void)
{	
	t_class *c;
	
	c = class_new("breakgen", (method)breakgen_new, (method)breakgen_free, (long)sizeof(t_breakgen), 
				  0L /* leave NULL!! */, A_GIMME, 0);
	
    class_addmethod(c, (method)breakgen_bang,			"bang", 0);
    class_addmethod(c, (method)breakgen_identify,		"identify", 0);
	CLASS_METHOD_ATTR_PARSE(c, "identify", "undocumented", gensym("long"), 0, "1");

	// here's an otherwise undocumented method, which does something that the user can't actually 
	// do from the patcher however, we want them to know about it for some weird documentation reason. 
	// so let's make it documentable. it won't appear in the quickref, because we can't send it from a message.
	class_addmethod(c, (method)breakgen_acant,			"blooop",       A_CANT, 0);
	CLASS_METHOD_ATTR_PARSE(c, "blooop", "documentable", gensym("long"), 0, "1");
    
    class_addmethod(c, (method)breakgen_wavetype,		"wavetype",     A_LONG, 0);
    class_addmethod(c, (method)breakgen_setfreq,		"freq",         A_FLOAT, 0);
    class_addmethod(c, (method)breakgen_setconstsig,	"constval",     A_FLOAT, 0);
    class_addmethod(c, (method)breakgen_setsr,          "sr",           A_FLOAT, 0);
    
    class_addmethod(c, (method)breakgen_setter,          "set",         A_GIMME, 0);
    class_addmethod(c, (method)breakgen_writebuf,        "writebuf",    A_GIMME, 0);
    class_addmethod(c, (method)breakgen_writefile,       "writefile",   A_GIMME, 0);

	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)breakgen_assist,			"assist",		A_CANT, 0);  
    class_addmethod(c, (method)breakgen_dblclick,		"dblclick",		A_CANT, 0);
    class_addmethod(c, (method)breakgen_getrand,		"getrand",		A_CANT, 0);
	
	CLASS_ATTR_SYM(c, "name", 0, t_breakgen, name);
	
	class_register(CLASS_BOX, c);
	breakgen_class = c;
    
    buffy_modified = gensym("buffer_modified");

	return 0;
}

RANDO* new_rando() {
    RANDO* nr;
    
    nr = (RANDO*) malloc(sizeof(RANDO));
    if (nr == NULL) {
        return NULL;
    }
    nr->current = 1.0;
    nr->prev = 1.0;
    nr->count = 0;
    nr->intensity = 0.05;
    nr->interval = 1;
    nr->mode = 0;
    
    return nr;
}

double no_rando(RANDO* rando_gen, double val) {
    return val;
}

double rando_replace(RANDO* rando_gen, double val) {
    double rn;
    rn = ((double) rand()) / ((double) (RAND_MAX / 2.0));
    return rn;
}

double rando_multi(RANDO* rando_gen, double val) {
    double rn;
    rn = ((double) rand()) / ((double) (RAND_MAX / 2.0));
    return val - ((val - rn) * rando_gen->intensity); /* scale diff by intensity, subtract from val */
}

double rando_interp(RANDO* rando_gen, double val) {
    double rn;
    double progress;
    if (rando_gen->prev == rando_gen->current) {
        rando_gen->current = ((double) rand()) / ((double) (RAND_MAX / 2.0));
    }
    if (rando_gen->count <= 0) {
        rando_gen->prev = rando_gen->current;
        rando_gen->current = ((double) rand()) / ((double) (RAND_MAX / 2.0));
        rando_gen->count = rando_gen->interval;
    }
    progress = 1.0 - ( (double) rando_gen->count ) / ( (double) rando_gen->interval );
    rn = rando_gen->prev + ((rando_gen->current - rando_gen->prev) * progress);
    post("interval %i, count %i, current %f, prev %f, rn %f", rando_gen->interval, rando_gen->count, rando_gen->current, rando_gen->prev, rn);
    rando_gen->count--;
    // return val + (rn * rando_gen->intensity); /* scale diff by intensity, subtract from val */
    return val + ((rn - val) * rando_gen->intensity);
}

void breakgen_acant(t_breakgen *x)
{
	object_post((t_object *)x, "can't touch this!");
}

void breakgen_assist(t_breakgen *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	} 
	else {	// outlet
		sprintf(s, "I am outlet %ld", a); 			
	}
}

void breakgen_free(t_breakgen *x)
{
	free(x->osc);
    free(x->rando_gen);
    object_free(x->buffy);
}

void breakgen_dblclick(t_breakgen *x)
{
	object_post((t_object *)x, "I got a double-click");
}

void breakgen_setter(t_breakgen *x, t_symbol *s, long argc, t_atom *argv)
{
    t_atom *ap;
    int wavetype;
    
    ap = argv;
    
    if (atom_gettype(ap) == A_SYM) {
        if (atom_getsym(ap) == gensym("freq")) {
            ap++;
            if (atom_gettype(ap) == A_FLOAT) {
                if (atom_getfloat(ap) > 0.0) {
                    x->freq = atom_getfloat(ap);
                    post("freq set to %f", atom_getfloat(ap));
                } else {
                    post("frequency must be positive");
                }
            } else {
                post("set sr argument of incorrect type");
            }
        } else if (atom_getsym(ap) == gensym("constval")) {
            ap++;
            if (atom_gettype(ap) == A_FLOAT) {
                post("const val set to %f", atom_getfloat(ap));
                x->constval = atom_getfloat(ap);
            } else {
                post("set const val arg of incorrect type");
            }
        } else if (atom_getsym(ap) == gensym("wavetype")) {
            ap++;
            if (atom_gettype(ap) == A_LONG) {
                wavetype = atom_getlong(ap);
                if (wavetype < 6) {
                x->constsig = 0;
                    switch (wavetype) {
                        case 0:
                            /* sine */
                            x->tick = sinetick;
                            break;
                        case 1:
                            /* triange */
                            x->tick = tritick;
                            break;
                        case 2:
                            /* square */
                            x->tick = sqtick;
                            break;
                        case 3:
                            /* sawdown */
                            x->tick = sawdtick;
                            break;
                        case 4:
                            /* sawup */
                            x->tick = sawutick;
                            break;
                        case 5:
                            x->constsig = 1;
                            break;
                            
                        default:
                            x->tick = sinetick;
                            break;
                    }
                    post("wavetype set to %i", wavetype);
                } else {
                    post("wavetype must be between 0 and 5");
                }
            } else {
                post("set wavetype argument of incorrect type");
            }
        } else if (atom_getsym(ap) == gensym("random")) {
            ap++;
            if (atom_gettype(ap) == A_LONG) {
                wavetype = atom_getlong(ap);
                if (wavetype < 4) {
                    switch (wavetype) {
                        case 0:
                            /* no random number */
                            x->rando_func = no_rando;
                            break;
                        case 1:
                            /* replace value with random number */
                            x->rando_func = rando_replace;;
                            break;
                        case 2:
                            /* scale random and +/- from val */
                            x->rando_func = rando_multi;
                            break;
                        case 3:
                            /* scale random and +/- from val with interval interp */
                            x->rando_func = rando_interp;
                            break;
                            
                        default:
                            x->rando_func = no_rando;
                            break;
                    }
                    post("random mode set to %i", wavetype);
                } else {
                    post("random mode must be between 0 and 3");
                }
            } else {
                post("set random argument of incorrect type");
            }
        } else if (atom_getsym(ap) == gensym("interval")) {
            ap++;
            if (atom_gettype(ap) == A_LONG) {
                x->rando_gen->interval = atom_getlong(ap);
            } else {
                post("set random interval argument of incorrect type");
            }
        } else if (atom_getsym(ap) == gensym("intensity")) {
            ap++;
            if (atom_gettype(ap) == A_FLOAT) {
                x->rando_gen->intensity = atom_getfloat(ap);
            } else {
                post("set random intensity argument of incorrect type");
            }
        } else if (atom_getsym(ap) == gensym("buffer")) {
            t_symbol *symb;
            ap++;
            if (atom_gettype(ap) == A_SYM) {
                symb = atom_getsym(ap);
                x->buffy = buffer_ref_new((t_object *)x, symb);
                if (buffer_ref_exists(x->buffy) != 0) {
                    object_post((t_object *)x, "\"%s\" buffer referenced", symb->s_name);
                } else {
                    object_post((t_object *)x, "\"%s\" buffer referenced but doesn't exist", symb->s_name);
                };
            } else {
                post("set buffer argument of incorrect type");
            }
        } else if (atom_getsym(ap) == gensym("sr")) {
            ap++;
            if (atom_gettype(ap) == A_FLOAT) {
                if (atom_getfloat(ap) > 0.0) {
                    x->sr = atom_getfloat(ap);
                    free(x->osc);
                    x->osc = new_oscil(x->sr);
                    post("sampling rate set to %f", atom_getfloat(ap));
                } else {
                    post("sampling rate can't be negative");
                }
            } else {
                post("set sr arg of incorrect type");
            }
        }
    }
}

void breakgen_writebuf(t_breakgen *x, t_symbol *s, long argc, t_atom *argv)
{
    t_atom *ap;
    t_atom_long framecount;
    long num_frames;
    t_buffer_obj *buf;  // need to free this
    float *bufframe;
    t_max_err buferror;
    int i;
    
    ap = argv;
    
    if (atom_gettype(ap) == A_SYM) {
        x->buffy = buffer_ref_new((t_object *)x, atom_getsym(ap));
        if (buffer_ref_exists(x->buffy) != 0) {
            buf = buffer_ref_getobject(x->buffy);
            framecount = buffer_getframecount(buf);
            ap++;
            if (atom_gettype(ap) == A_LONG) {
                num_frames = atom_getlong(ap);
                if (num_frames < framecount) framecount = num_frames;
                bufframe = buffer_locksamples(buf);
                if (bufframe) {
                    for (i = 0; i < framecount; i++) {
                        *bufframe = output_val(x) - 1.0;
                        bufframe++;
                    }
                }
                buferror = buffer_setdirty(buf);
                buffer_unlocksamples(buf);
            }
        } else {
            post("buffer doesn't exist");
        };
    }
}

void breakgen_writefile(t_breakgen *x, t_symbol *s, long argc, t_atom *argv)
{
    t_atom *ap;
    long num_frames;
    // t_max_err buferror;
    float frame;
    int i;
    FILE *break_out;
    float amp = 1.0;
    
    short		path;
    char		ps[MAX_FILENAME_CHARS] = "";
    char        finalpath[MAX_PATH_CHARS];
    
    ap = argv;
    
    // if (atom_gettype(ap) == A_SYM) {
    //     if (atom_getsym(ap) != gensym("")) {
    //        *ps = atom_getsym(ap);
    //     }
    // }
    
    // strcpy(ps, "");
    
    if (saveas_dialog(ps,&path,NULL)) {
        return;
    }
    
    path_toabsolutesystempath(path, ps, finalpath);
    post(finalpath);
    
    if (atom_gettype(ap) == A_LONG) {
        if ((break_out = fopen(finalpath, "w"))) {
            post("file opened");
            num_frames = atom_getlong(ap);
            post("%i", argc);
            if (argc > 1) {
                ap++;
                if ( (atom_gettype(ap) == A_FLOAT) && (atom_getfloat(ap) < 1.0) ) {
                    amp = atom_getfloat(ap);
                }
            }
            for (i = 0; i < num_frames; i++) {
                frame = ((output_val(x) - 1) * amp) + 1;
                fprintf(break_out, "%f", frame);
                if (i + 1 != num_frames) {
                    fprintf(break_out, "\n");
                }
            }
            fclose(break_out);
            post("file closed");
        } else {
            post("couldn't create file");
        }
    } else {
        post("wrong atom type");
    }
}

double output_val(t_breakgen *x)
{
    double val;
    val = 0.0;
    
    if (x->constsig == 1) {
        val = x->constval;
    } else {
        val = x->tick(x->osc, x->freq) + 1;
    }
    
    val = x->rando_func(x->rando_gen, val);
    
    return val;
}

t_max_err breakgen_notify(t_breakgen *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
    if (msg == buffy_modified)
        x->buffy_mod = true;
    return buffer_ref_notify(x->buffy, s, msg, sender, data);
}


void breakgen_getrand(t_breakgen *x) {
    double rn;
    rn = ((double) rand()) / ((double) (RAND_MAX / 2.0));
    
    x->rando_gen->current = rn;
}

void breakgen_bang(t_breakgen *x)
{
    double val;
    val = 0.0;
    
    if (x->constsig == 1) {
        val = x->constval;
    } else {
        val = x->tick(x->osc, x->freq) + 1;
    }
    
    val = x->rando_func(x->rando_gen, val);
    
    outlet_float(x->out, val);
}

void breakgen_identify(t_breakgen *x)
{
	object_post((t_object *)x, "my name is %s", x->name->s_name);
}

void breakgen_setfreq(t_breakgen *x, double f)
{
    if (f > 0.0) {
        x->freq = f;
    }
    object_post((t_object *)x, "Frequency set to %f", x->freq);
}

void breakgen_setsr(t_breakgen *x, double f)
{
    if (f > 0.0) {
        x->sr = f;
        free(x->osc);
        x->osc = new_oscil(x->sr);
    }
    object_post((t_object *)x, "Sampling rate set to %f", x->freq);
}

void breakgen_setconstsig(t_breakgen *x, double f)
{
    if (f > 0.0) {
        x->constval = f;
    }
    object_post((t_object *)x, "Constant signal value set to %f", x->constval);
}

void breakgen_wavetype(t_breakgen *x, long n)
{
    post("Wave type set to %i", n);
    
    x->constsig = 0;
    
    if (n < 6) {
        switch (n) {
            case 0:
                /* sine */
                x->tick = sinetick;
                break;
            case 1:
                /* triange */
                x->tick = tritick;
                break;
            case 2:
                /* square */
                x->tick = sqtick;
                break;
            case 3:
                /* sawdown */
                x->tick = sawdtick;
                break;
            case 4:
                /* sawup */
                x->tick = sawutick;
                break;
            case 5:
                x->constsig = 1;
                break;
                
            default:
                x->tick = sinetick;
                break;
        }
    }
}

void *breakgen_new(t_symbol *s, long argc, t_atom *argv)
{
	t_breakgen *x = NULL;
    
	if ((x = (t_breakgen *)object_alloc(breakgen_class))) {
		x->name = gensym("");
		if (argc && argv) {
			x->name = atom_getsym(argv);
		}
		if (!x->name || x->name == gensym(""))
			x->name = symbol_unique();
		
		atom_setlong(&x->val, 0);
		x->out = outlet_new(x, NULL);
        
        x->constsig = 0;
        x->constval = 1.0;
        
        x->rando_gen = NULL;
        x->rando_gen = new_rando();
        if(x->rando_gen == NULL){
            post("no memory for random generator\n");
        }
        x->rando_func = no_rando;
        
        srand(time(NULL));
        
        x->tick = sinetick;
        x->sr = 10000.00;
        x->freq = 100.00;
        x->osc = NULL;
        x->osc = new_oscil(x->sr);
        if(x->osc == NULL){
            post("no memory for oscillator\n");
        }
        
        x->buffy = buffer_ref_new((t_object *)x, gensym("buffy"));
        if (buffer_ref_exists(x->buffy) != 0) {
            post("buf ref exists");
        } else {
            post("buf ref doesn't exist");
        };
	}
	return (x);
}
