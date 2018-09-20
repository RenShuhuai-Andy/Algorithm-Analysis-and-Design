#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxn 1000
#define REDIRECT//输入输出重定向
// #define TCA//时间复杂度分析
int A[maxn];

void exchange(int* a,int* b)
{
    int tem=*a;
    *a=*b;
    *b=tem;
}

int partition(int* A,int p,int r)
{
    int x=A[r];//主元
    int i=p-1;
    for(int j=p;j<r;j++){
        if(A[j]<=x){
            i++;
            exchange(A+i,A+j);
        }
    }
    exchange(A+i+1,A+r);
    return i+1;
}

void quicksort(int* A,int p,int r)
{
    if(p<r){
        int q=partition(A,p,r);
        quicksort(A,p,q-1);
        quicksort(A,q+1,r);
    }
}

int main()
{
    #ifdef REDIRECT
        freopen("./quicksort_input.txt","r",stdin);
        freopen("./quicksort_output.txt","w",stdout);
        int p,r;
        while(scanf("%d%d",&p,&r)!=EOF)
        {
            int x;
            int i=0;
            while(scanf("%d",&x)!=EOF){
                if(x!=-1)
                    A[i++]=x;
                else
                    break;
            }
            quicksort(A,p,r);
            for(int i=0;i<=r;i++)
                printf("%d ",A[i]);
            printf("\n");
        }
    #endif

    #ifdef TCA
        srand((unsigned)time(NULL));
        for(int i=0;i<maxn;i++)
            A[i]=rand()%maxn+1;
        int A_length=sizeof(A)/sizeof(int);
        clock_t start,end;
        start=clock();
        quicksort(A,0,A_length);
        end=clock();
        printf("time=%f\n",(double)(end-start)/CLK_TCK);
    #endif
    return 0;
}
