#include "record.h"

SAMPLE * get_audio_signal_from_source(int *size)
{
	PaStreamParameters inputParameters, outputParameters;
	PaStream *stream;
	PaError err;
	SAMPLE *recordedSamples;
	int i;
	int totalFrames;
	int numSamples;
	size_t numBytes;
	SAMPLE max, average, val;

	printf("patest_read_record.c\n"); fflush(stdout);

	totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
	numSamples = totalFrames * NUM_CHANNELS;

	*size = numSamples;
	numBytes = numSamples * sizeof(SAMPLE);
	recordedSamples = (SAMPLE *) malloc(numBytes);
	if (!recordedSamples)
	{
		printf("Could not allocate record array.\n");
		exit(1);
	}
	for (i = 0; i<numSamples; i++) *(recordedSamples + i) = 0;

	err = Pa_Initialize();
	if (err != paNoError) goto error;

	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
	if (inputParameters.device == paNoDevice) {
		fprintf(stderr, "Error: No default input device.\n");
		goto error;
	}
	inputParameters.channelCount = NUM_CHANNELS;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	/* Record some audio. -------------------------------------------- */
	err = Pa_OpenStream(
		&stream,
		&inputParameters,
		NULL,                  /* &outputParameters, */
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,      /* we won't output out of range samples so don't bother clipping them */
		NULL, /* no callback, use blocking API */
		NULL); /* no callback, so no callback userData */
	if (err != paNoError) goto error;

	err = Pa_StartStream(stream);
	if (err != paNoError) goto error;
	printf("Now recording!!\n"); fflush(stdout);
	err = Pa_ReadStream(stream, recordedSamples, totalFrames);
	if (err != paNoError) goto error;

	err = Pa_CloseStream(stream);
	if (err != paNoError) goto error;
	return recordedSamples;
error:
	Pa_Terminate();
	fprintf(stderr, "An error occured while using the portaudio stream\n");
	fprintf(stderr, "Error number: %d\n", err);
	fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
	return -1;
	return recordedSamples;
}

void check_continue(char *y_n, char *path, int *current_index) {
	if (0 == strcmp(y_n, "y")) {
		free(y_n);
		record_audio_to_database(path, current_index);
	}
	else if (0 == strcmp(y_n, "n")) {
		return;
	}
	else {
		free(y_n);
		y_n = (char *)malloc(sizeof(char) * 5);
		printf("wrong answer!!! Reimport answer \n");
		scanf("%s", y_n);
		check_continue(y_n, path, current_index);
	}
}

void record_audio_to_database(char *path, int *current_index)
{
	int size;
	SAMPLE *audio_singal = get_audio_signal_from_source(&size);
	writeDBFS(audio_singal, 0, size);
	int number_of_sample = get_number_of_sample_in_record();
	char *keyword = (char *)malloc(sizeof(char) * 5);
	char *numerical_order = (char *)malloc(sizeof(char) * 5);
	char *y_n = (char *)malloc(sizeof(char) * 5);

	printf("choose index of keyword \n");
	scanf("%s", keyword);
	*current_index = atoi(keyword);
	printf("choose the number order of text file to save audio signal \n");
	scanf("%s", numerical_order);
	char *name = get_name_of_new_file(path, keyword, numerical_order);
	FILE *fp = fopen(name, "w");
	for (int i = 0; i < number_of_sample; ++i) {
		if (((i % NUMBER_OF_ELEMENTS_IN_A_ROW) == 0) && (i != 0)) {
			fprintf(fp, "\n");
		}
		fprintf(fp, "%f ", audio_singal[i]);
	}
	fclose(fp);
	free(keyword);
	free(numerical_order);
	free(audio_singal);
	printf("Do you wanna continue to record? (y/n) \n");
	scanf("%s", y_n);
	check_continue(y_n, path, current_index);
}

char * get_name_of_new_file(char *path, char *keyword, char *numerical_order)
{
	size_t len_path = strlen(path);
	const char *ext = ".txt";
	size_t keyword_len = strlen(keyword);
	size_t numer_len = strlen(numerical_order);
	char *name = (char *)malloc(sizeof(char) * (keyword_len + numer_len + 2 + 4 + len_path));
	strcpy(name, path);
	strcat(name, keyword);
	strcat(name, "_");
	strcat(name, numerical_order);
	strcat(name, ext);
	return name;
}

KEYWORDS get_key_word(int key)
{
	if (key == 0) return TU;
	else if (key == 1) return TRUNG_ANH;
	else if (key == 2) return TRUNG;
	else {
		exit(0);
	}
}

int get_number_of_sample_in_record()
{
	return NUM_SECONDS * SAMPLE_RATE * NUM_CHANNELS;
}

SAMPLE * read_audio_signal_from_file(char * path)
{
	int i, j;
	FILE *fp = fopen(path, "r");
	int number_of_sample = get_number_of_sample_in_record();
	SAMPLE *audio_signal = (SAMPLE *)malloc(sizeof(SAMPLE) * number_of_sample);
	SAMPLE tmp;
	int cols = NUMBER_OF_ELEMENTS_IN_A_ROW;
	int rows = number_of_sample / NUMBER_OF_ELEMENTS_IN_A_ROW;
	printf("cols : %d , rows : %d \n", cols, rows);
	if (fp == NULL) {
		fprintf(stderr, "file no exist!!! \n");
		exit(1);
	}
	else {
		for (i = 0; i < rows; ++i) {
			for (j = 0; j < cols; ++j) {
				fscanf(fp, "%f", &tmp);
				audio_signal[i * cols + j] = tmp;
			}
		}
	}
	fclose(fp);
	return audio_signal;
}

