#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define maxn 1000
#define REDIRECT//输入输出重定向
// #define TCA//时间复杂度分析
int A[maxn];

void radix_sort(int* A,int d,int A_length)
{
    for(int k=1;k<=d;k++){//d是位数
        for(int j=1;j<A_length;j++)//每一轮选择插入排序
        {
            int key=A[j];
            int i=j-1;
            while(i>=0 && (A[i]%int(pow(10,k)) > key%int(pow(10,k))) ){
                A[i+1]=A[i];
                i--;
            }
            A[i+1]=key;
        }
    }
}

int main()
{
    #ifdef REDIRECT
        freopen("./radix_sort_input.txt","r",stdin);
        freopen("./radix_sort_output.txt","w",stdout);
        int x;
        while(scanf("%d",&x)!=EOF){
            int i=1;
            A[0]=x;
            int A_length=0;
            while(scanf("%d",&x) && x!=-1){
                A[i++]=x;
                A_length++;
            }
            int d;
            scanf("%d",&d);//位数
            radix_sort(A,d,A_length);
            for(int i=0;i<A_length;i++)
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
        radix_sort(A,6,A_length);
        end=clock();
        printf("time=%f\n",(double)(end-start)/CLK_TCK);
    #endif
    return 0;
}
