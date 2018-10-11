#include <stdio.h>
#define INF 100000//代表无穷
#define p_length 7//矩阵规模序列长度
#define maxn 6//矩阵个数
int p[p_length] = { 30,35,15,5,10,20,25 };//矩阵规模序列
int m[maxn][maxn] = { 0 };//m[i][j]代表计算矩阵A_i..j所需标量乘法次数的最小值
int s[maxn][maxn] = { 0 };//记录最优值m[i][j]对应的分割点k
// int times=0;

void matrix_chain_order() {
	for (int l = 2; l <= maxn; l++) {//l为矩阵链的长度
		for (int i = 0; i<maxn - l + 1; i++) {
			int j = i + l - 1;
			m[i][j] = INF;
			for (int k = i; k<j; k++) {
				int q = m[i][k] + m[k + 1][j] + p[i] * p[k+1] * p[j+1];
				if (q<m[i][j]) {
					m[i][j] = q;
					s[i][j] = k+1;
				}
			}
		}
	}
}

void print_optimal_parens(int i, int j) {
	if (i == j)
		printf("A%d", i);
	else {
		printf("(");
		print_optimal_parens(i, s[i-1][j-1]);
		print_optimal_parens(s[i-1][j-1]+1, j);
        // times+=m[i-1][j];
		printf(")");
	}
}

int main() {
	matrix_chain_order();
	print_optimal_parens(1, maxn);
    printf("\ntimes: %d",m[0][5]);
	return 0;
}
