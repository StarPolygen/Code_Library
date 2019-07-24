#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=2550;
const ll INF= (1LL<<62)-1;

int n,k,x,no,en[maxn],pos[maxn],num[maxn];
double s[maxn],p[maxn],dp[maxn][maxn],val[maxn];
vector<int> G[maxn];


void dfs(int u){
    num[u]=++no;   //num 记录点对应的dfs序
    pos[no]=u;     //pos 记录dfs序对应的点
    int len=G[u].size();
    for(int i=0;i<len;i++){
        int v = G[u][i];
        dfs(v);
    }
    en[u]=no;   //子树中dfs序最大者
}


int judge(double x){
    for(int i=1;i<=n;i++){
        val[i]=p[i]-x*s[i];
    }
    for(int i=0;i<=n+1;i++){ //编号是0~n+1 其中0是主席 1~n是雇员
        for(int j=0;j<=k;j++){
            dp[i][j]=-INF;
        }
    }
    //初始化基础状态
    dp[1][0]=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=k;j++){
            if(dp[i][j] <= -INF) continue;
            if(j<k) dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j] + val[pos[i]]);
            dp[en[pos[i]]+1][j]=max(dp[en[pos[i]]+1][j],dp[i][j]);
        }
    }
    return (dp[n+1][k]>0);
}

int main() {
    scanf("%d %d",&k,&n);
    for(int i=1;i<=n;i++){
        scanf("%lf %lf %d",&s[i],&p[i],&x);
        G[x].push_back(i);
    }
    no=0;
    for(int i=1;i<=n;i++){  //求得dfs序
        if(!num[i]) dfs(i);
    }
    double L=0,R=10200,mid; //二分：01分数规划
    for(int i=1;i<50;i++){
        mid=L+(R-L)/2.0;
        if(judge(mid)) L=mid;
        else R=mid;
    }
    printf("%.3lf",mid);
    return 0;
}