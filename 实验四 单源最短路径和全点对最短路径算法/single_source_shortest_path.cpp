#include <stdio.h>
#define INF 100000
#define V_NUM 5
#define E_NUM 10
#define PRINT_VERBOSE//是否打印边的权重

typedef struct{
    char id;
    int d;
    char father_id;
}VERTEX;
typedef struct{
    int value;
    char start_id;
    char end_id;
}EDGE;

VERTEX vertexes[V_NUM];//顶点集
EDGE edges[E_NUM];//边集
char vertex_name[V_NUM]={'s','t','x','y','z'};

int w(VERTEX u,VERTEX v){
    //返回边(u,v)的权重
    for(int i=0;i<E_NUM;i++){
        if(edges[i].start_id==u.id && edges[i].end_id==v.id)
            return edges[i].value;
    }
}

void initialize_edges(){
    edges[0].start_id='s';
    edges[0].end_id='t';
    edges[0].value=6;

    edges[1].start_id='s';
    edges[1].end_id='y';
    edges[1].value=7;

    edges[2].start_id='t';
    edges[2].end_id='y';
    edges[2].value=8;

    edges[3].start_id='t';
    edges[3].end_id='x';
    edges[3].value=5;

    edges[4].start_id='t';
    edges[4].end_id='z';
    edges[4].value=-4;

    edges[5].start_id='x';
    edges[5].end_id='t';
    edges[5].value=-2;

    edges[6].start_id='y';
    edges[6].end_id='x';
    edges[6].value=-3;

    edges[7].start_id='y';
    edges[7].end_id='z';
    edges[7].value=9;

    edges[8].start_id='z';
    edges[8].end_id='s';
    edges[8].value=2;

    edges[9].start_id='z';
    edges[9].end_id='x';
    edges[9].value=7;
}

void initialize_single_source(){
    for(int i=0;i<V_NUM;i++){
        vertexes[i].id=vertex_name[i];
        vertexes[i].d=INF;
        vertexes[i].father_id=-1;
    }
    vertexes[0].d=0;
}        

void relax(VERTEX* u,VERTEX* v){
    //P377 松弛操作
    if(u->d==INF && v->d==INF)
        return;
    else if(v->d > u->d + w(*u,*v)){
        v->d=u->d + w(*u,*v);
        v->father_id=u->id;
    }
}

bool bellman_ford(){
    //P379
    initialize_single_source();
    initialize_edges();
    for(int i=0;i<V_NUM-1;i++){//对每条边进行V_NUM-1次松弛操作
        for(int j=0;j<E_NUM;j++){//遍历每条边
            VERTEX *u=NULL,*v=NULL;
            for(int k=0;k<V_NUM;k++){
                if(vertexes[k].id==edges[j].start_id)
                    u=&vertexes[k];
                if(vertexes[k].id==edges[j].end_id)
                    v=&vertexes[k];
            }
            relax(u,v);
        }
    }
    //查找是否存在一个从源节点可以到达的权重为负值的环路
    for(int i=0;i<E_NUM;i++){
        VERTEX u,v;
        for(int k=0;k<V_NUM;k++){
            if(vertexes[k].id==edges[i].start_id)
                u=vertexes[k];
            if(vertexes[k].id==edges[i].end_id)
                v=vertexes[k];
        }
        if(v.d>u.d + w(u,v))
            return false;
    }
    return true;
}

void dag_shortest_paths(){

}

void print_singel_source_shortest_path(){
    //vertexes[0]是源结点
    printf("s ");
    char print_id='s';//代表当前打印结点的id
    VERTEX u,v;
    for(int i=1;i<V_NUM;i++){
        for(int j=1;j<V_NUM;j++){
            if(vertexes[j].father_id==print_id){
                #ifdef PRINT_VERBOSE//是否打印边的权重
                for(int k=0;k<V_NUM;k++){
                    if(vertexes[k].id==print_id)
                        u=vertexes[k];
                    if(vertexes[k].id==vertexes[j].id)
                        v=vertexes[k];
                }
                printf("——> %d ",w(u,v));
                #endif
                printf("——> %c(%d) ",vertexes[j].id,vertexes[j].d);
                print_id=vertexes[j].id;//更新当前打印结点的id
            }
        }
    }
    for(int i=1;i<V_NUM;i++){
        if(vertexes[i].id==print_id)
            printf("\nthe distance of single source shortest path is %d.\n",vertexes[i].d);
    }
}

int main(){
    bool has_sssp=bellman_ford();
    if(has_sssp)
        printf("has single shortest path\n");
    else
        printf("no single shortest path\n");
    print_singel_source_shortest_path();
    return 0;
}