#ifndef RECORD_H
#define RECORD_H

/* includes 
-------------------------------------------
-------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portaudio.h"

/*defines, constants
-------------------------------------------
-------------------------------------------*/

#define SAMPLE_RATE  (16000)
#define FRAMES_PER_BUFFER (160)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (1)
#define NUMBER_OF_ELEMENTS_IN_A_ROW		(100)

#define DITHER_FLAG     (0) /**/

/* Select sample format. */
#if 1
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

typedef enum KEYWORDS {
	TU,
	TRUNG_ANH,
	TRUNG
}KEYWORDS;

/*functions
-------------------------------------------
-------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
	void check_continue(char *y_n, char *path, int *current_index);
	SAMPLE *get_audio_signal_from_source(int *size);
	void record_audio_to_database(char *path, int *current_index);
	char *get_name_of_new_file(char *path, char *keyword, char *numerical_order);
	KEYWORDS get_key_word(int key);
	int get_number_of_sample_in_record();
	SAMPLE* read_audio_signal_from_file(char *path, int *size);
#ifdef __cplusplus
}
#endif


#endif
