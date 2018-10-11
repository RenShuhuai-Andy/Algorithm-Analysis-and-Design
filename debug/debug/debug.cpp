#include <stdio.h>
#define INF 100000//��������
#define p_length 7//�����ģ���г���
#define maxn 6//�������
int p[p_length] = { 30,35,15,5,10,20,25 };//�����ģ����
int m[maxn][maxn] = { 0 };//m[i][j]����������A_i..j��������˷���������Сֵ
int s[maxn][maxn] = { 0 };//��¼����ֵm[i][j]��Ӧ�ķָ��k

void matrix_chain_order() {
	for (int l = 2; l <= maxn; l++) {//lΪ�������ĳ���
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
	if (i == j-1)
		printf("A_%d", i+1);
	else {
		printf("(");
		print_optimal_parens(i, s[i][j-1]);
		print_optimal_parens(s[i][j]+1, j);
		printf(")");
	}
}

int main() {
	matrix_chain_order();
	print_optimal_parens(0, maxn-1);
	return 0;
}