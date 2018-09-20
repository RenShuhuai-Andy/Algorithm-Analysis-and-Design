#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define maxn 100
#define bucket_n 10
#define REDIRECT//输入输出重定向
// #define TCA//时间复杂度分析Time Complexity Analysis
int A[maxn];

typedef struct node{
    int key;
    struct node* next;
}KeyNode;

void bucket_sort(int* A,int A_length,int bucket_size)
{
    int i,j;
    KeyNode** bucket_table=(KeyNode**)malloc(bucket_size*sizeof(KeyNode*));
    for(i=0;i<bucket_size;i++){
        bucket_table[i]=(KeyNode*)malloc(sizeof(KeyNode));
        bucket_table[i]->key=0;
        bucket_table[i]->next=NULL;
    }
    for(j=0;j<A_length;j++){
        KeyNode* node=(KeyNode*)malloc(sizeof(KeyNode));
        node->key=A[j];
        node->next=NULL;
        int index=A[j]/10;
        KeyNode *p=bucket_table[index];
        if(p->next==0){
            bucket_table[index]->next=node;
            (bucket_table[index]->key)++;
        }
        else{
            while(p->next!=NULL && p->next->key <= node->key)
                p=p->next;
            node->next=p->next;
            p->next=node;
            (bucket_table[index]->key)++;
        }
    }
    #ifndef TCA
        //打印结果
        KeyNode* k=NULL;
        for(i=0;i<bucket_size;i++)
            for(k=bucket_table[i]->next;k!=NULL;k=k->next)
                printf("%d ",k->key);
        printf("\n");
    #endif
}

int main()
{
    #ifdef TCA
        srand((unsigned)time(NULL));
        int max=-1000;
        int min=1000;
        for(int i=0;i<maxn;i++){
            A[i]=rand()%maxn+1;
            if(A[i]<min)
                min=A[i];
            if(A[i]>max)
                max=A[i];
        }
        int A_length=sizeof(A)/sizeof(int);
        clock_t start,end;
        start=clock();
        bucket_sort(A,A_length,(max-min)/A_length);
        end=clock();
        printf("time=%f\n",(double)(end-start)/CLK_TCK);
    #endif

    #ifdef REDIRECT
        freopen("./bucket_sort_input.txt","r",stdin);
        freopen("./bucket_sort_output.txt","w",stdout);
        int A_length=0;
        int x;
        while(scanf("%d",&x)){
            if(x!=-1)
                A[A_length++]=x;
            else{
                bucket_sort(A,A_length,bucket_n);
                A_length=0;
                continue;
            }
        }
    #endif
    return 0;
}
