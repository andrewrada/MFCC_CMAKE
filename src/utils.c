#include "utils.h"

int find_args(int argc, char * argv[], char * arg)
{
	int i;
	for (i = 0; i < argc; ++i) {
		if (!argv[i]) continue;
		if (0 == strcmp(argv[i], arg)) {
			return 1;
		}
	}
	return 0;
}

char * get_name_file_from_path(char * path)
{

	return NULL;
}

int cfileexists(const char * filename)
{
	/* try to open file to read */
	FILE *file;
	if (file = fopen(filename, "r")) {
		fclose(file);
		return 1;
	}
	return 0;
}

void ShortTimeFourierTransform(float * fftBuffer, long fftFrameSize, long sign)
{
	float wr = 0, wi = 0, arg = 0, temp = 0;
	float tr = 0, ti = 0, ur = 0, ui = 0;
	long i, bitm, j, le, le2, k;
	for (i = 2; i < 2 * fftFrameSize - 2; i += 2) {
		for (bitm = 2, j = 0; bitm < 2 * fftFrameSize; bitm <<= 1) {
			if ((i & bitm) != 0) {
				j++;
			}
			j <<= 1;
		}
		if (i < j) {
			temp = fftBuffer[i];
			fftBuffer[i] = fftBuffer[j];
			fftBuffer[j] = temp;
			temp = fftBuffer[i + 1];
			fftBuffer[i + 1] = fftBuffer[j + 1];
			fftBuffer[j + 1] = temp;
		}
	}
	long max = (long)(log(fftFrameSize) / log(2.0) + 0.5);
	for (k = 0, le = 2; k < max; ++k) {
		le <<= 1;
		le2 = le >> 1;
		ur = 1.0;
		ui = 0.0;
		arg = (float)M_PI / (le2 >> 1);
		wr = (float)(cos(arg));
		wi = (float)(sign * sin(arg));
		for (j = 0; j < le2; j += 2) {
			for (i = j; i < 2 * fftFrameSize; i += le) {
				tr = fftBuffer[i + le2] * ur - fftBuffer[i + le2 + 1] * ui;
				ti = fftBuffer[i + le2] * ui + fftBuffer[i + le2 + 1] * ur;
				fftBuffer[i + le2] = fftBuffer[i] - tr;
				fftBuffer[i + le2 + 1] = fftBuffer[i + 1] - ti;
				fftBuffer[i] += tr;
				fftBuffer[i + 1] += ti;
			}
			tr = ur * wr - ui * wi;
			ui = ur * wi + ui * wr;
			ur = tr;
		}
	}
}

void error(char *err)
{
	fprintf(stderr, "error : ", err);
	exit(0);
}