#ifndef SVM
#define SVM

/*include
---------------------------------------
---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"

/*constant, define
---------------------------------------
---------------------------------------*/
typedef struct svm_properties {
	int dim_data;
	uint64_t number_of_data_point;
	int *labels;
	float *K;
	int *one_vector;
}svm_properties;

typedef enum KERNEL_TYPE {
	LINEAR,
	POLYNOMIAL,
	SIGMOID,
	RBF
}KERNEL_TYPE;


/*functions
---------------------------------------
---------------------------------------*/

void kernel_function(int size_x, float *x, int size_z, float *z, KERNEL_TYPE t);
void kernel_linear(int size_x, float *x, int size_z, float *z);
void kernel_polynomial(int size_x, float *x, int size_z, float *z);
void kernel_sigmoid(int size_x, float *x, int size_z, float *z);
void kernel_rbf(int size_x, float *x, int size_z, float *z);
#endif