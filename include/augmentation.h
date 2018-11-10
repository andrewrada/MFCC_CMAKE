#ifndef AUGMENTATION_H
#define AUGMENTATION_H

/*includes
---------------------------------------
---------------------------------------*/
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/*define, constant
---------------------------------------
---------------------------------------*/
#define MAX_FRAME_LENGTH	16000

/*functions
---------------------------------------
---------------------------------------*/

//shift the pitch of the audio signal
//pitch_shift_param la chi so giam pitch. Trong do 1.0 tuong ung voi giu nguyen pitch cua am thanh, 0.5 tuong ung voi tam cung xuong, 1.5 tuong ung voi tam cung len
//numSampsToProcess la size cua audio_signal
//fftFrameSize la size cua khung bien doi Fourier cho thuat toan stft(short time fourier transform) thuong nhan cac gia tri 1024, 2048, ....
//osamp la he so do su chong cheo giua 2 khung stft, recommend dat gia tri la 32
//sample_rate la tan so lay mau cua audio_signal
//exp : float *x = pitch_shift(0.5, audio_signal, 80000, 2048, 10, 16000);
float *pitch_shift(float pitch_shift_param, float *audio_signal, int numSampsToProcess, long fftFrameSize, long osamp, float sample_rate);
#endif //AUGMENTATION_H