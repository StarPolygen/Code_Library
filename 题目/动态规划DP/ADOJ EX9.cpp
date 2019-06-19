#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define maxn 1010
#define INF 1e11

ll N,M;
ll arr[maxn][maxn];
ll dp[maxn][maxn];
ll big[maxn][maxn];

void init(){
    memset(arr,0,sizeof(arr));
    memset(dp,0,sizeof(dp));
    memset(big,0,sizeof(big));
    for(int i=0;i<maxn;i++){
        for(int j=0;j<maxn;j++){
            if(j<i) big[i][j]=-INF;
        }
    }
   
}
int main() {
    init();
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++)
    scanf("%lld%lld",&N,&M);{
            scanf("%lld",&arr[i][j]);
        }
    }

    for(int i=1;i<=N;i++){
        for(int j=i;j<=M;j++){
            dp[i][j]=max(big[i-1][j-1]+arr[i][j],dp[i-1][j]);
            big[i][j]=max(big[i-1][j-1]+arr[i][j],big[i][j-1]);
        }
    }


    printf("%lld\n",big[N][M]);
    return 0;
}