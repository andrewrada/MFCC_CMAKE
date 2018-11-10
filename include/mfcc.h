#ifndef MFCC_H
#define MFCC_H

/*includes
------------------------------------------
------------------------------------------*/
#include "record.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>

/*defines, constants
------------------------------------------
------------------------------------------*/

#define PI 3.14159265359
#define false 0
#define true 1
#define FEATSIZE 91

typedef struct SIGNAL {
	SAMPLE *raw_signal;
	int frame_length;		//so sample trong 1 frame
	int step_lengh;		//do dai bc nhay
	int num_frame;			//so frame trong 1 audio signal
	int signal_length;
}SIGNAL;

typedef struct COMPLEX {
	float img;
	float real;
	float magnitude;
}COMPLEX;

typedef struct hyper_vector {
	int row;
	int col;
	int dim;
	SAMPLE *data;
}hyper_vector;

typedef struct filter_bank {
	float *data;
	int nfilt;
	int filt_len;
}filter_bank;
/*functions
------------------------------------------
------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif
	filter_bank getFBank(float *fbank, int nfilt, int filt_len);
	int getLength(SAMPLE *a);
	SIGNAL setSignal(SAMPLE *a, int size);
	hyper_vector setHVector(SAMPLE *a, int col, int row, int dim);
	hyper_vector getFrames(struct SIGNAL a);
	void append_energy(hyper_vector dct, hyper_vector pow_spec);

	//COMPLEX *DFT(hyper_vector a, int pointFFT
	hyper_vector DCT(hyper_vector a, int num_ceps);
	hyper_vector DFT_PowerSpectrum(hyper_vector a, int pointFFT);

	float magnitude(float real, float img);
	filter_bank filterbank(int nfilt, int NFFT);
	float HammingWindow(float a, int frameLength);
	SIGNAL preEmphasis(SAMPLE *a, int size, float preemh);

	float hz2mel(float hz);
	float mel2hz(float hz);

	hyper_vector multiply(hyper_vector matrix1, hyper_vector matrix2);
	hyper_vector transpose(hyper_vector matrix);

	SIGNAL silence_trim(SIGNAL a);
	SAMPLE *reverse(SIGNAL a);

	//////////////////////////////////final_feature/////////////////////////////
	hyper_vector cov(hyper_vector mfcc);
	void normalize(char *path_nor, char *path_mean, int* label, float * data, int row, int col);
	void Get_normalize(int label, float * data, int row, int col);
	void normalize2(int label, float * data, int row, int col);
	hyper_vector var(hyper_vector);

	hyper_vector get_feature_vector_from_signal(SAMPLE *audio_signal, int size);
	void write_feature_vector_to_database(hyper_vector feature_vector, char *name);

	////////////////////////////////

	int check_path(char *path);

	//////////////////////test_signal_via_matlab/////////////////////////
	void writeDBFS(SAMPLE* raw_signal, int trim_ms, int signal_len);
	void create_database(char *path, int max_index);
	void normalize_db(char *path_nor, char *path_mean, char *path_db, char *path_info, int max_index);
	void normalize_from_file(char *path_nor, char *path_mean, char *filename, int row, int col);
#ifdef __cplusplus
}
#endif // __cplusplus



#endif // !MFCC_H