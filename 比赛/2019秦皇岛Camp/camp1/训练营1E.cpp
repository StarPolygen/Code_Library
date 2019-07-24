#include<bits/stdc++.h>
#define ll long long
#define maxn 4000100
using namespace std;

char mus[1010][1010];
int cnt[1010][1010];
int arr[maxn];
int father[maxn];
int find(int x);
void unite(int x,int y);
void ini();

int find(int x){
    if(x==father[x]) return x;
    return father[x] = find(father[x]);
}
void unite(int x,int y){
    int l=find(x);
    int r=find(y);
    father[r] = l;
}
void ini(){
	for (int i = 0; i < maxn;i++){
            father[i] = i;
    }
}
int main() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    memset(mus,0,sizeof(mus));
    memset(cnt,0,sizeof(cnt));
    memset(arr,0,sizeof(arr));
    ini();
    
    for(int i=1;i<=n;i++){
        scanf("%s",mus[i]+1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mus[i][j]=='*'){
                if(mus[i-1][j]=='.') cnt[i-1][j]++;
                if(mus[i][j-1]=='.') cnt[i][j-1]++;
                if(mus[i+1][j]=='.') cnt[i+1][j]++;
                if(mus[i][j+1]=='.') cnt[i][j+1]++;
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         printf("%d ",cnt[i][j]);
    //     }
    //     printf("\n");
    // }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(mus[i][j]=='.'){
                if(mus[i][j+1]=='.') unite((i-1)*m+j,(i-1)*m+j+1);
                if(mus[i+1][j]=='.') unite((i-1)*m+j,(i)*m+j);
                if(mus[i-1][j]=='.') unite((i-2)*m+j,(i-1)*m+j);
                if(mus[i][j-1]=='.') unite((i-1)*m+j,(i-1)*m+j-1);
            }
        }
    }
    for(int i=1;i<=n*m;i++){
        int row=i%m==0?(i/m):(i/m)+1;
        int lie=i%m==0?m:(i%m);
        arr[find(i)]+=cnt[row][lie];
        // printf("%d ",find(i));
        // if(i%m==0) printf("\n");
    }
    // for(int i=1;i<=n*m;i++){
    //     int row=i%m==0?(i/m):(i/m)+1;
    //     int lie=i%m==0?m:(i%m);
    //     printf("%d ",arr[i]);
    //     if(i%m==0) printf("\n");
    // }
    for(int i=1;i<=k;i++){
        int ax,bx;
        scanf("%d%d",&ax,&bx);
        printf("%d\n",arr[find((ax-1)*m+bx)]);
    }


    return 0;
}
/*
5 6 3
******
*..*.*
******
*....*
******
1 2 3 4 5 6
7 8 9 10 11 12
13 14 14 16 17 18
19 20 21 22 23 24
25 26 26 26 26 30
0 0 0 0 0 0
0 3 3 0 4 0
0 0 0 0 0 0
0 3 2 2 3 0
0 0 0 0 0 0
2 2
0
2 5
0
4 3
*/