#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define REDIRECT//输入输出重定向
// #define TCA//时间复杂度分析
#define maxn 60000
int A[maxn];

void insertion_sort(int* A, int A_length)
{
    for(int j=1;j<A_length;j++){
        int key=A[j];
        int i=j-1;
        while(i>=0 && A[i]>key){
            A[i+1]=A[i];
            i--;
        }
        A[i+1]=key;
    }
    #ifdef REDIRECT
        for(int i=0;i<A_length;i++)
            printf("%d ",A[i]);
        printf("\n");
    #endif
}

int main()
{
    #ifdef REDIRECT
        freopen("./insertion_sort_input.txt", "r", stdin);
        freopen("./insertion_sort_output.txt", "w", stdout);
        int A_length;
        while(scanf("%d",&A_length)!=EOF){
            int x;
            int i=0;
            while(scanf("%d",&x)){
                if(x!=-1)
                    A[i++]=x;
                else
                    break;
            }
            insertion_sort(A,A_length);
        }
    #endif

    #ifdef TCA
        srand((unsigned)time(NULL));
        for(int i=0;i<maxn;i++)
            A[i]=rand()%maxn+1;
        int A_length=sizeof(A)/sizeof(int);
        clock_t start,end;
        start=clock();
        insertion_sort(A,A_length);
        end=clock();
        printf("time=%f\n",(double)(end-start)/CLK_TCK);
    #endif
    return 0;
}
