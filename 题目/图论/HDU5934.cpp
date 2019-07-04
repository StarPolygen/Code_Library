//练习Tarjan缩点模板:1.缩点   2.重建图
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>
#define maxn 1010
using namespace std;
const double eps = 1e-8;
const int inf = 0x3f3f3f3f;
int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }

//点和距离
struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y)
    {
        x = _x;y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x - b.x,y - b.y);
    }
    //点向量叉积 
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
};

double dis(Point a, Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}


//Tarjan缩点
int dfn[maxn],low[maxn],stack[maxn],vis[maxn],color[maxn],sum,deep,top;
vector<int> g[maxn];
int degree[maxn],cost[maxn],arr[maxn][4];
void Tarjan(int u){
    dfn[u]=++deep;  //首先初始化dfn[u]=low[u]=第几个被dfs到 
    low[u]=deep;
    vis[u]=1;
    stack[++top]=u;  //将u存入stack[]中，并将vis[u]设为true
    int sz=g[u].size();
    for(int i=0;i<sz;i++){
        int v=g[u][i];
        if(!dfn[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else{
            if(vis[v]){
                low[u]=min(low[u],low[v]);
            }
        }
    }
    if(dfn[u]==low[u]){
        color[u]=++sum;
        vis[u]=0;
        cost[sum]=min(cost[sum],arr[u][3]);
        while(stack[top]!=u){
            cost[sum]=min(cost[sum],arr[stack[top]][3]);
            color[stack[top]]=sum;
            vis[stack[top--]]=0;
        }
        top--;
    }
}

void init();
int main()
{
    int T,kcase=0;
    scanf("%d",&T);
    while(T--){
        init();
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
           scanf("%d %d %d %d",&arr[i][0],&arr[i][1],&arr[i][2],&arr[i][3]);
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j) continue;
                else{
                    if(sgn(dis(Point(arr[i][0],arr[i][1]),Point(arr[j][0],arr[j][1]))-arr[i][2])<=0){
                        g[i].push_back(j);
                    }
                }
            }
        }

        for(int i=1;i<=n;i++){
            if(!dfn[i]) Tarjan(i);
        }
        
        for(int i=1;i<=n;i++){
            int len=g[i].size();
            for(int j=0;j<len;j++){
                if(color[i]==color[g[i][j]]) continue;
                else degree[color[g[i][j]]]++;
            }
        }

        int ans=0;
        for(int i=1;i<=sum;i++){
            if(degree[i]==0) ans+=cost[i];
        }
        printf("Case #%d: %d\n",++kcase,ans);
    }
    return 0;
    
}

void init(){
    sum=deep=top=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(stack,0,sizeof(stack));
    memset(vis,0,sizeof(vis));
    memset(color,0,sizeof(color));
    for(int i=0;i<maxn;i++){
        g[i].clear();
    }
    memset(degree,0,sizeof(degree));
    memset(arr,0,sizeof(arr));
    for(int i=0;i<maxn;i++){
        cost[i]=inf;
    }
}