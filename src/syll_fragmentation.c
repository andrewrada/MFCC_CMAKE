#include "syll_fragmentation.h"
#include <sys/time.h>
#include <time.h>

void check_sentence_formation(char *path, char *ext, int sent_len, char *wtemp, int num_of_sents) {
	char *label = (char *)malloc(sizeof(char) * 2);
	const char *default_ext = ".txt";
	size_t lent_path_tmp = strlen(path) + strlen(label) + 6;
	char *temp = (char *)malloc(sizeof(char) * lent_path_tmp);
	FILE *fsent;
	int num, dtemp, succeed = 0;
	for (int i = 0; i < num_of_sents; ++i) {
		sprintf(label, "%d", i + 1);
		strcpy(temp, path);
		strcat(temp, "s_");
		strcat(temp, label);
		strcat(temp, default_ext);
		//printf("%s\n", temp);
		fsent = fopen(temp, "r");

		if (fsent == NULL) {
			printf("FILE DOESN'T EXIST!!");
			return;
		}
		fscanf(fsent, "%d", &num);
		for (int j = 0; j < num; ++j) {
			fscanf(fsent, "%d", &dtemp);
			if (dtemp == sent_buff[j]) {
				succeed = 0;
			}
			else {
				succeed = 1;
				break;
			}
		}
		if (succeed == 0) {
			printf("VALID SENTENCE: ");
			for (int k = 0; k < num; ++k) {
				fscanf(fsent, "%s", wtemp);
				printf("%s", wtemp);
				sent_buff[k] = 0;
			}
			fscanf(fsent, "%s", wtemp);
			printf("%s", wtemp);
		}
		fclose(fsent);
		return;

	}
	fclose(fsent);
	if (succeed == 1) {
		printf("INVALID SENTENCE!!!\n");
	}
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
			if (index * 160 < (MAX_WORD_BUFFER_RECORD * FRAMES_PER_BUFFER)) {
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

void Push2(float *data, int index, float *word, SAMPLE *final_feats, hyper_vector fbank, hyper_vector temp_feats, kiss_fft_cfg cfg, kiss_fft_cpx * cx_in, kiss_fft_cpx * cx_out, hyper_vector pow_spectrum, hyper_vector matrix, hyper_vector dct,float *temp) {
	int dem = 480;
	//printf("x1");
	//for (int i = 0; i < 160; i++) {
	//	false_data[index * 160 + i] = data[dem];
	//	dem++;
	//}
	if (index == 0) {
		for (int i = 0; i < 160; ++i) {
			word[i] = data[dem];
			dem++;
		}
	}
	else if (index < 2)
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
	else if (index == 2) {
		for (int i = index * 160; i < (index + 1) * 160; i++) {
			word[i] = data[dem];
			dem++;
		}
		for (int i = 0; i < 400; ++i) {
			temp_feats.data[i] = word[i];
		}
		add_to_final(final_feats, get_feature_vector_from_signal2(temp_feats, fbank, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp), index - 2);
	}
	else if (index > 2) {
		for (int i = 160; i < 480; ++i) {
			word[i - 160] = word[i];
			temp_feats.data[i - 160] = word[i - 160];
		}
		for (int i = 320; i < 480; i++) {
			word[i] = data[dem];
			if (i < 400) {
				temp_feats.data[i] = word[i];
			}
			dem++;
		}
		add_to_final(final_feats, get_feature_vector_from_signal2(temp_feats, fbank, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp), index - 2);
		/*for (int i = index; i < index + 13; ++i) {
			printf("%f ", final_feats[i]);
		}
		printf("\n");*/
	}
}

int silence_detect(float *data, size_t length, int *time, int *cond_flag, int *dist, float *word, float *peak, float *syll, float *lowPeak1, float *lowPeak2,
	int *d_word, char *def_name, char *ext, char *path, float *A, float *d1, float *d2, float *d3, float *d4, float *w0, float *w1, float *w2, float *w3, float *w4,
	float *x, svm_model_td *model, SAMPLE *sum_normal, PaStream *stream, hyper_vector fbank, char **words, SAMPLE *final_feats,
	hyper_vector temp_feats, kiss_fft_cfg cfg, kiss_fft_cpx * cx_in, kiss_fft_cpx * cx_out, float *db, svm_node_td *node, int *info, SAMPLE *mean, 
	SAMPLE *normalize_detect, int row_of_training_set,hyper_vector pow_spectrum, hyper_vector matrix, hyper_vector dct,float *temp) {
	////
	int chunk_size = 160;
	float sum = 0;
	int trim_ms = 0;
	int dem = 0;
	int succeed = 1;
	///

	//printf("x\n");

	x = butterworth_bandpass_v2(2, data, length, 16000, 4000, 500, A, d1, d2, d3, d4, w0, w1, w2, w3, w4, x);
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
	//printf("x1\n");
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
				Push2(data, *dist - 1, word, final_feats, fbank, temp_feats, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp);
				*time = 0;
			}
			else
			{
				Push2(data, *dist - 1, word, final_feats, fbank, temp_feats, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp);
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
			Push2(data, *dist - 1, word, final_feats, fbank, temp_feats, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp);
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
				Push2(data, *dist - 1, word, final_feats, fbank, temp_feats, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp);
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
			Push2(data, *dist - 1, word, final_feats, fbank, temp_feats, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp);
		}
		else
		{
			if (fabs(*peak - *lowPeak2) > 15 && *dist >= 13) {
				//printf("case 2 con 1\n");

				*lowPeak1 = syll[1];
				*dist += 1;
				//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
				//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
				Push2(data, *dist - 1, word, final_feats, fbank, temp_feats, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp);
				//write_to_syll2(d_word, def_name, ext, path, dist, final_feats, model, sum_normal, fbank, words);
				/*if (errflag == 0) {
					printf("DATA\n");
					FILE *ftemp = fopen("data.txt", "w");

					for (int i = 0; i < (*dist)*FRAMES_PER_BUFFER; i++) {
						fprintf(ftemp,"%f\n", false_data[i]);
					}
					fclose(ftemp);

				}*/
				Pa_StopStream(stream);

				succeed = write_to_syll2(d_word, def_name, ext, path, dist, final_feats, model, sum_normal, fbank, words,
					node, info, mean, normalize_detect,row_of_training_set,pow_spectrum, matrix,dct,temp);
				//printf("temp: %d\n", succeed);

				Pa_StartStream(stream);
				/*free(word);
				word = (float *)malloc(sizeof(float) * FRAMES_PER_BUFFER * MAX_WORD_BUFFER);*/
				//word = (float *)realloc(word, sizeof(float) * FRAMES_PER_BUFFER);
				*dist = 0;
				*cond_flag = 0;
				//succeed = 0;
			}
			else if (fabs(*peak - *lowPeak2) > 12 && *dist <= 18 || *dist > 150) {
				printf("EXCEPTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
				*dist = 0;
				*cond_flag = 0;
			}
			else
			{
				//printf("case 2 con 2\n");
				*peak = syll[1];
				*cond_flag = 3;
				*dist += 1;
				//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
				//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
				//Push2(data, *dist - 1, word);
				Push2(data, *dist - 1, word, final_feats, fbank, temp_feats, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp);
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
		Push2(data, *dist - 1, word, final_feats, fbank, temp_feats, cfg, cx_in, cx_out,pow_spectrum, matrix,dct,temp);
		//Push2(data, *dist - 1, word);
		break;
	default:
		break;
	}
	//printf("x2\n");

	//free(temp_data);
	//free(db);
	//printf("3.");
	return succeed;
}

void write_to_syll(int *d_word, char *def_name, char *ext, char*path, int *dist, float *word, svm_model_td *model, SAMPLE *sum_normal, hyper_vector fbank) {
	SIGNAL a = setSignal2(word, (*dist)*FRAMES_PER_BUFFER);
	int temp = predict_test_one_time(a, path, 0, model, sum_normal, fbank);
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

int write_to_syll2(int *d_word, char *def_name, char *ext, char*path, int *dist, SAMPLE *final_feats, struct svm_model *model, SAMPLE *sum_normal
	, hyper_vector fbank, char **words, svm_node_td *node, int *info, SAMPLE *mean, SAMPLE *normalize_detect, int row_of_training_set,hyper_vector pow_spectrum, hyper_vector matrix, hyper_vector dct,float *temp) {

	//struct timeval tv0, tv1;
	//gettimeofday(&tv0, NULL);

	hyper_vector compact_final_feats = cov(setHVector2(final_feats, RAW_FEAT_SIZE, *dist - 2, 1));
	//gettimeofday(&tv1, NULL);
	//printf("Cov time 1 : %.6f\n", ((double)tv1.tv_usec - (double)tv0.tv_usec) / 1000);

	/*if (errflag == 0) {
		printf("DATA\n");
		FILE *ftemp = fopen("data.txt", "w");

		for (int i = 0; i < 91; i++) {
			fprintf(ftemp, "%f\n", compact_final_feats.data[i]);
		}
		fclose(ftemp);

	}*/
	int temp2 = predict_one_time(compact_final_feats, path, 0, model, sum_normal, fbank, errflag, node, info, mean, normalize_detect,row_of_training_set);

	//int temp = 1;

		//int temp = predict_test_one_time(compact_final_feats, path, 0, model, sum_normal, fbank);

	printf("%d : %s\n", *d_word, words[temp2 - 1]);
	//printf("%d", temp);
	//sent_buff[*d_word] = temp;
	*d_word += 1;
	return (temp2 - 1);
}

void real_time_predict(svm_model_td *model, SAMPLE *sum_normal, char *def_path, char *sent_path, int num_of_sents, char **words) {
	struct timeval tv0, tv1;

	////////////// init feats params///////////
	filter_bank fbank = filterbank(26, 512);
	hyper_vector transpose_param = setHVector2(fbank.data, fbank.filt_len, fbank.nfilt, 1);
	hyper_vector tmp = transpose(transpose_param);
	hyper_vector final_feats = setEHVector(RAW_FEAT_SIZE, MAX_FEATS_BUFFER, 1);
	hyper_vector temp_feats;
	temp_feats.row = 1;
	temp_feats.col = 400;
	temp_feats.dim = 1;
	temp_feats.data = (SAMPLE*)calloc(400,sizeof(SAMPLE));
	int NFFT = 512;
	kiss_fft_cfg cfg = kiss_fft_alloc(NFFT, 0, 0, 0);
	kiss_fft_cpx * cx_in = (kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx)*NFFT);
	kiss_fft_cpx * cx_out = (kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx)*NFFT);
	/////////////// MFCC params///////////////
	hyper_vector pow_spectrum;
	pow_spectrum.data = (SAMPLE*)calloc(1 * (NFFT / 2 + 1),sizeof(SAMPLE));
	pow_spectrum.col = (NFFT / 2 + 1);
	pow_spectrum.row = 1;
	pow_spectrum.dim = 1;

	hyper_vector matrix;
	matrix.data = (float*)calloc(1 * fbank.filt_len,sizeof(float));

	hyper_vector dct;
	dct.data = (float*)calloc(1 * 13,sizeof(float));
	dct.row = 1;
	dct.col = 13;
	float *temp = (float*)calloc(16,sizeof(float));
	/////////////////////////////////////////

	////////////////////init normalize params/////////////////
	size_t len_path = strlen(def_path);
	const char *info_path_def = "info.txt";
	const char *config_path_def = "config.txt";
	//const char *db_path_def = "db.txt";
	char *info_path = (char *)malloc(sizeof(char) * (len_path + 8));
	char *config_path = (char *)malloc(sizeof(char) * (len_path + 10));
	//char *db_path = (char *)malloc(sizeof(char) * (len_path + 6));
	int *info;
	strcpy(info_path, def_path);
	strcat(info_path, info_path_def);
	strcpy(config_path, def_path);
	strcat(config_path, config_path_def);
	//strcpy(db_path, path);
	//strcat(db_path, db_path_def);
	FILE *config_file = fopen(config_path, "r");
	if (config_file == NULL) {
		fprintf(stderr, "Config file not exists!!!\n");
		exit(1);
	}
	int row_of_training_set;
	fscanf(config_file, "%d", &row_of_training_set);
	info = (int *)malloc(sizeof(int) * (row_of_training_set + 2));
	fclose(config_file);

	FILE *info_file = fopen(info_path, "r");
	if (info_file == NULL) {
		fprintf(stderr, "info file not exists!!!\n");
		exit(1);
	}
	for (int i = 0; i < row_of_training_set + 2; ++i) {
		fscanf(info_file, "%d", &info[i]);
	}
	fclose(info_file);
	SAMPLE * mean = (SAMPLE *)malloc(sizeof(SAMPLE) * FEATSIZE);
	SAMPLE *normalize_detect = (SAMPLE *)malloc(sizeof(SAMPLE) * FEATSIZE);
	 svm_node_td *node = (svm_node_td *)malloc(sizeof(svm_node_td) * (FEATSIZE +1));

	/////////////////////////////////////////////////////////

	false_data = (float*)calloc(MAX_WORD_BUFFER_RECORD * FRAMES_PER_BUFFER, sizeof(float));
	float *db = (float *)calloc(7,sizeof(float));
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

	float *queue = (float *)calloc( QUEUE_SIZE,sizeof(float) );
	float *word = (float *)calloc(FRAMES_PER_BUFFER * MAX_WORD_BUFFER,sizeof(float));
	char *wtemp = (char *)malloc(sizeof(char) * 8);
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
	int temp2 = 1;
	char *def_name = "syllabic";
	char *ext = ".txt";
	///////////////////////////
	/*char *def_sent = "./sentences/s_1.txt";
	int sent_len = strlen(def_sent);*/


	///////////////////////////
	int get_data_time = 0;
	PaError err = paNoError;
	if ((err = Pa_Initialize())) goto done;
	const PaDeviceInfo *infoDV = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice());
	printf("device name : %s - SAMPLE RATE: %f\n", infoDV->name, infoDV->defaultSampleRate);
	/*AudioSnippet sampleBlock =
	{
		.snippet = NULL,
		.size = 4000 * sizeof(float)
	};*/
	PaStream *stream = NULL;
	//sampleBlock.snippet = (float *)calloc(sampleBlock.size,sizeof(float));
	PaStreamParameters inputParameters =
	{
		.device = Pa_GetDefaultInputDevice(),
		.channelCount = 1,
		.sampleFormat = paFloat32,
		.suggestedLatency = infoDV->defaultLowInputLatency,
		.hostApiSpecificStreamInfo = NULL
	};
	//if (err = Pa_OpenDefaultStream(&stream, 1, 0, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL)) goto done;
	if (err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL)) goto done;
	if (err = Pa_StartStream(stream)) goto done;

	//QueryPerformanceFrequency(&Frequency);
	int demtemp = 0;
	int timer = 0;
	AudioSnippet sampleBlock =
	{
		.snippet = NULL,
		.size = FRAMES_PER_BUFFER * sizeof(float)
	};
	sampleBlock.snippet = (float *)malloc(sampleBlock.size * sizeof(float));

	for (int i = 0;;) {
		//printf("1");
		err = Pa_ReadStream(stream, sampleBlock.snippet, FRAMES_PER_BUFFER);
		//printf("2");

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
					//free(sampleBlock.snippet);
					continue;
				}
				else {
					silence_detect(queue, QUEUE_SIZE, &time, &cond_flag, &dist, word, &peak, syll, &lowPeak1, &lowPeak2, &d_word, def_name, ext, def_path, A, d1, d2, d3, d4,
						w0, w1, w2, w3, w4, x, model, sum_normal, stream, tmp, words, final_feats.data, temp_feats, cfg, cx_in, cx_out,db, node, info, mean, normalize_detect, row_of_training_set,pow_spectrum, matrix,dct,temp);
				}
			}
			else
			{

				//gettimeofday(&tv0, NULL);
				//printf("3");
				temp = silence_detect(queue, QUEUE_SIZE, &time, &cond_flag, &dist, word, &peak, syll, &lowPeak1, &lowPeak2, &d_word, def_name, ext, def_path, A, d1, d2,
					d3, d4, w0, w1, w2, w3, w4, x, model, sum_normal, stream, tmp, words, final_feats.data, temp_feats, cfg, cx_in, cx_out,db, node, info, mean, normalize_detect,row_of_training_set,pow_spectrum, matrix,dct,temp);
				//printf("4");
				//if (temp == 10) {
				//	errflag = 0;
				//	//printf("sdsd");
				//	//goto done;
				//}
				//gettimeofday(&tv1, NULL);
				//double total = ((double)tv1.tv_usec - (double)tv0.tv_usec) / 1000;

				/*if (total > 7) {
					printf("total time silence detect : %.6f\n", total);
				}*/
				//if (d_word == 1) {
				//	p_word = d_word;
				//	timer = 1;
				//}
				/*if (d_word>0&&!check_word(d_word,p_word)) {
				timer = 1;
				}
				else*/
				/*if (check_word(d_word, p_word) && tdem < 100) {
					p_word = d_word;
					timer = 1;
					tdem = 0;
				}


				if (timer) {
					tdem++;
					if (tdem > 100) {
						check_sentence_formation(sent_path, ext, d_word, wtemp, num_of_sents);
						d_word = p_word = 0;
						tdem = 0;
						timer = 0;
						demtemp = 0;
					}
				}*/

			}
			//free(sampleBlock.snippet);
		}
	}
done:
	printf("error code : %d\n", err);
	svm_free_and_destroy_model(model);
	//free(sampleBlock.snippet);
	free(cx_in);
	free(cx_out);
	free(db);
	kiss_fft_free(cfg);
	free(queue);
	free(temp_feats.data);
	free(final_feats.data);
	//free(node);
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
	Pa_Terminate();	printf("111");

}


int check_word(int word, int pword) {
	if (word != pword)
		return 1;
	return 0;
}

int silence_detect_record(float *data, size_t length, int *time, int *cond_flag, int *dist, float *word, float *peak, float *syll, float *lowPeak1, float *lowPeak2,
	int *d_word, float *A, float *d1, float *d2, float *d3, float *d4, float *w0, float *w1, float *w2, float *w3, float *w4, float *x) {

	x = butterworth_bandpass_v2(2, data, length, 16000, 4000, 500, A, d1, d2, d3, d4, w0, w1, w2, w3, w4, x);
	int chunk_size = 160;
	float sum = 0;
	int trim_ms = 0;
	int dem = 0;
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
		}
		break;
	case 1:
		if (*peak < syll[1]) {
			//printf("case1 cond 0.0\n");
			*peak = syll[1];
			*dist += 1;
			Push(x, *dist - 1, word);
		}
		else
		{
			if (fabs(*peak - *lowPeak1) > 15) {
				//printf("case 1 cond 0\n");
				*lowPeak2 = syll[1];
				*cond_flag = 2;
				*dist += 1;
				Push(x, *dist - 1, word);
			}
			else
			{
				//printf("case 1 cond 1\n");
				*cond_flag = 0;
				*dist = 0;
				*lowPeak1 = syll[1];
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
			if (fabs(*peak - *lowPeak2) > 15 && *dist >= 14) {
				//printf("case 2 con 1\n");
				*lowPeak1 = syll[1];
				*dist += 1;
				//word = (float *)realloc(word, sizeof(float) * (*dist) * FRAMES_PER_BUFFER);
				//word = realloc_same_add(word, (*dist - 1) * FRAMES_PER_BUFFER, (*dist) * FRAMES_PER_BUFFER);
				Push(x, *dist - 1, word);

				free(db);
				return 1;
				/*free(word);
				word = (float *)malloc(sizeof(float) * FRAMES_PER_BUFFER * MAX_WORD_BUFFER);*/
				//word = (float *)realloc(word, sizeof(float) * FRAMES_PER_BUFFER);
				/**dist = 0;
				*cond_flag = 0;*/
			}
			else if (fabs(*peak - *lowPeak2) > 10 && *dist <= 18 || *dist > 150) {
				printf("EXCEPTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n");
				*dist = 0;
				*cond_flag = 0;
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
	return 0;

}

void add_to_final(SAMPLE *final_feats, hyper_vector temp, int num_feats) {
	int dem = 0;
	for (int i = num_feats * RAW_FEAT_SIZE; i < (num_feats + 1)*RAW_FEAT_SIZE; i++) {
		final_feats[i] = temp.data[dem];
		//	printf("%f ", final_feats[i]);
		dem++;
	}
	//printf("\n");
}

void record_audio_to_database2(char *path, int *current_index) {
	int size;
	SIGNAL audio_signal = real_time_record();
	int number_of_sample = audio_signal.signal_length;
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
	fprintf(fp, "%d\n", number_of_sample);

	for (int i = 0; i < number_of_sample; ++i) {
		fprintf(fp, "%f\n", audio_signal.raw_signal[i]);
	}
	fclose(fp);
	free(keyword);
	free(numerical_order);
	free(audio_signal.raw_signal);
	printf("Do you wanna continue to record? (y/n) \n");
	scanf("%s", y_n);
	check_continue(y_n, path, current_index);
}

SIGNAL real_time_record() {
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

	float *queue = (float *)malloc(sizeof(float) * QUEUE_SIZE);
	float *word = (float *)malloc(sizeof(float) * FRAMES_PER_BUFFER * MAX_WORD_BUFFER_RECORD);

	int trim_ms = 0;
	int offset = FRAMES_PER_BUFFER;
	int flag = 1;
	int dem = 0;
	int succeed = 0;
	int time = 1;
	int cond_flag = 0;
	float peak;
	float syll[2];
	int dist = 0;
	float lowPeak1;
	float lowPeak2;
	int d_word = 0;
	char def_name[3];
	SIGNAL result;
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

	for (int i = 0;;) {
		err = Pa_ReadStream(stream, sampleBlock.snippet, FRAMES_PER_BUFFER);
		if (err) goto done;
		else {
			/*for (int u = 0; u < FRAMES_PER_BUFFER; ++u) {
				printf("%d : %f\n", u, sampleBlock.snippet[u]);
			}
			getchar();*/
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
					silence_detect_record(queue, QUEUE_SIZE, &time, &cond_flag, &dist, word, &peak, syll, &lowPeak1, &lowPeak2, &d_word, A, d1, d2, d3, d4,
						w0, w1, w2, w3, w4, x);
				}
			}
			else
			{
				succeed = silence_detect_record(queue, QUEUE_SIZE, &time, &cond_flag, &dist, word, &peak, syll, &lowPeak1, &lowPeak2, &d_word, A, d1, d2,
					d3, d4, w0, w1, w2, w3, w4, x);

				if (succeed == 1) {
					result = setSignal2(word, dist * FRAMES_PER_BUFFER);
					goto done;
				}
				/*for (int j = FRAMES_PER_BUFFER; j < QUEUE_SIZE; ++j) {
				queue[j - FRAMES_PER_BUFFER] = queue[j];
				}*/
			}
		}
	}

done:
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
	return result;
}

