#ifndef GEMM_H
#define GEMM_H

/*include 
-----------------------------------------
-----------------------------------------*/

/*define, constant
-----------------------------------------
-----------------------------------------*/

typedef struct gemm_multithread_struct {
	int TA; int TB; int M; int N; int K; float ALPHA; float * A; int lda; float * B;
	int ldb; float BETA; float * C; int ldc; int id; int nb;
}gemm_multithread_struct;

/*functions
-----------------------------------------
-----------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
	void gemm(int TA, int TB, int M, int N, int K,
		float ALPHA, float *A, int lda, float *B, int ldb, float BETA, float *C, int ldc);
	void gemm_detail(int TA, int TB, int M, int N, int K,
		float ALPHA, float *A, int lda, float *B, int ldb, float BETA, float *C, int ldc);

	void gemm_nn(int M, int N, int K, float ALPHA, float *A, int lda, float *B, int ldb, float *C, int ldc);
#ifdef USE_MULTI_THREAD
	void gemm_multithread(int TA, int TB, int M, int N, int K,
		float ALPHA, float *A, int lda, float *B, int ldb, float BETA, float *C, int ldc, int id, int nb);

	void pre_gemm_detail_multithread(int M, int N, float BETA, int id, int nb, float *C);

	void gemm_detail_multithread(int TA, int TB, int M, int N, int K,
		float ALPHA, float *A, int lda, float *B, int ldb, float BETA, float *C, int ldc, int id, int nb);

	void gemm_nn_multithread(int M, int N, int K, float ALPHA, float *A, int lda, float *B, int ldb, float *C, int ldc, int id, int nb);
#endif // USE_MULTI_THREAD

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //GEMM