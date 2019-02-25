#include <stdio.h>
#include "record.h"
#include "mfcc.h"
#include "utils.h"
#include "syll_fragmentation.h"
#include <sys/time.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "svm2.h"
#ifdef __cplusplus
}
#endif // __cplusplus

char **load_words_sent(char *sent_path, int *num_of_sents);

void runtest() {
	int numf = 91, l = 1739,nr_class=30;
	int sumi = 0;
	float sumf = 0;
	struct timeval tv0, tv1;


	gettimeofday(&tv0, NULL);

	for (int i = 0; i < numf; i++) {
		for (int j = 0; j < l; j++) {
			sumi = 3 * 4;
		}
	}

	for (int i = 0; i < nr_class; i++) {
		for (int j = 0; j < nr_class; j++) {
			for (int k = 0; k < nr_class; k++) {
				sumi = 3 * 4;
			}
		}
	}
	gettimeofday(&tv1, NULL);
	printf("total time 1 : %.6f\n", ((double)tv1.tv_usec - (double)tv0.tv_usec) / 1000);
	
	struct timeval tv2, tv3;

	gettimeofday(&tv2, NULL);
	for (int i = 0; i < numf; i++) {
		for (int j = 0; j < l; j++) {
			sumf = 0.00323 * 0.043;
		}
	}
	for (int i = 0; i < nr_class; i++) {
		for (int j = 0; j < nr_class; j++) {
			for (int k = 0; k < nr_class; k++) {
				sumi = 3 * 4;
			}
		}
	}
	gettimeofday(&tv3, NULL);
	printf("total time 2 : %.6f\n", ((double)tv3.tv_usec - (double)tv2.tv_usec) / 1000);
}

int main(int argc, char **argv)
{
	printf("cc");
	int current_max_index = 0;
	int is_record = find_args(argc, argv, "-record");
	int is_create_database = find_args(argc, argv, "-createdb");
	int is_normalize_db = find_args(argc, argv, "-normlizedb");
	int is_train = find_args(argc, argv, "-training");
	int is_predict = find_args(argc, argv, "-predicting");
	int is_predict_file = find_args(argc, argv, "-pf");
	if (is_record) {
		int current_index;
		char *path = argv[2];
		size_t len_path_folder = strlen(path);
		char *path_config = (char *)malloc(sizeof(char) *(len_path_folder + 10));
		strcpy(path_config, path);
		strcat(path_config, "config.txt");
		record_audio_to_database2(path, &current_index);
		FILE *config;
		if (!cfileexists(path_config)) {
			FILE *config_first_write = fopen(path_config, "w");
			current_max_index = current_index;
			fprintf(config_first_write, "%d", current_index);
			fclose(config_first_write);
		}
		else {
			config = fopen(path_config, "r");
			fscanf(config, "%d", &current_max_index);
			if (current_index > current_max_index) {
				fclose(config);
				FILE *config_write = fopen(path_config, "w");
				current_max_index = current_index;
				fprintf(config_write, "%d", current_max_index);
				fclose(config_write);
			}
			else {
				fclose(config);
			}
		}
	}
	if (is_create_database) {
		char *path = argv[2];
		if (path == NULL) {
			fprintf(stderr, "Path no exist!");
			exit(1);
		}
		size_t len_path_folder = strlen(path);
		char *path_config = (char *)malloc(sizeof(char) *(len_path_folder + 10));
		strcpy(path_config, path);
		strcat(path_config, "config.txt");
		FILE *config = fopen(path_config, "r");
		if (config == NULL) {
			fprintf(stderr, "Config file no exist!");
			exit(1);
		}
		fscanf(config, "%d", &current_max_index);
		fclose(config);
		filter_bank fbank = filterbank(26, 512);
		hyper_vector transpose_param = setHVector(fbank.data, fbank.filt_len, fbank.nfilt, 1);
		hyper_vector tmp = transpose(transpose_param);
		int NFFT = 512;
		kiss_fft_cfg cfg = kiss_fft_alloc(NFFT, 0, 0, 0);
		kiss_fft_cpx * cx_in = (kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx)*NFFT);
		kiss_fft_cpx * cx_out = (kiss_fft_cpx*)malloc(sizeof(kiss_fft_cpx)*NFFT);
		create_database(path, current_max_index, tmp, cfg, cx_in, cx_out);
	}
	if (is_normalize_db) {
		char *path = argv[2];
		if (path == NULL) {
			fprintf(stderr, "Path no exist!");
			exit(1);
		}
		size_t len_path_folder = strlen(path);
		char *path_config = (char *)malloc(sizeof(char) *(len_path_folder + 10));
		char *path_db = (char *)malloc(sizeof(char) * (len_path_folder + 6));
		char *path_info = (char *)malloc(sizeof(char) * (len_path_folder + 8));
		char *path_meaning = (char *)malloc(sizeof(char) * (len_path_folder + 8));
		char *path_nor = (char *)malloc(sizeof(char) * (len_path_folder + 14));
		char *path_sum = (char *)malloc(sizeof(char) * (len_path_folder + 7));
		strcpy(path_config, path);
		strcat(path_config, "config.txt");
		strcpy(path_db, path);
		strcat(path_db, "db.txt");
		strcpy(path_info, path);
		strcat(path_info, "info.txt");
		strcpy(path_meaning, path);
		strcat(path_meaning, "mean.txt");
		strcpy(path_nor, path);
		strcat(path_nor, "normalized.txt");
		strcpy(path_sum, path);
		strcat(path_sum, "sum.txt");
		FILE *config = fopen(path_config, "r");
		if (config == NULL) {
			fprintf(stderr, "Config file no exist!");
			exit(1);
		}
		fscanf(config, "%d", &current_max_index);
		normalize_db(path_nor, path_meaning, path_db, path_info, path_sum, current_max_index);
	}
	if (is_train) {
		char *path = argv[argc - 1];
		training_normalize(path, argc, argv);
	}
	if (is_predict) {
		char *sent_path = argv[argc - 1];
		char *path = argv[argc - 2];
		printf("cc");

		const char *model_path_def = "normalized.model";
		const char * sum_path_def = "sum.txt";
		size_t len_path = strlen(path);
		char *model_path = (char *)malloc(sizeof(char) * (len_path + 16));
		char *sum_path = (char *)malloc(sizeof(char) * (len_path + 7));

		strcpy(model_path, path);
		strcat(model_path, model_path_def);

		strcpy(sum_path, path);
		strcat(sum_path, sum_path_def);

		struct svm_model *model;
		if ((model = svm_load_model(model_path)) == 0) {
			fprintf(stderr, "cant load model file \n");
			exit(1);
		}
		SAMPLE *sum_normal = (SAMPLE*)malloc(sizeof(SAMPLE) * 91);
		mfcc_load_normalized_sum(sum_normal, sum_path);
		int num_of_sents;
		char **words;
		words = load_words_sent(sent_path, &num_of_sents);
		/*int predict_probability;
		if (argv[2][0] != '-' && argv[2][1] != 'b') {
			predict_probability = 0;
		}
		else {
			predict_probability = 1;
		}*/
		//printf("cc");
		real_time_predict(model, sum_normal, path, sent_path, num_of_sents, words);
	}
	if (is_predict_file) 
	{
		FILE *ftemp = fopen("/home/pi/MFCC_CMAKE/build/data.txt", "r");
		hyper_vector compact_final_feats;
		compact_final_feats.data = (float*)calloc(91, sizeof(float));
		for (int i = 0; i < 91; i++) {
			fscanf(ftemp, "%f", &compact_final_feats.data[i]);
		}
		compact_final_feats.col = 91;
		compact_final_feats.dim = 1;
		compact_final_feats.row = 1;
		SAMPLE *sum_normal = (SAMPLE*)malloc(sizeof(SAMPLE) * 91);

		//////
		char *sent_path = argv[argc - 1];
		char *path = argv[argc - 2];
		//char *test_folder = argv[argc - 3];

		size_t len_path = strlen(path);

		//char *sent_path = "D:\\Visual_Studio_Workspace\\sentences\\";
		//char *path = "D:\\Visual_Studio_Workspace\\data\\scaleData\\";
		//char *test_folder = "D:\\Visual_Studio_Workspace\\test\\";
		printf("Cc1");

		const char *model_path_def = "normalized.model";
		const char *sum_path_def = "sum.txt";
		char *sum_path = (char *)malloc(sizeof(char) * (len_path + 8));
		char *model_path = (char *)malloc(sizeof(char) * (len_path + 17));


		strcpy(model_path, path);
		strcat(model_path, model_path_def);
		strcpy(sum_path, path);
		strcat(sum_path, sum_path_def);

		/////////////////
		struct svm_model *model;
		printf("Cc1");

		if ((model = svm_load_model(model_path)) == 0) {
			fprintf(stderr, "cant load model file \n");
			exit(1);
		}
		printf("Cc2");

		mfcc_load_normalized_sum(sum_normal, sum_path);
		printf("Cc3");

		//filter_bank fbank = filterbank(26, 512);

		filter_bank fbank = filterbank(26, 512);
		hyper_vector transpose_param = setHVector2(fbank.data, fbank.filt_len, fbank.nfilt, 1);		//26x257
		hyper_vector tmp = transpose(transpose_param);

		//printf("Cc");
		//int temp = predict_one_time(compact_final_feats, path, 0, model, sum_normal, tmp,1);
		//printf("label: %d", temp);
	}
	//runtest();

	return 0;
}

char **load_words_sent(char *sent_path, int *num_of_sents) {
	const char* num_sent_def = "num_sents.txt";
	const char* lwords = "words.txt";
	size_t len_path_sent = strlen(sent_path);
	char *num_sent = (char *)malloc(sizeof(char) * (len_path_sent + 14));

	/////////////num_sent///////////
	strcpy(num_sent, sent_path);
	strcat(num_sent, num_sent_def);

	char *word_path = (char *)malloc(sizeof(char) * (len_path_sent + 10));
	strcpy(word_path, sent_path);
	strcat(word_path, lwords);

	FILE* fnumt = fopen(num_sent, "r");
	fscanf(fnumt, "%d", num_of_sents);
	fclose(fnumt);
	////////////words list///////////

	FILE* fword = fopen(word_path, "r");
	int num_words;
	fscanf(fword, "%d", &num_words);

	printf("num words : %d\n", num_words);
	char **words = (char**)malloc(num_words * sizeof(char*));
	for (int i = 0; i < num_words; i++) {
		words[i] = (char*)malloc(6 * sizeof(char));
		fscanf(fword, "%s", words[i]);
		printf("%s\n", words[i]);
	}
	fclose(fword);
	return words;
}
