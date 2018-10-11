//source - charset:utf - 8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #define REDIRECT
#define maxn 4
int** A;
int** B;
int** R;

int** strassen(int** A, int** B, int n,int rb0,int cb0,int rb1, int cb1, int rb2, int cb2) {
	//n代表A、B的矩阵维数
	//rb=row begin,cb=column begin.
	//rb1代表左矩阵的起始行，cb1代表左矩阵的起始列，rb2代表右矩阵的起始行，cb2代表右矩阵的起始列
	int** C = (int**)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		C[i] = (int*)malloc(n * sizeof(int));
	if (n == 1)
		C[rb0][cb0] = A[rb1][cb1] * B[rb2][cb2];
	else {
		int** S1=(int**)malloc(n/2*sizeof(int));
		for(int i=0;i<n/2;i++)
		    S1[i]=(int*)malloc(n/2*sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S1[i][j] = B[rb1 + i][cb1 + j + n / 2] - B[rb2 + i + n / 2][cb2 + j + n / 2];

		int** S2 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S2[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S2[i][j] = A[rb1 + i][cb1 + j] + A[rb2 + i][cb2 + j + n / 2];

		int** S3 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S3[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S3[i][j] = A[rb1 + i + n / 2][cb1 + j] + A[rb2 + i + n / 2][cb2 + j + n / 2];

		int** S4 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S4[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S4[i][j] = B[rb1 + i][cb1 + j + n / 2] - B[rb2 + i][cb2 + j];

		int** S5 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S5[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S5[i][j] = A[rb1 + i][cb1 + j] + A[rb2 + i + n / 2][cb2 + j + n / 2];

		int** S6 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S6[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S6[i][j] = B[rb1 + i][cb1 + j] + B[rb2 + i + n / 2][cb2 + j + n / 2];

		int** S7 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S7[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S7[i][j] = A[rb1 + i][cb1 + j + n / 2] - A[rb2 + i + n / 2][cb2 + j + n / 2];

		int** S8 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S8[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S8[i][j] = B[rb1 + i + n / 2][cb1 + j] + B[rb2 + i + n / 2][cb2 + j + n / 2];

		int** S9 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S9[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S9[i][j] = A[rb1 + i][cb1 + j] - A[rb2 + i + n / 2][cb2 + j];

		int** S10 = (int**)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			S10[i] = (int*)malloc(n / 2 * sizeof(int));
		for (int i = 0;i<n / 2;i++)
			for (int j = 0;j<n / 2;j++)
				S10[i][j] = B[rb1 + i][cb1 + j] + B[rb2 + i][cb2 + j + n / 2];
		int** P1 = strassen(A, S1, n / 2, 0,0,0, 0, 0, 0);
		int** P2 = strassen(S2, B, n / 2, 0,0,0, 0, n / 2, n / 2);
		int** P3 = strassen(S3, B, n / 2, 0,0,0, 0, 0, 0);
		int** P4 = strassen(A, S4, n / 2, 0,0,n / 2, n / 2, 0, 0);
		int** P5 = strassen(S5, S6, n / 2, 0,0,0, 0, 0, 0);
		int** P6 = strassen(S7, S8, n / 2, 0,0,0, 0, 0, 0);
		int** P7 = strassen(S9, S10, n / 2, 0,0,0, 0, 0, 0);
		for (int i = 0; i<n / 2; i++)
			for (int j = 0; j<n / 2; j++) {
				C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
				C[i][j + n / 2] = P1[i][j] + P2[i][j];
				C[i + n / 2][j] = P3[i][j] + P4[i][j];
				C[i + n / 2][j + n / 2] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
			}
	}
	return C;
}

int main() {
#ifdef REDIRECT
	freopen("./square_matrix_strassen_input.txt", "r", stdin);
	freopen("./square_matrix_strassen_output.txt", "w", stdout);
#endif
	// memset(A,0,sizeof(A));
	// memset(B,0,sizeof(B));
	// while(scanf("%d%d",&A[0][0],&A[0][1])!=EOF){
	//     scanf("%d%d",&A[1][0],&A[1,1]);
	//     getchar();
	//     scanf("%d%d",&B[0][0],&B[0][1]);
	//     scanf("%d%d",&B[1][0],&B[1][1]);
	// }

	A = (int**)malloc(maxn * sizeof(int));
	B = (int**)malloc(maxn * sizeof(int));
	for (int i = 0;i<maxn;i++) {
		A[i] = (int*)malloc(maxn * sizeof(int));
		B[i] = (int*)malloc(maxn * sizeof(int));
	}
	R = (int**)malloc(maxn*maxn * sizeof(int));
	// A[0][0] = A[0][1] = A[1][0] = A[1][1] = 1;
	// B[0][0] = B[0][1] = B[1][0] = B[1][1] = 2;
    srand((unsigned)time(NULL));
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++){
            A[i][j]=rand()%5+1;
            B[i][j]=rand()%5+1;
        }
	R = strassen(A, B, 2, 0, 0, 0, 0, 0, 0);
    for (int i = 0;i<maxn;i++) {
		int j = 0;
		for (j = 0;j<maxn - 1;j++)
			printf("%d,", A[i][j]);
		printf("%d", A[i][j]);
		printf("\n");
	}printf("\n");
    for (int i = 0;i<maxn;i++) {
		int j = 0;
		for (j = 0;j<maxn - 1;j++)
			printf("%d,", B[i][j]);
		printf("%d", B[i][j]);
		printf("\n");
	}printf("\n");
	for (int i = 0;i<maxn;i++) {
		int j = 0;
		for (j = 0;j<maxn - 1;j++)
			printf("%d,", R[i][j]);
		printf("%d", R[i][j]);
		printf("\n");
	}
	getchar();
	return 0;
}