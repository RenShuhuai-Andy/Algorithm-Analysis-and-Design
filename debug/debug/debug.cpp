#include <stdio.h>
#define INF 100000
#define V_NUM 5
#define E_NUM 9
// #define PRINTF_VERBOSE

typedef struct {
	char id;
	int d;
	char father_id;
}VERTEX;
typedef struct {
	int value;
	char start_id;
	char end_id;
}EDGE;

VERTEX vertexes[V_NUM];//顶点集
EDGE edges[E_NUM];//边集
int W[V_NUM][V_NUM];//P399输入矩阵，代表有向图边的权重
int PI[V_NUM][V_NUM];//P399前驱节点矩阵
int PI_next[V_NUM][V_NUM];//同PI
int L[V_NUM][V_NUM];//P401存储每一次松弛后的路径的实际权重
int L_next[V_NUM][V_NUM];//同L

char vertex_name[V_NUM] = { '1','2','3','4','5' };

bool is_edge(char uid, char vid) {
	for (int i = 0; i<E_NUM; i++) {
		if (edges[i].start_id == uid && edges[i].end_id == vid)
			return true;
	}
	return false;
}

int w(VERTEX u, VERTEX v) {
	//返回边(u,v)的权重
	for (int i = 0; i<E_NUM; i++) {
		if (edges[i].start_id == u.id && edges[i].end_id == v.id)
			return edges[i].value;
	}
	return 0;
}

void initialize_edges() {
	edges[0].start_id = '1';
	edges[0].end_id = '2';
	edges[0].value = 3;

	edges[1].start_id = '1';
	edges[1].end_id = '3';
	edges[1].value = 8;

	edges[2].start_id = '1';
	edges[2].end_id = '5';
	edges[2].value = -4;

	edges[3].start_id = '2';
	edges[3].end_id = '4';
	edges[3].value = 1;

	edges[4].start_id = '2';
	edges[4].end_id = '5';
	edges[4].value = 7;

	edges[5].start_id = '3';
	edges[5].end_id = '2';
	edges[5].value = 4;

	edges[6].start_id = '4';
	edges[6].end_id = '1';
	edges[6].value = 2;

	edges[7].start_id = '4';
	edges[7].end_id = '3';
	edges[7].value = -5;

	edges[8].start_id = '5';
	edges[8].end_id = '4';
	edges[8].value = 6;
}

void initialize_matrix() {
	//initialize W and L
	for (int i = 0; i<V_NUM; i++) {
		for (int j = 0; j<V_NUM; j++) {
			if (i == j)
				W[i][j] = L[i][j] = 0;
			if (i != j && is_edge(i + '0' + 1, j + '0' + 1)) {//注意+1，因为vertex的编码是从1开始的
				VERTEX u, v;
				for (int k = 0; k<V_NUM; k++) {
					if (vertexes[k].id == i + '0' + 1)
						u = vertexes[k];
					if (vertexes[k].id == j + '0' + 1)
						v = vertexes[k];
				}
				W[i][j] = L[i][j] = w(u, v);
			}
			if (i != j && !is_edge(i + '0' + 1, j + '0' + 1))
				W[i][j] = L[i][j] = INF;
		}
	}
	//initialize PI
	for (int i = 0; i<V_NUM; i++) {
		for (int j = 0; j<V_NUM; j++) {
			if (i == j || !is_edge(i + '0' + 1, j + '0' + 1))
				PI[i][j] = -1;//-1代表NULL
			else {
				for (int k = 0; k<V_NUM; k++)
					if (vertexes[k].id == j + '0' + 1)
						PI[i][j] = i + 1;
				// PI[i][j]=vertexes[k].father_id-'0';
			}
		}
	}
}

void initialize_single_source() {
	for (int i = 0; i<V_NUM; i++) {
		vertexes[i].id = vertex_name[i];
		vertexes[i].d = INF;
		vertexes[i].father_id = -1;
	}
	vertexes[0].d = 0;
}

void relax(VERTEX* u, VERTEX* v) {
	//P377 松弛操作
	if (u->d == INF && v->d == INF)
		return;
	else if (v->d > u->d + w(*u, *v)) {
		v->d = u->d + w(*u, *v);
		v->father_id = u->id;
	}
}

void extend_shortest_paths(int L_tem[V_NUM][V_NUM], int W_tem[V_NUM][V_NUM]) {
	//P401
	//L has been initialized in initialize_matrix()
	for (int i = 0; i<V_NUM; i++)
		for (int j = 0; j<V_NUM; j++) {
			L_tem[i][j] = INF;
			VERTEX u, v;
			int k_final = -1;
			for (int k = 0; k<V_NUM; k++) {
				if ((L_tem[i][j] == INF && L[i][k] == INF) || (L_tem[i][j] == INF && W_tem[k][j] == INF)) {}
				// if(L_tem[i][j]==INF && W_tem[k][j]==INF){}
				else {
					// PI[i][j]=(L_tem[i][j] < L[i][k]+W_tem[k][j]) ? PI[i][j] : PI[k][j];
					// PI_next[i][j]=(L_tem[i][j] < L[i][k]+W_tem[k][j]) ? PI[i][j] : PI[k][j];
					if (L_tem[i][j] >= L[i][k] + W_tem[k][j])
						k_final = k;
					L_tem[i][j] = (L_tem[i][j] < L[i][k] + W_tem[k][j]) ? L_tem[i][j] : L[i][k] + W_tem[k][j];
				}
			}
			if (k_final != -1)
				PI[i][j] = PI[k_final][j];
		}
}

void slow_all_pairs_shortest_paths() {
	//L has been initialized in initialize_matrix()
	for (int m = 1; m<V_NUM - 1; m++) {
#ifdef PRINTF_VERBOSE
		for (int i = 0; i<V_NUM; i++) {
			for (int j = 0; j<V_NUM; j++) {
				if (L[i][j]>INF - INF / 10)
					printf("INF ");
				else
					printf("%3d ", L[i][j]);
			}
		}
		printf("--------------------------\n");
#endif  

		// extend_shortest_paths();
		extend_shortest_paths(L_next, W);
		//copy L_next to L, copy PI_next to PI
		for (int i = 0; i<V_NUM; i++)
			for (int j = 0; j<V_NUM; j++) {
				L[i][j] = L_next[i][j];
				// PI[i][j]=PI_next[i][j];
			}
	}
}

//WRONG!!!!
void faster_all_pairs_shortest_paths() {
	//L has been initialized in initialize_matrix()
	int m = 1;
	while (m<V_NUM - 1) {
#ifdef PRINTF_VERBOSE
		for (int i = 0; i<V_NUM; i++) {
			for (int j = 0; j<V_NUM; j++) {
				if (L[i][j]>INF - INF / 10)
					printf("INF ");
				else
					printf("%3d ", L[i][j]);
			}
		}
		printf("--------------------------\n");
#endif  

		extend_shortest_paths(L_next, L_next);
		//copy L_next to L, copy PI_next to PI
		for (int i = 0; i<V_NUM; i++)
			for (int j = 0; j<V_NUM; j++) {
				L[i][j] = L_next[i][j];
				PI[i][j] = PI_next[i][j];
			}
		m *= 2;
	}
}

void floyd_warshall() {
	for (int k = 0; k<V_NUM; k++) {
#ifdef PRINTF_VERBOSE
		for (int i = 0; i<V_NUM; i++) {
			for (int j = 0; j<V_NUM; j++) {
				if (L[i][j]>INF - INF / 10)
					printf("INF ");
				else
					printf("%3d ", L[i][j]);
			}
			printf("\n");
		}
		printf("--------------------------\n");
#endif  

		for (int i = 0; i<V_NUM; i++)
			for (int j = 0; j<V_NUM; j++) {
				L_next[i][j] = (L[i][j]<L[i][k] + L[k][j]) ? L[i][j] : L[i][k] + L[k][j];
				PI_next[i][j] = (L[i][j] <= L[i][k] + L[k][j]) ? PI[i][j] : PI[k][j];
			}

		//copy L_next to L, copy PI_next to PI
		for (int i = 0; i<V_NUM; i++)
			for (int j = 0; j<V_NUM; j++) {
				L[i][j] = L_next[i][j];
				PI[i][j] = PI_next[i][j];
			}
	}
}

void print_all_pairs_shortest_path(int i, int j) {
	if (i == j)
		printf("%d ——> ", i);
	else if (PI[i][j] == -1)
		printf("no path from %d to %d\n", i, j);
	else {
		print_all_pairs_shortest_path(i, PI[i - 1][j - 1]);
		printf("%d ——> ", j);
	}
}

int main() {
	initialize_edges();
	initialize_single_source();
	initialize_matrix();
	for (int i = 0; i<V_NUM; i++) {
		for (int j = 0; j<V_NUM; j++) {
			if (PI[i][j] == -1)
				printf("NIL ");
			else
				printf("%3d ", PI[i][j]);
		}
		printf("\n");
	}
	slow_all_pairs_shortest_paths();
	// for(int i=0;i<V_NUM;i++){
	//     for(int j=0;j<V_NUM;j++){
	//         if(W[i][j]==INF)
	//             printf("INF ");
	//         else
	//             printf("%3d ",W[i][j]);
	//     }
	//     printf("\n");
	// }

	// faster_all_pairs_shortest_paths();
	// floyd_warshall();
	//printf result
	printf("DI^(%d):\n", V_NUM);
	for (int i = 0; i<V_NUM; i++) {
		for (int j = 0; j<V_NUM; j++)
			printf("%3d ", L[i][j]);
		printf("\n");
	}
	printf("\nPI^(%d):\n", V_NUM);
	for (int i = 0; i<V_NUM; i++) {
		for (int j = 0; j<V_NUM; j++) {
			if (PI[i][j] == -1)
				printf("NIL ");
			else
				printf("%3d ", PI[i][j]);
		}
		printf("\n");
	}
	int i = 2, j = 1;
	printf("\nthe distance of (%d,%d) is %d.\nthe path is:", i, j, L[i - 1][j - 1]);
	print_all_pairs_shortest_path(i, j);
	return 0;
}