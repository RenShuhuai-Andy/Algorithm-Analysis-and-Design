#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define REDIRECT//输入输出重定向
// #define TCA//时间复杂度分析
#define maxn 1000
int A[maxn];
int B[maxn];
int C[maxn];

void counting_sort(int* A,int* B,int k,int A_length){
    memset(C,0,sizeof(C));
    memset(B,0,sizeof(B));
    for(int j=0;j<A_length;j++)
        C[A[j]]=C[A[j]]+1;//C[i]存放着A数组中等于i的元素个数
    for(int i=1;i<=k;i++)
        C[i]=C[i]+C[i-1];//C[i]存放着A数组中小于等于i的元素个数
    for(int j=A_length-1;j>=0;j--){
        B[C[A[j]]-1]=A[j];
        C[A[j]]=C[A[j]]-1;
    }
}

int main()
{
    #ifdef REDIRECT
        freopen("./counting_sort_input.txt","r",stdin);
        freopen("./counting_sort_output.txt","w",stdout);
        int k;
        while(scanf("%d",&k)!=EOF){
            int A_length=0;
            int x;
            while(scanf("%d",&x)){
                if(x!=-1)
                    A[A_length++]=x;
                else
                    break;
            }
            counting_sort(A,B,k,A_length);
            for(int i=0;i<A_length;i++)
                printf("%d ",B[i]);
            printf("\n");
        }
    #endif

    #ifdef TCA
        srand((unsigned)time(NULL));
        for(int i=0;i<maxn;i++)
            A[i]=rand()%maxn+1;
        int A_length=sizeof(A)/sizeof(int);
        int k=maxn;
        clock_t start,end;
        start=clock();
        counting_sort(A,B,k,A_length);
        end=clock();
        printf("time=%f\n",(double)(end-start)/CLK_TCK);
    #endif
    return 0;
}
