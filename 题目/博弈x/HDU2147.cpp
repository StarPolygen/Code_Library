//博弈  手动推NP或打表DP
//1 2 1 2 1 2
//2 2 2 2 2 2
//1 2 1 2 1 2
//2 2 2 2 2 2
#include<bits/stdc++.h>
#define ll long long
using namespace std;

char arr[2010][2010];
int main() {
    int n,m;
    //1代表P必败态 向各方向拓展为2   2代表N必胜态 向回查找若都为2 则该点为1
    memset(arr,0,sizeof(arr));
    arr[0][0]='1';
    for(int i=0;i<=2001;i++){
        for(int j=0;j<=2001;j++){
            if(arr[i][j]=='1') {
                arr[i+1][j]=arr[i][j+1]=arr[i+1][j+1]='2';
            }else if(arr[i][j]==0){
                int bools=1;
                if(i-1>=0&&arr[i-1][j]!='2') bools=-1;
                if(j-1>=0&&arr[i][j-1]!='2') bools=-1;
                if(j-1>=0&&i-1>=0&&arr[i-1][j-1]!='2') bools=-1;
                if(bools==1) arr[i][j]='1'; 
                int boolt=-1;
                if(i-1>=0&&arr[i-1][j]=='1') boolt=1;
                if(j-1>=0&&arr[i][j-1]=='1') boolt=1;
                if(j-1>=0&&i-1>=0&&arr[i-1][j-1]=='1') boolt=1;
                if(boolt==1) arr[i][j]='2'; 
            }
        }
    }
    // for(int i=0;i<=100;i++){
    //     for(int j=0;j<=100;j++){
    //         printf("%d ",arr[i][j]);
    //     }
    //     printf("\n");
    // }
    while(true){
        scanf("%d%d",&n,&m);
        if(n==0 && m==0) break;
        if(arr[n-1][m-1]=='1') printf("What a pity!\n");
        else printf("Wonderful!\n");
    }

    return 0;
}