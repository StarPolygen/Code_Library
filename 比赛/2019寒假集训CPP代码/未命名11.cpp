#include <bits/stdc++.h>
#define maxn 1005
#define inf 1e9+7
using namespace std;
int mp[maxn][maxn];
int dis[maxn];
int pre[maxn];
void init(){
    int i, j;
    for (i = 1; i < maxn; ++i) {
        for (j = 1; j < maxn; ++j) {
            if (i == j) {
                mp[i][j] = 0;
            }
            else {
                mp[i][j] = inf;
            }
        }
    }
}
void dijkstra(int n,int v)
{
    bool vis[maxn];
    for(int i=1;i<=n;i++)
    {
        vis[i]=false;
        dis[i]=mp[v][i];
        if(dis[i]==inf)
        {
            pre[i]=0;
        }
        else pre[i]=v;
    }
    dis[v]=0;
    vis[v]=true;
    for(int i=2;i<=n;i++)
    {
            int u=v;
            int mazz=inf;
            for(int j=1;j<=n;j++){
        if(!vis[j]&&dis[j]<mazz)
        {
                u=j;
                mazz=dis[j];
        }
        }
        vis[u]=true;
        for(int k=1;k<=n;k++)
        {
            if(!vis[k]&&mp[u][k]<inf)
            {
                if(dis[k]>mp[u][k]+dis[u]){
                    dis[k]=mp[u][k]+dis[u];
                    pre[k]=u;
                }
            }
        }

    }
}
int main()
{
    int T,x,y,k,n;
    int num[maxn][12];
    char s[25];
    scanf("%d",&T);
    while(T--)
    {
        init();
        for(int i=0;i<maxn;i++){
        	for(int j=0;j<12;j++){
        		num[i][j]=0;
			}
		}
        scanf("%d%d%d",&n,&x,&y);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",&s);
            for(int k=0;k<20;k++)
        	num[i][s[k]-'0']++;
        }
        for(int i=1;i<n;i++)
            for(int j=i+1;j<=n;j++)
        {
            int com=0;
            for(int k=0;k<=9;k++)
            {
                com+=min(num[i][k],num[j][k]);
            }
            if(com==17)
            {
                mp[i][j] = 1;
                mp[j][i] = 1;
            }
        }
        dijkstra(n,x);
        if(dis[y]==inf)
           printf("-1\n");
        else
            printf("%d\n",dis[y]);
    }
}
