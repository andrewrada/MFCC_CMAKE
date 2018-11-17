#include "syll_fragmentation.h"
#include <sys/time.h>

void check_sentence_formation(char *path, char *ext, int sent_len) {
	FILE *fsent = fopen(path, "r");

	if (fsent == NULL) {
		printf("FILE DOESN'T EXIST!!");
		exit(1);
	}
	int dtemp, index = 0, succeed = 0;

	while (fscanf(fsent, "%d", &dtemp) != EOF) {
		if (dtemp == sent_buff[index]) {
			succeed = 0;
		}
		else {
			succeed = 1;
			break;
		}
		index++;
	}
	if (succeed == 0) {
		printf("VALID SENTENCE: ");	//return true
		for (int i = 0; i < sent_len; i++) {
			printf("%s ", sent_buff[i] == 2 ? "mo" : (sent_buff[i] == 3 ? "cua" : sent_buff[i] == 4 ? "truoc" : "ra"));
		}
	}
	else {
		printf("INVALID SENTENCE!! ");	//return true
	}
	fclose(fsent);
}



void Push(float *data, int index, float *word) {
	int dem = 480;
	if (index == 0) {
		for (int i = 0; i < 160; ++i) {
			word[i] = data[dem];
			dem++;
		}
	}
	else
	{
		for (int i = index * 160; i < (index + 1) * 160; i++) {
			if (index * 160 < (MAX_WORD_BUFFER * FRAMES_PER_BUFFER)) {
				word[i] = data[dem];
				dem++;
			}
			else
			{
				break;
			}
		}
	}
}

int silence_detect(float *data, size_t length, int *time, int *cond_flag, int *dist, float *word, float *peak, float *syll, float *lowPeak1, float *lowPeak2,
	int *d_word, char *def_name, char *ext, char *path, float *A, float *d1, float *d2, float *d3, float *d4, float *w0, float *w1, float *w2, float *w3, float *w4, float *x, svm_model_td *model, 		SAMPLE *sum_normal) {
	x = butterworth_bandpass_v2(2, data, length, 16000, 4000, 500, A, d1, d2, d3, d4, w0, w1, w2, w3, w4, x);
	int chunk_size = 160;
	float sum = 0;
	int trim_ms = 0;
	int dem = 0;
	int succeed = 1;
	float *db = (float *)malloc(sizeof(float) * 7);
	while (trim_ms < length)
	{
		sum = 0;
		for (int i = trim_ms; i < trim_ms + chunk_size; i++) {
			sum += x[i] * x[i];
		}
		sum = sqrt(sum / chunk_size);
		sum = 20 * log10(sum);
		db[dem] = sum;
		dem++;
		trim_ms += chunk_size;
	}

	if (*time) {
		syll[0] = (db[0] + db[1] + db[2] + db[3] + db[4] + db[5]) / 6;
		syll[1] = (db[1] + db[2] + db[3] + db[4] + db[5] + db[6]) / 6;
		*lowPeak1 = syll[0];
		*lowPeak2 = 0;
	}
	else
	{
		syll[1] = (db[1] + db[2] + db[3] + db[4] + db[5] + db[6]) / 6;
	}
	switch (*cond_flag)
	{
	case 0:
		if (*lowPeak1 < syll[1]) {
			//printf("case 0, cond 0\n");
			*peak = syll[1];
			*cond_flag = 1;
			(*dist) += 1;
			//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
			if (!(*time)) {
				//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
				Push(x, *dist - 1, word);
				*time = 0;
			}
			else
			{
				Push(x, *dist - 1, word);
				*time = 0;
			}
		}
		else if (*lowPeak1 >= syll[1]) {
			//printf("case 0, cond 1\n");
			*lowPeak1 = syll[1];

			/*free(word);
			word = (float *)malloc(sizeof(float) * FRAMES_PER_BUFFER);*/
			//word = (float *)realloc(word, sizeof(float) * FRAMES_PER_BUFFER);
		}
		break;
	case 1:
		if (*peak < syll[1]) {
			//printf("case1 cond 0.0\n");
			*peak = syll[1];
			*dist += 1;
			//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
			//word = realloc_same_add(data, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
			Push(x, *dist - 1, word);
		}
		else
		{
			if (fabs(*peak - *lowPeak1) > 15) {
				//printf("case 1 cond 0\n");
				*lowPeak2 = syll[1];
				*cond_flag = 2;
				*dist += 1;
				//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
				//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
				Push(x, *dist - 1, word);
			}
			else
			{
				//printf("case 1 cond 1\n");
				*cond_flag = 0;
				*dist = 0;
				*lowPeak1 = syll[1];
				/*free(word);
				word = (float *)malloc(sizeof(float) * FRAMES_PER_BUFFER * MAX_WORD_BUFFER);*/
				//word = (float *)realloc(word, sizeof(float) * FRAMES_PER_BUFFER);
			}
		}
		break;
	case 2:
		if (*lowPeak2 > syll[1]) {
			//printf("case 2 cond 0\n");
			*lowPeak2 = syll[1];
			*dist += 1;
			//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
			//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
			Push(x, *dist - 1, word);
		}
		else
		{
			if (fabs(*peak - *lowPeak2) > 15 && *dist >= 13) {
				//printf("case 2 con 1\n");

				*lowPeak1 = syll[1];
				*dist += 1;
				//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
				//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
				Push(x, *dist - 1, word);
				write_to_syll(d_word, def_name, ext, path, dist, word, model, sum_normal);

				/*free(word);
				word = (float *)malloc(sizeof(float) * FRAMES_PER_BUFFER * MAX_WORD_BUFFER);*/
				//word = (float *)realloc(word, sizeof(float) * FRAMES_PER_BUFFER);
				*dist = 0;
				*cond_flag = 0;
				succeed = 0;
			}
			else
			{
				//printf("case 2 con 2\n");
				*peak = syll[1];
				*cond_flag = 3;
				*dist += 1;
				//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
				//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
				Push(x, *dist - 1, word);
			}
		}
		break;
	case 3:
		if (*peak < syll[1]) {
			//printf("case 3 cond 1\n");
			*peak = syll[1];
		}
		else
		{
			//printf("case 3 cond 2\n");
			*lowPeak2 = syll[1];
			*cond_flag = 2;
		}
		*dist += 1;
		//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
		//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
		Push(x, *dist - 1, word);
		break;
	default:
		break;
	}
	//free(temp_data);
	free(db);
	return succeed;
}

void write_to_syll(int *d_word, char *def_name, char *ext, char*path, int *dist, float *word, svm_model_td *model, SAMPLE *sum_normal) {
	SIGNAL a = setSignal2(word, (*dist)*FRAMES_PER_BUFFER);
	int temp = predict_test_one_time(a, path, 0, model, sum_normal);
	if (temp == 1) {
		printf("tu\n");
		sent_buff[*d_word] = 1;
	}
	else if (temp == 2) {
		printf("mo\n");
		sent_buff[*d_word] = 2;
	}
	else if (temp == 3) {
		printf("cua\n");
		sent_buff[*d_word] = 3;
	}
	else if (temp == 4)
	{
		printf("truoc\n");
		sent_buff[*d_word] = 4;
	}
	else
	{
		printf("ra\n");
		sent_buff[*d_word] = 5;
	}
	*d_word += 1;
}

void real_time_predict(svm_model_td *model, SAMPLE *sum_normal, char *path) {
	struct timeval tv0, tv1;
	sent_buff = (int*)malloc(sizeof(int) * 7);
	int order = 2;
	float *A = (float *)malloc(sizeof(float) * order);
	float *d1 = (float *)malloc(sizeof(float) * order);
	float *d2 = (float *)malloc(sizeof(float) * order);
	float *d3 = (float *)malloc(sizeof(float) * order);
	float *d4 = (float *)malloc(sizeof(float) * order);
	float *x = (float *)malloc(sizeof(float) * QUEUE_SIZE);
	float *w0 = (float *)calloc(order, sizeof(float));
	float *w1 = (float *)calloc(order, sizeof(float));
	float *w2 = (float *)calloc(order, sizeof(float));
	float *w3 = (float *)calloc(order, sizeof(float));
	float *w4 = (float *)calloc(order, sizeof(float));
	//LARGE_INTEGER Frequency;

	float *queue = (float *)malloc(sizeof(float) * QUEUE_SIZE);
	float *word = (float *)malloc(sizeof(float) * FRAMES_PER_BUFFER * MAX_WORD_BUFFER);
	int trim_ms = 0;
	int offset = FRAMES_PER_BUFFER;
	int flag = 1;
	int dem = 0;
	int time = 1;
	int cond_flag = 0;
	int p_word = 0;
	float peak;
	float syll[2];
	int dist = 0;
	float lowPeak1;
	float lowPeak2;
	int d_word = 0;
	int temp = 1;
	char *def_name = "syllabic";
	char *ext = ".txt";
	///////////////////////////
	char *def_sent = "./sentences/s_1.txt";
	int sent_len = strlen(def_sent);
	///////////////////////////
	int get_data_time = 0;
	PaError err = paNoError;
	if ((err = Pa_Initialize())) goto done;
	const PaDeviceInfo *info = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice());
	//AudioData data = initAudioData(16000, 1, paFloat32);
	AudioSnippet sampleBlock =
	{
		.snippet = NULL,
		.size = FRAMES_PER_BUFFER * sizeof(float)
	};
	PaStream *stream = NULL;
	sampleBlock.snippet = (float *)malloc(sampleBlock.size);
	PaStreamParameters inputParameters =
	{
		.device = Pa_GetDefaultInputDevice(),
		.channelCount = 1,
		.sampleFormat = paFloat32,
		.suggestedLatency = info->defaultHighInputLatency,
		.hostApiSpecificStreamInfo = NULL
	};

	if (err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL)) goto done;
	if (err = Pa_StartStream(stream)) goto done;

	//QueryPerformanceFrequency(&Frequency);
	int demtemp = 0;
	int timer = 0;
	for (int i = 0;;) {
		//PRINT_TIME_SAMPLE_START(start);
		err = Pa_ReadStream(stream, sampleBlock.snippet, FRAMES_PER_BUFFER);
		//PRINT_TIME_SAMPLE_STOP("SAMPLE: ",10);

		if (err) goto done;
		else {
			if (trim_ms < QUEUE_SIZE) {
				for (int j = trim_ms, k = 0; j < trim_ms + offset; ++j) {
					queue[j] = sampleBlock.snippet[k];
					k++;
				}
			}
			else {
				for (int j = FRAMES_PER_BUFFER; j < QUEUE_SIZE; ++j) {
					queue[j - FRAMES_PER_BUFFER] = queue[j];
				}
				for (int j = 0; j < FRAMES_PER_BUFFER; ++j) {
					queue[QUEUE_SIZE - FRAMES_PER_BUFFER + j] = sampleBlock.snippet[j];
				}
			}

			if (trim_ms < QUEUE_SIZE) {
				trim_ms += offset;
				if (trim_ms < QUEUE_SIZE) {
					continue;
				}
				else {
					silence_detect(queue, QUEUE_SIZE, &time, &cond_flag, &dist, word, &peak, syll, &lowPeak1, &lowPeak2, &d_word, def_name, ext, path, A, d1, d2, d3, d4,
						w0, w1, w2, w3, w4, x, model, sum_normal);
				}
			}
			else
			{	
				if (d_word == 1) {
					p_word = d_word;
					timer = 1;
				}
				/*if (d_word>0&&!check_word(d_word,p_word)) {
				timer = 1;
				}
				else*/
				if (check_word(d_word, p_word) && tdem < 100) {
					p_word = d_word;
					timer = 1;
					tdem = 0;
				}
				if (timer) {
					tdem++;
					if (tdem > 100) {
						check_sentence_formation(def_sent, ext, d_word);
						d_word = p_word = 0;
						tdem = 0;
						timer = 0;
						demtemp = 0;
					}
				}
			}
		}
	}
done:
	svm_free_and_destroy_model(&model);
	free(sampleBlock.snippet);
	free(queue);
	free(word);
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
	free(x);
	Pa_Terminate();

}


int check_word(int word, int pword) {
	if (word != pword)
		return 1;
	return 0;
}
