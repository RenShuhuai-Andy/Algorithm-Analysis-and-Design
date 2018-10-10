#ifndef	__IA_STRASSEN_H__
#define __IA_STRASSEN_H__
 
//To avoid copying data, we define ROW_STEP:
//	Arow1			Arow2
// [----------------------][----------------------]
// .............
// 
//  A11row1     A12row1     A11row2     A12row2
// [----------][----------][----------][----------]
// |<--------row_step---->|
// .............
 
typedef
struct _sm_t {
	int *add_start;
	int rows;
	int cols;
	int row_step;
}sm_t;
 
typedef
struct _sm_mem_t {
	char *addr_start;
	size_t len;
	size_t usedlen;
}sm_mem_t;
 
//-1 fail
//0 success
int square_matrix_alloc_mem(
	__in size_t size,
	__inout sm_mem_t *mem);
 
void square_matrix_free_mem(
	__in sm_mem_t *mem);
 
//return 
// -1 -- fail
// 0  -- success
int square_matrix_strassen_recursive(
	__in	sm_mem_t *mem,
	__in	sm_t *sm_A,
	__in	sm_t *sm_B,
	__inout	sm_t *sm_C);
 
#endif
