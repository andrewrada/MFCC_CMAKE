#include "augmentation.h"

float * pitch_shift(float pitch_shift_param, float * audio_signal, int numSampsToProcess, long fftFrameSize, long osamp, float sample_rate)
{
	float *gInFIFO = (float *)calloc(MAX_FRAME_LENGTH, sizeof(float));
	float *gOutFIFO = (float *)calloc(MAX_FRAME_LENGTH, sizeof(float));
	float *gFFTworksp = (float *)calloc(MAX_FRAME_LENGTH * 2, sizeof(float));
	float *gLastPhase = (float *)calloc((MAX_FRAME_LENGTH / 2 + 1), sizeof(float));
	float *gSumPhase = (float *)calloc((MAX_FRAME_LENGTH / 2 + 1), sizeof(float));
	float *gOutputAccum = (float *)calloc((MAX_FRAME_LENGTH * 2), sizeof(float));
	float *gAnaFreq = (float *)calloc(MAX_FRAME_LENGTH, sizeof(float));
	float *gAnaMagn = (float *)calloc(MAX_FRAME_LENGTH, sizeof(float));
	float *gSynFreq = (float *)calloc(MAX_FRAME_LENGTH, sizeof(float));
	float *gSynMagn = (float *)calloc(MAX_FRAME_LENGTH, sizeof(float));
	float *out_data = (float *)malloc(numSampsToProcess * sizeof(float));
	float magn, phase, tmp, window, real, imag;
	float freqPerBin, expct;
	long i, k, qpd, index, inFifoLatency, stepSize, fftFrameSize2;
	long gRover = 0, gInit = 0;

	fftFrameSize2 = fftFrameSize / 2;
	stepSize = fftFrameSize / osamp;
	printf("stepSize : %ld \n", stepSize);
	freqPerBin = sample_rate / (float)fftFrameSize;
	expct = 2.0 * M_PI * (float)stepSize / (float)fftFrameSize;
	inFifoLatency = fftFrameSize - stepSize;
	if (gRover == 0) gRover = inFifoLatency;

	for (i = 0; i < numSampsToProcess; ++i) {
		gInFIFO[gRover] = audio_signal[i];
		out_data[i] = gOutFIFO[gRover - inFifoLatency];
		gRover++;
		if (gRover >= fftFrameSize) {
			gRover = inFifoLatency;
			for (k = 0; k < fftFrameSize; ++k) {
				window = -0.5 * cos(2.0 * M_PI * (float)k / (float)fftFrameSize) + 0.5;
				gFFTworksp[2 * k] = (float)(gInFIFO[k] * window);
				gFFTworksp[2 * k + 1] = 0.0f;
			}
			// do Transform
			ShortTimeFourierTransform(gFFTworksp, fftFrameSize, -1);

			//analysis step
			for (k = 0; k <= fftFrameSize2; ++k) {
				real = gFFTworksp[2 * k];
				imag = gFFTworksp[2 * k + 1];
				// compute magnitude and phase
				magn = 2.0 * sqrt(real * real + imag * imag);
				phase = atan2(imag, real);
				// compute phase diffrence
				tmp = phase - gLastPhase[k];
				gLastPhase[k] = (float)phase;

				//subtract exptected phase diffence
				tmp -= (float)k * expct;

				// map delta phase into +- pi interval

				qpd = (long)(tmp / M_PI);
				if (qpd >= 0) qpd += qpd & 1;
				else qpd -= qpd & 1;
				tmp -= M_PI * (float)qpd;

				// get deviation from bin frequency from the +- pi interval

				tmp = osamp * tmp / (2.0 * M_PI);

				//compute k-th partial's true frequency

				tmp = (float)k * freqPerBin + tmp * freqPerBin;
				//store magnitude and true frequency in analysis arrays
				gAnaMagn[k] = (float)magn;
				gAnaFreq[k] = (float)tmp;
			}

			//pitch shift processing
			for (int zero = 0; zero < fftFrameSize; ++zero) {
				gSynMagn[zero] = 0;
				gSynFreq[zero] = 0;
			}
			for (k = 0; k <= fftFrameSize2; ++k) {
				index = (long)(k * pitch_shift_param);
				if (index <= fftFrameSize2) {
					gSynMagn[index] += gAnaMagn[k];
					gSynFreq[index] = gAnaFreq[k] * pitch_shift_param;
				}
			}
			// synthesis step
			for (k = 0; k <= fftFrameSize2; ++k) {
				//get magnitude and true freq from synthesis arrays
				magn = gSynMagn[k];
				tmp = gSynFreq[k];

				//subtract bin mid freq
				tmp -= (float)k * freqPerBin;

				//get bin deviation from freq deviation
				tmp /= freqPerBin;

				//take osamp into account

				tmp = 2.0 * M_PI * tmp / osamp;

				//add the overlap phase advance back in
				tmp += (float)k * expct;

				// accumulate delta phase advance back in

				gSumPhase[k] += (float)tmp;
				phase = gSumPhase[k];

				//get real and imag part and re-interleave
				gFFTworksp[2 * k] = (float)(magn * cos(phase));
				gFFTworksp[2 * k + 1] = (float)(magn * sin(phase));
			}
			//zero negative frequency
			for (k = fftFrameSize + 2; k < 2 * fftFrameSize; k++) {
				gFFTworksp[k] = 0.0f;
			}

			//inverse stft
			ShortTimeFourierTransform(gFFTworksp, fftFrameSize, 1);

			//do windowing and add to output accumulator
			for (k = 0; k < fftFrameSize; ++k) {
				window = -0.5*cos(2.0*M_PI*(float)k / (float)fftFrameSize) + 0.5;
				gOutputAccum[k] += (float)(2.0*window*gFFTworksp[2 * k] / (fftFrameSize2 *osamp));
			}
			for (k = 0; k < stepSize; ++k) {
				gOutFIFO[k] = gOutputAccum[k];
			}

			//shift accumulator
			for (k = 0; k < fftFrameSize; ++k) {
				gOutputAccum[k] = gOutputAccum[k + stepSize];
			}

			//move input fifo
			for (k = 0; k < inFifoLatency; ++k) {
				gInFIFO[k] = gInFIFO[k + stepSize];
			}
		}
	}
	free(gAnaFreq);
	free(gInFIFO);
	free(gOutFIFO);
	free(gFFTworksp);
	free(gLastPhase);
	free(gSumPhase);
	free(gOutputAccum);
	free(gAnaMagn);
	free(gSynFreq);
	free(gSynMagn);
	return out_data;
}
