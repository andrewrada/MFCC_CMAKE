#ifndef SYLL_FRAGMENTATION_H
#define SYLL_FRAGMENTATION_H
/*define-----------------------
------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"
#include "filter.h"
#include "mfcc.h"
#include "record.h"
#ifdef WINDOW
#include "windows.h"
#include "Sysinfoapi.h"
#endif
#ifdef __cplusplus
extern "C"{
#endif
#include "svm2.h"
#ifdef __cplusplus
}
#endif

#define SAMPLE float
/*constants, variables--------
------------------------------*/
long long start, stop, sample_start,last;
int tflag = 0;
int tdem = 0;
int *sent_buff;
#ifdef WINDOW
#define PRINT_TIME_PROCESS_START(s) do {	\
	s = PerformanceCounter();				\
}while(0)

#define PRINT_TIME_PROCESS_STOP(s,message,threshold) do {											\
	double dftDuration2 = (double)(PerformanceCounter() - s) * 1000.0 / (double)Frequency.QuadPart;	\
	if (dftDuration2 > threshold)																	\
		printf(message ": %f\n", dftDuration2);														\
}while(0)

#define PRINT_TIME_SAMPLE_START()					PRINT_TIME_PROCESS_START(sample_start)
#define PRINT_TIME_SAMPLE_STOP(message,threshold)	PRINT_TIME_PROCESS_STOP(sample_start,message,threshold)
#endif

/*defines, constants
------------------------------------------
------------------------------------------*/
#define FRAMES_PER_BUFFER 160
#define QUEUE_SIZE	1120
#define SAMPLE_RATE	16000
#define MAX_WORD_BUFFER	200

typedef struct
{
	uint16_t formatType;
	uint8_t numberOfChannels;
	uint32_t sampleRate;
	size_t size;
	float *recordedSamples;
} AudioData;

typedef struct
{
	float *snippet;
	size_t size;
} AudioSnippet;

/*AudioData initAudioData(uint32_t sampleRate, uint16_t channels, int type)
{
	AudioData data;
	data.formatType = type;
	data.numberOfChannels = channels;
	data.sampleRate = sampleRate;
	data.size = 0;
	data.recordedSamples = NULL;
	return data;
};*/

typedef struct svm_model svm_model_td;

/*functions--------------------
------------------------------*/
#ifdef __cplusplus
extern "C"{
#endif
void real_time_predict(svm_model_td *model, SAMPLE *sum_normal, char *path);
void Push(float *data, int index, float *word);
void write_to_syll(int *d_word, char *def_name, char *ext, char *path, int *dist, float *word, svm_model_td *model, SAMPLE *sum_normal);
int silence_detect(float *data, size_t length, int *time, int *cond_flag, int *dist, float *word, float *peak, float *syll, float *lowPeak1, float *lowPeak2,
	int *d_word, char *def_name, char *ext, char *path, float *A, float *d1, float *d2, float *d3, float *d4, float *w0, float *w1, float *w2, float *w3, float *w4, float *x, svm_model_td *model, 		SAMPLE *sum_normal);
void check_sentence_formation(char *path, char *ext, int sent_len);
int check_word(int word, int pword);
#ifdef __cplusplus
}
#endif


#endif // !SYLL_FRAGMENTATION_H
