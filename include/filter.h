#ifndef FILTER_H

/* include -------------------------------------
------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

/* define, constant ----------------------------------------------
------------------------------------------------------------------*/

/*functions
-------------------------------------------------
-------------------------------------------------*/

float *butterworth_bandpass(int order, float *signal, int size, float sample_rate, float high_freq_cutoff, float low_freq_cutoff);
float *butterworth_lowpass(int order, float *signal, int size, float sample_rate, float cutoff_freq);

float *butterworth_bandpass_v2(int order, float *signal, int size, float sample_rate, float high_freq_cutoff, float low_freq_cutoff, float *A,
	float *d1, float *d2, float *d3, float *d4, float *w0, float *w1, float *w2, float *w3, float *w4, float *x);

#endif // !FILTER_H
