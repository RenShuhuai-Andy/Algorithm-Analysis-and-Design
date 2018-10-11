#include <stdio.h>
#include <string.h>
#define maxm 16
#define maxn 16
char X[maxm] = { 'A','C','C','G','G','T','C','G','A','G','A','T','G','C','A','G' };
char Y[maxn] = { 'G','T','C','G','T','T','C','G','G','A','A','T','G','C','A','T' };
//#define maxm 7
//#define maxn 6
//char X[maxm] = { 'A','B','C','B','D','A','B' };
//char Y[maxn] = { 'B','D','C','A','B','A' };
int c[maxm+1][maxn+1]={0};
char b[maxm+1][maxn+1]={0};
int len=0;

void LCS_length(char X[],char Y[]){
    for(int i=1;i<=maxm;i++){
        for(int j=1;j<=maxn;j++){
            if(X[i-1]==Y[j-1]){
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]='t';//tilted
            }
            else if(c[i-1][j] >= c[i][j-1]){
                c[i][j]=c[i-1][j];
                b[i][j]='u';//upper
            }
            else{
                c[i][j]=c[i][j-1];
                b[i][j]='l';//left
            }
        }
    }
}

void print_LCS(int i,int j){
    if(i==0 || j==0)
        return;
    if(b[i][j]=='t'){
        print_LCS(i-1,j-1);
        printf("%c",X[i-1]);
        len++;
    }
    else if(b[i][j]=='u')
        print_LCS(i-1,j);
    else    
        print_LCS(i,j-1);
}

int main(){
    // freopen("./LCS_problem_input.txt","r",stdin);
    // for(int i=0;i<maxm;i++)
    //     scanf("%c",&X[i]);
    // getchar();
    // for(int i=0;i<maxn;i++)
    //     scanf("%c",&Y[i]);
    LCS_length(X,Y);
    print_LCS(maxm,maxn);
    printf("\nlength: %d\n",len);
    return 0;
}
