#include <common.h>
#include <math.h>
#include <Windows.h>
#include "strassen.h"
 
#define SM_SUB11(sm) sm[0]
#define SM_SUB12(sm) sm[1]
#define SM_SUB21(sm) sm[2]
#define SM_SUB22(sm) sm[3]
 
//2. 构造加减法运算
//sm_C = sm_A + sm_B
//no check here
static void square_matrix_add(
	__in sm_t *sm_A,
	__in sm_t *sm_B,
	__inout sm_t *sm_C)
{
	int i,j;
	for (i = 0; i < sm_A->rows; ++i) {
		for (j = 0; j < sm_A->cols; ++j) {
			sm_C->add_start[i*sm_C->row_step + j] =
				sm_A->add_start[i*sm_A->row_step + j] +
				sm_B->add_start[i*sm_B->row_step + j];
		}
	}
}
 
//sm_C = sm_A - sm_B
//no check here
static void square_matrix_sub(
	__in sm_t *sm_A,
	__in sm_t *sm_B,
	__inout sm_t *sm_C)
{
	int i,j;
	for (i = 0; i < sm_A->rows; ++i) {
		for (j = 0; j < sm_A->cols; ++j) {
			sm_C->add_start[i*sm_C->row_step + j] =
				sm_A->add_start[i*sm_A->row_step + j] -
				sm_B->add_start[i*sm_B->row_step + j];
		}
	}
}
 
//-1 fail
//0 success
int square_matrix_alloc_mem(
	__in size_t size,
	__inout sm_mem_t *mem)
{
	size_t mem_size = 0;
	int i = 0;
	int seven = 1;
 
	while(size > 1) {
		size = size/2;
		mem_size += size*size * seven;
		seven *= 7;
		i++;
	}
 
	mem_size = sizeof(int) * 17 * mem_size;
	mem_size += 0x3ff;
	mem_size -= mem_size%0x400;
 
	TRACE("square matrix size %d memory size 0x%08X\n", size, mem_size);
 
	if (mem_size == 0) {
		return 0;
	}
 
	//mem->addr_start = (char *) malloc(mem_size);
	mem->addr_start = (char *) VirtualAlloc(
					NULL,
					mem_size,
					MEM_COMMIT,
					PAGE_READWRITE);
 
	if (mem->addr_start == NULL) {
		TRACE("Last error %d\n", GetLastError());
		return -1;
	}
 
	//memset(mem->addr_start, 0, mem_size);
	mem->len = mem_size;
	mem->usedlen = 0;
	return 0;
}
 
void square_matrix_free_mem(
	__in sm_mem_t *mem)
{
	if (mem->addr_start != NULL) {
		VirtualFree(mem->addr_start, 0, MEM_RELEASE);
	}
}
 
 
 
//return 
// -1 -- fail
// 0  -- success
int square_matrix_strassen_recursive(
	__in	sm_mem_t *mem,
	__in	sm_t *sm_A,
	__in	sm_t *sm_B,
	__inout	sm_t *sm_C)
{
	int ret = 0;
	int sm_size =  sm_A->rows;
	int hs = sm_size/2;
	sm_t Asub[4];
	sm_t Bsub[4];
	sm_t Csub[4];
	sm_t S[10];
	sm_t P[7];
	int i = 0;
	if (sm_size == 1) {
		*(sm_C->add_start) += \
			(*(sm_A->add_start)) * (*(sm_B->add_start));
		return 0;
	}
 
	//check memory
	if (17 * (hs * hs) * sizeof(int) > (mem->len - mem->usedlen)) {
		ret = -1;
		goto l_exit;
	}
 
	//malloc memory for S[]
	memset(S, sizeof(S), 0);
	for (i = 0; i < sizeof(S)/sizeof(sm_t); ++i) {
		//S[i].add_start = (int *)malloc(sizeof(int) * hs * hs);
		S[i].add_start = (int *)(mem->addr_start + mem->usedlen);
		mem->usedlen += sizeof(int) * hs * hs;
		if (S[i].add_start == NULL) {
			ret = -1;
			goto l_exit;
		}
		//TODO: useless
		memset(S[i].add_start, 0, sizeof(int) * hs * hs);
		S[i].row_step = hs;
		S[i].rows = hs;
		S[i].cols = hs;
	}
 
	//malloc memory for P[]
	memset(P, sizeof(P), 0);
	for (i = 0; i < sizeof(P)/sizeof(sm_t); ++i) {
		//P[i].add_start = (int *)malloc(sizeof(int) * hs * hs);
		P[i].add_start = (int *)(mem->addr_start + mem->usedlen);
		mem->usedlen += sizeof(int) * hs * hs;
		if (P[i].add_start == NULL) {
			ret = -1;
			goto l_exit;
		}
		memset(P[i].add_start, 0, sizeof(int) * hs * hs);
		P[i].row_step = hs;
		P[i].rows = hs;
		P[i].cols = hs;
	}
 
	for (i = 0; i < 4; ++i) {
		Asub[i].row_step = sm_A->row_step;
		Asub[i].rows = hs;
		Asub[i].cols = hs;
		Asub[i].add_start = sm_A->add_start + 
			(i/2) * sm_A->row_step * hs + (i%2) * hs;
 
		Bsub[i].row_step = sm_B->row_step;
		Bsub[i].rows = hs;
		Bsub[i].cols = hs;
		Bsub[i].add_start = sm_B->add_start +
			(i/2) * sm_B->row_step * hs + (i%2) * hs;
 
		Csub[i].row_step = sm_C->row_step;
		Csub[i].rows = hs;
		Csub[i].cols = hs;
		Csub[i].add_start = sm_C->add_start +
			(i/2) * sm_C->row_step * hs + (i%2) * hs;
	}
 
	//Get S[]
	//S1=B12 - B22
	square_matrix_sub(&SM_SUB12(Bsub), &SM_SUB22(Bsub), &S[0]);
	//S2=A11 + A12
	square_matrix_add(&SM_SUB11(Asub), &SM_SUB12(Asub), &S[1]);
	//S3=A21 + A22
	square_matrix_add(&SM_SUB21(Asub), &SM_SUB22(Asub), &S[2]);
	//S4=B21 - B11
	square_matrix_sub(&SM_SUB21(Bsub), &SM_SUB11(Bsub), &S[3]);
	//S5=A11 + A22
	square_matrix_add(&SM_SUB11(Asub), &SM_SUB22(Asub), &S[4]);
	//S6=B11 + B22
	square_matrix_add(&SM_SUB11(Bsub), &SM_SUB22(Bsub), &S[5]);
	//S7=A12 - A22
	square_matrix_sub(&SM_SUB12(Asub), &SM_SUB22(Asub), &S[6]);
	//S8=B21 + B22
	square_matrix_add(&SM_SUB21(Bsub), &SM_SUB22(Bsub), &S[7]);
	//S9=A11 - A21
	square_matrix_sub(&SM_SUB11(Asub), &SM_SUB21(Asub), &S[8]);
	//S10=B11 + B12
	square_matrix_add(&SM_SUB11(Bsub), &SM_SUB12(Bsub), &S[9]);
 
	//Get P
	//P1= A11 * S1
	if (ret = square_matrix_strassen_recursive(
			mem,
			&SM_SUB11(Asub),
			&S[0],
			&P[0])) {
		goto l_exit;
	}
 
	//P2 = S2 * B22
	if (ret = square_matrix_strassen_recursive(
			mem,
			&S[1],
			&SM_SUB22(Bsub),
			&P[1])) {
		goto l_exit;
	}
 
	//P3 = S3 * B11
	if (ret = square_matrix_strassen_recursive(
			mem,
			&S[2],
			&SM_SUB11(Bsub),
			&P[2])) {
		goto l_exit;
	}
 
	//P4 = A22 * S4
	if (ret = square_matrix_strassen_recursive(
			mem,
			&SM_SUB22(Asub),
			&S[3],
			&P[3])) {
		goto l_exit;
	}
 
	//P5 = S5 * S6
	if (ret = square_matrix_strassen_recursive(
			mem,
			&S[4],
			&S[5],
			&P[4])) {
		goto l_exit;
	}
 
	//P6 = S7 * S8
	if (ret = square_matrix_strassen_recursive(
			mem,
			&S[6],
			&S[7],
			&P[5])) {
		goto l_exit;
	}
 
	//P7 = S9 * S10
	if (ret = square_matrix_strassen_recursive(
			mem,
			&S[8],
			&S[9],
			&P[6])) {
		goto l_exit;
	}
 
	//Get the result
	//C11 = P5 + P4 - P2 + P6
	square_matrix_add(&P[4], &P[3], &SM_SUB11(Csub));
	square_matrix_sub(&SM_SUB11(Csub), &P[1], &SM_SUB11(Csub));
	square_matrix_add(&SM_SUB11(Csub), &P[5], &SM_SUB11(Csub));
 
	//C12 = P1 + P2
	square_matrix_add(&P[0], &P[1], &SM_SUB12(Csub));
 
	//C21 = P3 + P4
	square_matrix_add(&P[2], &P[3], &SM_SUB21(Csub));
 
	//C22 = P5 + P1 - P3 - P7
	square_matrix_add(&P[4], &P[0], &SM_SUB22(Csub));
	square_matrix_sub(&SM_SUB22(Csub), &P[2], &SM_SUB22(Csub));
	square_matrix_sub(&SM_SUB22(Csub), &P[6], &SM_SUB22(Csub));
 
l_exit:
	/*
	//free memory
	for ( i = 0; i < sizeof(S)/sizeof(sm_t); ++i) {
		if (S[i].add_start)
			free(S[i].add_start);
	}
	for ( i = 0; i < sizeof(P)/sizeof(sm_t); ++i) {
		if (P[i].add_start)
			free(P[i].add_start);
	}*/
 
	if (ret) {
		TRACE("strassen fail\n");
	}
	return ret;
}
