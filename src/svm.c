#include "svm.h"

void kernel_function(int size_x, float *x, int size_z, float *z, KERNEL_TYPE t)
{
	if (t == LINEAR) {
		kernel_linear(size_x, x, size_z, z);
	}
	else if (t == POLYNOMIAL) {
		kernel_polynomial(size_x, x, size_z, z);
	}
	else if (t == SIGMOID) {
		kernel_sigmoid(size_x, x, size_z, z);
	}
	else if (t == RBF) {
		kernel_rbf(size_x, x, size_z, z);
	}
	else
	{
		char *err = "kernel type no exist!!! \n";
		error(err);
	}
}

void kernel_linear(int size_x, float *x, int size_z, float *z) {

}

void kernel_polynomial(int size_x, float * x, int size_z, float * z)
{

}

void kernel_sigmoid(int size_x, float * x, int size_z, float * z)
{
}

void kernel_rbf(int size_x, float * x, int size_z, float * z)
{
}
