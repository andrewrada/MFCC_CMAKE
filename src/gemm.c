#include "gemm.h"

void gemm(int TA, int TB, int M, int N, int K, float ALPHA, float * A, int lda, float * B, int ldb, float BETA, float * C, int ldc)
{
	gemm_detail(TA, TB, M, N, K, ALPHA, A, lda, B, ldb, BETA, C, ldc);
}

void gemm_detail(int TA, int TB, int M, int N, int K, float ALPHA, float * A, int lda, float * B, int ldb, float BETA, float * C, int ldc)
{
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			C[i * N + j] *= BETA;
		}
	}

	if (!TA && !TB)
		gemm_nn(M, N, K, ALPHA, A, lda, B, ldb, C, ldc);
}

void gemm_nn(int M, int N, int K, float ALPHA, float * A, int lda, float * B, int ldb, float * C, int ldc)
{
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < K; ++j) {
			register float A_PART = ALPHA * A[i * lda + j];
			for (int k = 0; k < N; ++k) {
				C[i * ldc + j] += A_PART * B[j * ldb + k];
			}
		}
	}
}

#ifdef USE_MULTI_THREAD
void gemm_multithread(int TA, int TB, int M, int N, int K, float ALPHA, float * A, int lda, float * B, int ldb, float BETA, float * C, int ldc, int id, int nb)
{
	gemm_detail_multithread(TA, TB, M, N, K, ALPHA, A, lda, B, ldb, BETA, C, ldc, id, nb);
}

void pre_gemm_detail_multithread(int M, int N, float BETA, int id, int nb, float * C)
{
	int size = M * N;
	int alpha = N;
	int index_of_thread = size * id / nb;
	int index_of_next_thread = size * (id + 1) / nb;
	int h_index = index_of_thread / alpha;
	int w_index = index_of_thread - h_index * alpha;
	int h_index_next = index_of_next_thread / alpha;
	int w_index_next = index_of_next_thread - h_index_next * alpha;
	for (int i = h_index; i <= h_index_next; ++i) {
		if (h_index == h_index_next) {
			for (int j = w_index; j < w_index_next; ++j) {
				C[i * N + j] *= BETA;
			}
		}
		else {
			if (i == h_index_next) {
				for (int j = w_index; j < w_index_next; ++j) {
					C[i * N + j] *= BETA;
				}
			}
			else {
				for (int j = w_index; j < alpha; ++j) {
					C[i * N + j] *= BETA;
				}
				w_index = 0;
			}
		}
	}
}

void gemm_detail_multithread(int TA, int TB, int M, int N, int K, float ALPHA, float * A, int lda, float * B, int ldb, float BETA, float * C, int ldc, int id, int nb)
{
#ifdef USE_MULTI_OF_MULTI
	pre_gemm_detail_multithread(M, N, BETA, id, nb, C);
#else
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			C[i * N + j] *= BETA;
		}
	}
#endif

	if (!TA && !TB)
		gemm_nn_multithread(M, N, K, ALPHA, A, lda, B, ldb, C, ldc, id, nb);
}

void gemm_nn_multithread(int M, int N, int K, float ALPHA, float * A, int lda, float * B, int ldb, float * C, int ldc, int id, int nb)
{
	int size = M * K;
	int alpha = K;
	int index_of_thread = size * id / nb;
	int index_of_next_thread = size * (id + 1) / nb;
	int h_index = index_of_thread / alpha;
	int w_index = index_of_thread - h_index * alpha;
	int h_index_next = index_of_next_thread / alpha;
	int w_index_next = index_of_next_thread - h_index_next * alpha;
	for (int i = h_index; i <= h_index_next; ++i) {
		if (h_index == h_index_next) {
			for (int j = w_index; j < w_index_next; j++) {
				register float A_PART = ALPHA * A[i * lda + j];
				for (int k = 0; k < N; ++k) {
					C[i * ldc + j] += A_PART * B[j * ldb + k];
				}
			}
		}
		else {
			if (i == h_index_next) {
				for (int j = w_index; j < w_index_next; ++j) {
					register float A_PART = ALPHA * A[i * lda + j];
					for (int k = 0; k < N; ++k) {
						C[i * ldc + j] += A_PART * B[j * ldb + k];
					}
				}
			}
			else {
				for (int j = w_index; j < K; ++j) {
					register float A_PART = ALPHA * A[i * lda + j];
					for (int k = 0; k < N; ++k) {
						C[i * ldc + j] += A_PART * B[j * ldb + k];
					}
				}
			}
			w_index = 0;
		}
	}
}
#endif //end use_multi_thread
