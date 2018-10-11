#include <stdio.h>
#define maxi 2
#define maxj 5
int f[maxi][maxj]={0};//代表子问题最优解的值
int l[maxi][maxj]={0};//装配线的编号
int e[2]={2,4};
int x[2]={3,6};
int a[maxi][maxj]={{7,9,3,4,8},{8,5,6,4,5}};
int t[maxi][maxj-1]={{2,3,1,3},{2,1,2,2}};
int f_final,l_final;//分别代表最终的代价和最终选择的线路

void fast_way(){
    f[0][0]=e[0]+a[0][0];
    f[1][0]=e[1]+a[1][0];
    for(int j=1;j<maxj;j++){
        if(f[0][j-1]+a[0][j] <= f[1][j-1]+t[1][j-1]+a[0][j]){
            f[0][j]=f[0][j-1]+a[0][j];
            l[0][j]=1;//注意没有定义l[0][0]
        }
        else{
            f[0][j]=f[1][j-1]+t[1][j-1]+a[0][j];
            l[0][j]=2;
        }

        if(f[1][j-1]+a[1][j] <= f[0][j-1]+t[0][j-1]+a[1][j]){
            f[1][j]=f[1][j-1]+a[1][j];
            l[1][j]=2;
        }
        else{
            f[1][j]=f[0][j-1]+t[0][j-1]+a[1][j];
            l[1][j]=1;
        }
    }
    if(f[0][maxj-1]+x[0] <= f[1][maxj-1]+x[1]){
        f_final=f[0][maxj-1]+x[0];
        l_final=1;
    }
    else{
        f_final=f[1][maxj-1]+x[1];
        l_final=2;
    }
}

void print_stations(){
    printf("line %d, station %d\n", l_final,maxj);
    for(int j=maxj-1;j>0;j--)
        printf("line %d, station %d\n", l[l_final-1][j], j);//注意l_final-1
    printf("time cost: %d",f_final);
}

int main(){
    fast_way();
    print_stations();
    return 0;
}