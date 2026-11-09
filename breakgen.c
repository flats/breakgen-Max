/**
	@file
	breakgen - generates tempo multipliers (and breakpoint files of them) for modmetro~

	Each bang advances an oscillator (sine, triangle, square, saw down, saw up, or a
	constant) by freq/sr of a cycle, optionally randomizes the result, and outputs it
	offset to center on 1.0. modmetro~ multiplies each beat's length by one of these
	values. See docs/refpages/breakgen-ref/breakgen.maxref.xml for every message.

	D. Flaherty, started from the Cycling '74 Max SDK "simplemax" example.
*/

#include "ext.h"							// standard Max include, always required
#include "ext_obex.h"						// required for new style Max object
#include "ext_buffer.h"
#include "ext_atomic.h"
#include <stdlib.h>
#include <time.h>
#include "wave.h"

typedef struct t_rando {
    double      intensity; /* how far modes 2 and 3 pull toward the random value (attribute) */
    t_atom_long interval; /* steps between random targets in mode 3 (attribute) */
    double      current; /* current random value */
    double      prev; /* previous random for calculating interpolated random */
    t_atom_long count; /* steps left until the next random target */
} RANDO;

typedef double (*randfunc) (RANDO* rando_gen, double val);

////////////////////////// object struct
typedef struct _breakgen
{
	t_object	ob;
	void		*out;
    tickfunc    tick;
    OSCIL       *osc;
    short       constsig; /* signal for the const wavetype */
    randfunc    rando_func;
    RANDO       rando; /* random state; intensity and interval are attributes */
    t_bool      buffy_mod;
    t_buffer_ref *buffy;

    /* attributes */
    t_atom_long wavetype; /* 0 sine, 1 triangle, 2 square, 3 saw down, 4 saw up, 5 constant */
    double      freq; /* oscillator frequency */
    double      sr; /* oscillator steps per second */
    double      constval; /* value for the constant wavetype */
    t_atom_long random; /* 0 none, 1 replace, 2 multi, 3 multi interp */
    t_symbol    *buffer; /* buffer~ used by writebuf */
    double      depth; /* default writefile depth */
} t_breakgen;

double no_rando(RANDO* rando_gen, double val);
double rando_replace(RANDO* rando_gen, double val);
double rando_multi(RANDO* rando_gen, double val);
double rando_interp(RANDO* rando_gen, double val);

///////////////////////// function prototypes
//// standard set
void *breakgen_new(t_symbol *s, long argc, t_atom *argv);
void breakgen_free(t_breakgen *x);
void breakgen_assist(t_breakgen *x, void *b, long m, long a, char *s);

void breakgen_bang(t_breakgen *x);

void breakgen_getrand(t_breakgen *x);

void breakgen_setter(t_breakgen *x, t_symbol *s, long argc, t_atom *argv);
void breakgen_writebuf(t_breakgen *x, t_symbol *s, long argc, t_atom *argv);
void breakgen_writefile(t_breakgen *x, t_symbol *s, long argc, t_atom *argv);
void breakgen_dowritefile(t_breakgen *x, t_symbol *s, short argc, t_atom *argv);

t_max_err breakgen_notify(t_breakgen *x, t_symbol *s, t_symbol *msg, void *sender, void *data);
double output_val(t_breakgen *x);
t_max_err breakgen_set_wavetype(t_breakgen *x, t_atom_long n);
t_max_err breakgen_set_random(t_breakgen *x, t_atom_long n);
t_bool breakgen_isnum(t_atom *a);
t_bool breakgen_getpositive(t_breakgen *x, const char *name, long argc, t_atom *argv, double *out);

//// attribute setters
t_max_err breakgen_attr_wavetype_set(t_breakgen *x, void *attr, long argc, t_atom *argv);
t_max_err breakgen_attr_freq_set(t_breakgen *x, void *attr, long argc, t_atom *argv);
t_max_err breakgen_attr_sr_set(t_breakgen *x, void *attr, long argc, t_atom *argv);
t_max_err breakgen_attr_constval_set(t_breakgen *x, void *attr, long argc, t_atom *argv);
t_max_err breakgen_attr_random_set(t_breakgen *x, void *attr, long argc, t_atom *argv);
t_max_err breakgen_attr_intensity_set(t_breakgen *x, void *attr, long argc, t_atom *argv);
t_max_err breakgen_attr_interval_set(t_breakgen *x, void *attr, long argc, t_atom *argv);
t_max_err breakgen_attr_buffer_set(t_breakgen *x, void *attr, long argc, t_atom *argv);
t_max_err breakgen_attr_depth_set(t_breakgen *x, void *attr, long argc, t_atom *argv);

static t_symbol *buffy_modified;
//////////////////////// global class pointer variable
void *breakgen_class;


void ext_main(void *r)
{
	t_class *c;

	c = class_new("breakgen", (method)breakgen_new, (method)breakgen_free, (long)sizeof(t_breakgen),
				  0L /* leave NULL!! */, A_GIMME, 0);

    class_addmethod(c, (method)breakgen_bang,			"bang", 0);

    class_addmethod(c, (method)breakgen_setter,          "set",         A_GIMME, 0);
    class_addmethod(c, (method)breakgen_writebuf,        "writebuf",    A_GIMME, 0);
    class_addmethod(c, (method)breakgen_writefile,       "writefile",   A_GIMME, 0);

	/* you CAN'T call this from the patcher */
    class_addmethod(c, (method)breakgen_assist,			"assist",		A_CANT, 0);
    class_addmethod(c, (method)breakgen_getrand,		"getrand",		A_CANT, 0);
    class_addmethod(c, (method)breakgen_notify,			"notify",		A_CANT, 0); // needed by buffer_ref

	/* Attributes. Each one also responds to a message of the same name ("freq 100"),
	   can be typed into the object box ("@freq 100"), and is saved with the patcher
	   when changed in the inspector. The setters reject invalid values with an error. */
	CLASS_ATTR_LONG(c, "wavetype", 0, t_breakgen, wavetype);
	CLASS_ATTR_ACCESSORS(c, "wavetype", NULL, breakgen_attr_wavetype_set);
	CLASS_ATTR_ENUMINDEX(c, "wavetype", 0, "sine triangle square \"saw down\" \"saw up\" constant");
	CLASS_ATTR_LABEL(c, "wavetype", 0, "Waveform");

	CLASS_ATTR_DOUBLE(c, "freq", 0, t_breakgen, freq);
	CLASS_ATTR_ACCESSORS(c, "freq", NULL, breakgen_attr_freq_set);
	CLASS_ATTR_LABEL(c, "freq", 0, "Frequency");

	CLASS_ATTR_DOUBLE(c, "sr", 0, t_breakgen, sr);
	CLASS_ATTR_ACCESSORS(c, "sr", NULL, breakgen_attr_sr_set);
	CLASS_ATTR_LABEL(c, "sr", 0, "Steps per Second");

	CLASS_ATTR_DOUBLE(c, "constval", 0, t_breakgen, constval);
	CLASS_ATTR_ACCESSORS(c, "constval", NULL, breakgen_attr_constval_set);
	CLASS_ATTR_LABEL(c, "constval", 0, "Constant Value");

	CLASS_ATTR_LONG(c, "random", 0, t_breakgen, random);
	CLASS_ATTR_ACCESSORS(c, "random", NULL, breakgen_attr_random_set);
	CLASS_ATTR_ENUMINDEX(c, "random", 0, "\"no random\" replace multi \"multi interp\"");
	CLASS_ATTR_LABEL(c, "random", 0, "Random Mode");

	CLASS_ATTR_DOUBLE(c, "intensity", 0, t_breakgen, rando.intensity);
	CLASS_ATTR_ACCESSORS(c, "intensity", NULL, breakgen_attr_intensity_set);
	CLASS_ATTR_LABEL(c, "intensity", 0, "Random Intensity");

	CLASS_ATTR_LONG(c, "interval", 0, t_breakgen, rando.interval);
	CLASS_ATTR_ACCESSORS(c, "interval", NULL, breakgen_attr_interval_set);
	CLASS_ATTR_LABEL(c, "interval", 0, "Random Interval");

	CLASS_ATTR_SYM(c, "buffer", 0, t_breakgen, buffer);
	CLASS_ATTR_ACCESSORS(c, "buffer", NULL, breakgen_attr_buffer_set);
	CLASS_ATTR_LABEL(c, "buffer", 0, "Buffer");

	CLASS_ATTR_DOUBLE(c, "depth", 0, t_breakgen, depth);
	CLASS_ATTR_ACCESSORS(c, "depth", NULL, breakgen_attr_depth_set);
	CLASS_ATTR_LABEL(c, "depth", 0, "File Depth");

	CLASS_ATTR_CATEGORY(c, "wavetype", 0, "Oscillator");
	CLASS_ATTR_CATEGORY(c, "freq", 0, "Oscillator");
	CLASS_ATTR_CATEGORY(c, "sr", 0, "Oscillator");
	CLASS_ATTR_CATEGORY(c, "constval", 0, "Oscillator");
	CLASS_ATTR_CATEGORY(c, "random", 0, "Random");
	CLASS_ATTR_CATEGORY(c, "intensity", 0, "Random");
	CLASS_ATTR_CATEGORY(c, "interval", 0, "Random");
	CLASS_ATTR_CATEGORY(c, "buffer", 0, "Output");
	CLASS_ATTR_CATEGORY(c, "depth", 0, "Output");

	CLASS_ATTR_DEFAULT_SAVE(c, "wavetype", 0, "0");
	CLASS_ATTR_DEFAULT_SAVE(c, "freq", 0, "100.");
	CLASS_ATTR_DEFAULT_SAVE(c, "sr", 0, "10000.");
	CLASS_ATTR_DEFAULT_SAVE(c, "constval", 0, "1.");
	CLASS_ATTR_DEFAULT_SAVE(c, "random", 0, "0");
	CLASS_ATTR_DEFAULT_SAVE(c, "intensity", 0, "0.05");
	CLASS_ATTR_DEFAULT_SAVE(c, "interval", 0, "1");
	CLASS_ATTR_SAVE(c, "buffer", 0);
	CLASS_ATTR_DEFAULT_SAVE(c, "depth", 0, "1.");

	CLASS_ATTR_ORDER(c, "wavetype", 0, "1");
	CLASS_ATTR_ORDER(c, "freq", 0, "2");
	CLASS_ATTR_ORDER(c, "sr", 0, "3");
	CLASS_ATTR_ORDER(c, "constval", 0, "4");
	CLASS_ATTR_ORDER(c, "random", 0, "5");
	CLASS_ATTR_ORDER(c, "intensity", 0, "6");
	CLASS_ATTR_ORDER(c, "interval", 0, "7");
	CLASS_ATTR_ORDER(c, "buffer", 0, "8");
	CLASS_ATTR_ORDER(c, "depth", 0, "9");

	CLASS_ATTR_BASIC(c, "wavetype", 0);
	CLASS_ATTR_BASIC(c, "freq", 0);
	CLASS_ATTR_BASIC(c, "sr", 0);
	CLASS_ATTR_BASIC(c, "random", 0);

	class_register(CLASS_BOX, c);
	breakgen_class = c;

    buffy_modified = gensym("buffer_modified");
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
    rando_gen->count--;
    // return val + (rn * rando_gen->intensity); /* scale diff by intensity, subtract from val */
    return val + ((rn - val) * rando_gen->intensity);
}

/* hover help for the inlet and outlet (Max passes a 512-byte buffer) */
void breakgen_assist(t_breakgen *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) {
		strncpy_zero(s, "(bang) Output the next tempo multiplier, (messages) attributes, set, writefile, writebuf", 512);
	}
	else {
		strncpy_zero(s, "(float) Tempo multiplier for the next beat's length: 1.0 = unchanged, 1.1 = 10% longer (slower), 0.9 = 10% shorter (faster)", 512);
	}
}

void breakgen_free(t_breakgen *x)
{
	free(x->osc);
    object_free(x->buffy);
}

/* "set <attribute> <value>" is kept for patches written before these were attributes */
void breakgen_setter(t_breakgen *x, t_symbol *s, long argc, t_atom *argv)
{
    static const char *names[] = { "wavetype", "freq", "sr", "constval", "random",
                                   "intensity", "interval", "buffer", "depth" };
    t_symbol *param;
    size_t i;

    /* every "set" option takes a name and exactly one value */
    if (argc < 2 || atom_gettype(argv) != A_SYM) {
        object_error((t_object *)x, "set expects a parameter name and a value, e.g. \"set freq 100\"");
        return;
    }
    param = atom_getsym(argv);
    for (i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
        if (param == gensym(names[i])) {
            object_attr_setvalueof(x, param, 1, argv + 1); /* the attribute's setter validates it */
            return;
        }
    }
    object_error((t_object *)x, "set: unknown parameter \"%s\"", param->s_name);
}

/* writebuf <frames> uses the buffer attribute; writebuf <name> <frames> sets it first */
void breakgen_writebuf(t_breakgen *x, t_symbol *s, long argc, t_atom *argv)
{
    t_atom_long framecount;
    t_atom_long num_frames;
    t_atom_long chans;
    t_buffer_obj *buf;  // owned by the buffer~ object, not by us
    float *bufframe;
    float val;
    t_atom_long i, c;

    if (argc >= 2 && atom_gettype(argv) == A_SYM && breakgen_isnum(argv + 1)) {
        object_attr_setvalueof(x, gensym("buffer"), 1, argv);
        num_frames = atom_getlong(argv + 1);
    } else if (argc >= 1 && breakgen_isnum(argv)) {
        num_frames = atom_getlong(argv);
    } else {
        object_error((t_object *)x, "writebuf expects a number of frames, optionally after a buffer~ name, e.g. \"writebuf 1000\" or \"writebuf mybuffer 1000\"");
        return;
    }

    if (x->buffer == gensym("")) {
        object_error((t_object *)x, "writebuf: no buffer~ set; use the buffer attribute or \"writebuf <name> <frames>\"");
        return;
    }
    buf = buffer_ref_getobject(x->buffy);
    if (!buf) {
        object_error((t_object *)x, "buffer~ \"%s\" doesn't exist", x->buffer->s_name);
        return;
    }

    framecount = buffer_getframecount(buf);
    if (num_frames < framecount) framecount = num_frames;
    chans = buffer_getchannelcount(buf);

    bufframe = buffer_locksamples(buf);
    if (!bufframe) {
        object_error((t_object *)x, "couldn't access the samples of buffer~ \"%s\"", x->buffer->s_name);
        return;
    }
    /* samples are interleaved by channel, so write each value to every channel of the frame */
    for (i = 0; i < framecount; i++) {
        val = output_val(x) - 1.0;
        for (c = 0; c < chans; c++) {
            *bufframe++ = val;
        }
    }
    buffer_setdirty(buf);
    buffer_unlocksamples(buf);
}

void breakgen_writefile(t_breakgen *x, t_symbol *s, long argc, t_atom *argv)
{
    if (argc < 1 || !breakgen_isnum(argv)) {
        object_error((t_object *)x, "writefile expects a number of frames and an optional depth, e.g. \"writefile 2000 0.2\"");
        return;
    }
    /* the save dialog must run on the main thread, so do the work there (defer_low copies the atoms) */
    defer_low(x, (method)breakgen_dowritefile, s, (short)(argc > 2 ? 2 : argc), argv);
}

void breakgen_dowritefile(t_breakgen *x, t_symbol *s, short argc, t_atom *argv)
{
    t_atom_long num_frames;
    t_atom_long i;
    float frame;
    FILE *break_out;
    float amp;

    short		path;
    char		ps[MAX_FILENAME_CHARS] = "";
    char        finalpath[MAX_PATH_CHARS];

    num_frames = atom_getlong(argv);
    /* an explicit depth overrides the depth attribute; as before, 1 or more means full depth */
    amp = x->depth;
    if (argc > 1 && breakgen_isnum(argv + 1)) {
        amp = atom_getfloat(argv + 1) < 1.0 ? atom_getfloat(argv + 1) : 1.0;
    }

    if (saveas_dialog(ps,&path,NULL)) {
        return; /* cancelled */
    }
    path_toabsolutesystempath(path, ps, finalpath);

    if (!(break_out = fopen(finalpath, "w"))) {
        object_error((t_object *)x, "couldn't create file %s", finalpath);
        return;
    }
    for (i = 0; i < num_frames; i++) {
        frame = ((output_val(x) - 1) * amp) + 1;
        fprintf(break_out, "%f", frame);
        if (i + 1 != num_frames) {
            fprintf(break_out, "\n");
        }
    }
    fclose(break_out);
    object_post((t_object *)x, "wrote %lld values to %s", (long long)num_frames, finalpath);
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

    val = x->rando_func(&x->rando, val);

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

    x->rando.current = rn;
}

void breakgen_bang(t_breakgen *x)
{
    outlet_float(x->out, output_val(x));
}

t_max_err breakgen_set_wavetype(t_breakgen *x, t_atom_long n)
{
    if (n < 0 || n > 5) {
        object_error((t_object *)x, "wavetype must be between 0 and 5");
        return MAX_ERR_GENERIC;
    }

    x->wavetype = n;
    x->constsig = 0;

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
    }
    return MAX_ERR_NONE;
}

t_max_err breakgen_set_random(t_breakgen *x, t_atom_long n)
{
    if (n < 0 || n > 3) {
        object_error((t_object *)x, "random mode must be between 0 and 3");
        return MAX_ERR_GENERIC;
    }

    x->random = n;

    switch (n) {
        case 0:
            /* no random number */
            x->rando_func = no_rando;
            break;
        case 1:
            /* replace value with random number */
            x->rando_func = rando_replace;
            break;
        case 2:
            /* scale random and +/- from val */
            x->rando_func = rando_multi;
            break;
        case 3:
            /* scale random and +/- from val with interval interp */
            x->rando_func = rando_interp;
            break;
    }
    return MAX_ERR_NONE;
}

/* true for ints and floats, so "freq 100" works as well as "freq 100." */
t_bool breakgen_isnum(t_atom *a)
{
    return atom_gettype(a) == A_LONG || atom_gettype(a) == A_FLOAT;
}

/* read a single number greater than 0 for the attribute called name */
t_bool breakgen_getpositive(t_breakgen *x, const char *name, long argc, t_atom *argv, double *out)
{
    if (argc < 1 || !argv || !breakgen_isnum(argv)) {
        object_error((t_object *)x, "%s needs a number", name);
        return false;
    }
    if (atom_getfloat(argv) <= 0.0) {
        object_error((t_object *)x, "%s must be greater than 0", name);
        return false;
    }
    *out = atom_getfloat(argv);
    return true;
}

t_max_err breakgen_attr_wavetype_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    if (argc < 1 || !argv || !breakgen_isnum(argv)) {
        object_error((t_object *)x, "wavetype needs a number from 0 to 5");
        return MAX_ERR_GENERIC;
    }
    return breakgen_set_wavetype(x, atom_getlong(argv));
}

t_max_err breakgen_attr_freq_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    double f;
    if (!breakgen_getpositive(x, "freq", argc, argv, &f)) {
        return MAX_ERR_GENERIC;
    }
    x->freq = f;
    return MAX_ERR_NONE;
}

/* changing sr also restarts the waveform from the beginning of its cycle */
t_max_err breakgen_attr_sr_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    double f;
    OSCIL *osc;
    if (!breakgen_getpositive(x, "sr", argc, argv, &f)) {
        return MAX_ERR_GENERIC;
    }
    if (!(osc = new_oscil(f))) {
        object_error((t_object *)x, "out of memory");
        return MAX_ERR_OUT_OF_MEM;
    }
    free(x->osc);
    x->osc = osc;
    x->sr = f;
    return MAX_ERR_NONE;
}

t_max_err breakgen_attr_constval_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    double f;
    if (!breakgen_getpositive(x, "constval", argc, argv, &f)) {
        return MAX_ERR_GENERIC;
    }
    x->constval = f;
    return MAX_ERR_NONE;
}

t_max_err breakgen_attr_random_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    if (argc < 1 || !argv || !breakgen_isnum(argv)) {
        object_error((t_object *)x, "random needs a number from 0 to 3");
        return MAX_ERR_GENERIC;
    }
    return breakgen_set_random(x, atom_getlong(argv));
}

t_max_err breakgen_attr_intensity_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    if (argc < 1 || !argv || !breakgen_isnum(argv)) {
        object_error((t_object *)x, "intensity needs a number");
        return MAX_ERR_GENERIC;
    }
    x->rando.intensity = atom_getfloat(argv);
    return MAX_ERR_NONE;
}

t_max_err breakgen_attr_interval_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    t_atom_long n;
    if (argc < 1 || !argv || !breakgen_isnum(argv) || (n = atom_getlong(argv)) < 1) {
        object_error((t_object *)x, "interval must be a whole number of at least 1");
        return MAX_ERR_GENERIC;
    }
    x->rando.interval = n;
    if (x->rando.count > n) {
        x->rando.count = n; /* don't let a glide in progress overshoot the new interval */
    }
    return MAX_ERR_NONE;
}

t_max_err breakgen_attr_buffer_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    t_symbol *name = gensym("");
    if (argc >= 1 && argv) {
        if (atom_gettype(argv) != A_SYM) {
            object_error((t_object *)x, "buffer needs a buffer~ name");
            return MAX_ERR_GENERIC;
        }
        name = atom_getsym(argv);
    }
    x->buffer = name;
    buffer_ref_set(x->buffy, name);
    return MAX_ERR_NONE;
}

t_max_err breakgen_attr_depth_set(t_breakgen *x, void *attr, long argc, t_atom *argv)
{
    if (argc < 1 || !argv || !breakgen_isnum(argv) || atom_getfloat(argv) < 0.0 || atom_getfloat(argv) > 1.0) {
        object_error((t_object *)x, "depth must be a number from 0 to 1");
        return MAX_ERR_GENERIC;
    }
    x->depth = atom_getfloat(argv);
    return MAX_ERR_NONE;
}

void *breakgen_new(t_symbol *s, long argc, t_atom *argv)
{
	t_breakgen *x = NULL;

	if ((x = (t_breakgen *)object_alloc(breakgen_class))) {
		x->out = outlet_new(x, NULL);

        /* defaults (matching the attributes' default values); typed-in @attributes are applied below */
        x->wavetype = 0;
        x->tick = sinetick;
        x->constsig = 0;
        x->freq = 100.0;
        x->sr = 10000.0;
        x->constval = 1.0;

        x->random = 0;
        x->rando_func = no_rando;
        x->rando.intensity = 0.05;
        x->rando.interval = 1;
        x->rando.current = 1.0;
        x->rando.prev = 1.0;
        x->rando.count = 0;

        x->depth = 1.0;
        x->buffer = gensym("");
        x->buffy = buffer_ref_new((t_object *)x, x->buffer);

        srand(time(NULL));

        x->osc = new_oscil(x->sr);
        if (!x->osc) {
            object_error((t_object *)x, "out of memory");
            object_free(x);
            return NULL;
        }

        attr_args_process(x, (short)argc, argv);
	}
	return (x);
}
