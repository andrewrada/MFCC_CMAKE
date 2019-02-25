#include "filter.h"

float * butterworth_bandpass(int order, float * signal, int size, float sample_rate, float high_freq_cutoff, float low_freq_cutoff)
{
	if (order % 4) {
		fprintf(stderr, "order must be 4,8,12,16,...\n");
		exit(1);
	}
	float a = cos(M_PI * (high_freq_cutoff + low_freq_cutoff) / sample_rate) / cos(M_PI * (high_freq_cutoff - low_freq_cutoff) / sample_rate);
	float a_2 = a * a;
	float b = tan(M_PI * (high_freq_cutoff - low_freq_cutoff) / sample_rate);
	float b_2 = b * b;
	float r;

	order = order / 4;
	float *A = (float *)malloc(sizeof(float) * order);
	float *d1 = (float *)malloc(sizeof(float) * order);
	float *d2 = (float *)malloc(sizeof(float) * order);
	float *d3 = (float *)malloc(sizeof(float) * order);
	float *d4 = (float *)malloc(sizeof(float) * order);
	float *w0 = (float *)calloc(order, sizeof(float));
	float *w1 = (float *)calloc(order, sizeof(float));
	float *w2 = (float *)calloc(order, sizeof(float));
	float *w3 = (float *)calloc(order, sizeof(float));
	float *w4 = (float *)calloc(order, sizeof(float));
	float *x = (float *)malloc(sizeof(float) * size);
	for (int i = 0; i < order; ++i) {
		r = sin(M_PI * (2.0 * i + 1.0) / (4.0 * order));
		sample_rate = b_2 + 2.0 * b * r + 1.0;
		A[i] = b_2 / sample_rate;
		d1[i] = 4.0 * a * (1.0 + b * r) / sample_rate;
		d2[i] = 2.0 * (b_2 - 2.0 * a_2 - 1.0) / sample_rate;
		d3[i] = 4.0 * a * (1.0 - b * r) / sample_rate;
		d4[i] = -(b_2 - 2.0 * b * r + 1.0) / sample_rate;
	}
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < order; ++j) {
			if (j == 0) {
				w0[j] = d1[j] * w1[j] + d2[j] * w2[j] + d3[j] * w3[j] + d4[j] * w4[j] + signal[i];
			}
			else {
				w0[j] = d1[j] * w1[j] + d2[j] * w2[j] + d3[j] * w3[j] + d4[j] * w4[j] + x[i];
			}
			x[i] = A[j] * (w0[j] - 2.0 * w2[j] + w4[j]);
			w4[j] = w3[j];
			w3[j] = w2[j];
			w2[j] = w1[j];
			w1[j] = w0[j];
		}
	}
	free(A);
	free(d1);
	free(d2);
	free(d3);
	free(d4);
	free(w0);
	free(w1);
	free(w2);
	free(w3);
	free(w4);
	return x;
}

float * butterworth_lowpass(int order, float * signal, int size, float sample_rate, float cutoff_freq)
{
	order = order / 2;
	float a = tan(M_PI * cutoff_freq / sample_rate);
	float a_2 = a * a;
	float r;
	float *A = (float *)malloc(order * sizeof(float));
	float *d1 = (float *)malloc(order * sizeof(float));
	float *d2 = (float *)malloc(order * sizeof(float));
	float *w0 = (float *)calloc(order, sizeof(float));
	float *w1 = (float *)calloc(order, sizeof(float));
	float *w2 = (float *)calloc(order, sizeof(float));

	float *x = (float *)malloc(size * sizeof(float));

	for (int i = 0; i<order; ++i) {
		r = sin(M_PI*(2.0*i + 1.0) / (4.0*order));
		sample_rate = a_2 + 2.0*a*r + 1.0;
		A[i] = a_2 / sample_rate;
		d1[i] = 2.0*(1 - a_2) / sample_rate;
		d2[i] = -(a_2 - 2.0*a*r + 1.0) / sample_rate;
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < order; ++j) {
			if (j == 0) {
				w0[j] = d1[j] * w1[j] + d2[j] * w2[j] + signal[i];
			}
			else {
				w0[j] = d1[j] * w1[j] + d2[j] * w2[j] + x[i];
			}
			x[i] = A[j] * (w0[j] + 2.0*w1[j] + w2[j]);
			w2[j] = w1[j];
			w1[j] = w0[j];
		}
	}
	free(A);
	free(d1);
	free(d2);
	free(w0);
	free(w1);
	free(w2);
	return x;
}

float * butterworth_bandpass_v2(int order, float * signal, int size, float sample_rate, float high_freq_cutoff, float low_freq_cutoff, float *A,
	float *d1, float *d2, float *d3, float *d4, float *w0, float *w1, float *w2, float *w3, float *w4, float *x)
{
	float a = cos(M_PI * (high_freq_cutoff + low_freq_cutoff) / sample_rate) / cos(M_PI * (high_freq_cutoff - low_freq_cutoff) / sample_rate);
	float a_2 = a * a;
	float b = tan(M_PI * (high_freq_cutoff - low_freq_cutoff) / sample_rate);
	float b_2 = b * b;
	float r;
	for (int i = 0; i < order; ++i) {
		r = sin(M_PI * (2.0 * i + 1.0) / (4.0 * order));
		sample_rate = b_2 + 2.0 * b * r + 1.0;
		A[i] = b_2 / sample_rate;
		d1[i] = 4.0 * a * (1.0 + b * r) / sample_rate;
		d2[i] = 2.0 * (b_2 - 2.0 * a_2 - 1.0) / sample_rate;
		d3[i] = 4.0 * a * (1.0 - b * r) / sample_rate;
		d4[i] = -(b_2 - 2.0 * b * r + 1.0) / sample_rate;
	}
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < order; ++j) {
			if (j == 0) {
				w0[j] = d1[j] * w1[j] + d2[j] * w2[j] + d3[j] * w3[j] + d4[j] * w4[j] + signal[i];
			}
			else {
				w0[j] = d1[j] * w1[j] + d2[j] * w2[j] + d3[j] * w3[j] + d4[j] * w4[j] + x[i];
			}
			x[i] = A[j] * (w0[j] - 2.0 * w2[j] + w4[j]);
			w4[j] = w3[j];
			w3[j] = w2[j];
			w2[j] = w1[j];
			w1[j] = w0[j];
		}
	}

	return x;
}
