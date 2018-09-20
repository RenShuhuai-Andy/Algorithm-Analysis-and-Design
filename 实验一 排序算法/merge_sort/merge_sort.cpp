#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define maxn 10000
#define REDIRECT//输入输出重定向
// #define TCA//时间复杂度分析
int A[maxn];
int L[maxn];
int R[maxn];
//n=r-p+1:待合并元素的总数
void merge(int* A,int p,int q,int r)
{
    int n1=q-p+1;//左半数组的长度(包括A[q])
    int n2=r-q;//右半数组的长度(不包括A[q])
    // memset(L,0,sizeof(L));
    // memset(R,0,sizeof(R));
    for(int i=0;i<n1;i++)
        L[i]=A[p+i];
    for(int j=0;j<n2;j++)
        R[j]=A[q+j+1];
    L[n1]=300000;//在L和R后设置哨兵
    R[n2]=300000;
    int i=0,j=0;
    for(int k=p;k<=r;k++)
        if(L[i]<=R[j]){
            A[k]=L[i];
            i++;
        }
        else{
            A[k]=R[j];
            j++;
        }
}

void merge_sort(int*A,int p,int r)
{
    if(p<r){
        int q=(p+r)/2;
        merge_sort(A,p,q);
        merge_sort(A,q+1,r);
        merge(A,p,q,r);
    }
} 

int main()
{
    #ifdef REDIRECT
        freopen("./merge_sort_input.txt","r",stdin);
        freopen("./merge_sort_output.txt","w",stdout);
        int p,r;
        while(scanf("%d%d",&p,&r)!=EOF){
            int x;
            int i=0;
            while(scanf("%d",&x)){
                if(x!=-1)
                    A[i++]=x;
                else
                    break;
            }
            merge_sort(A,p,r);
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
        merge_sort(A,0,A_length);
        end=clock();
        printf("time=%f\n",(double)(end-start)/CLK_TCK);
    #endif
    return 0;
}
