#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 100010

struct Edge{
    int to,next;
    ll w;
}edge[200020];
ll idex=0,remain=0;
const int MAXN=maxn;
int a[MAXN],head[MAXN];


void addedge(int u,int v, ll w)
{
    edge[idex].to=v;
    edge[idex].next=head[u];
    edge[idex].w=w;
    head[u]=idex++;
}

void dfs(int u,int pre, ll w)
{
    if (a[u]<w) return;
    remain++;
    for(int i=head[u]; i!=-1; i=edge[i].next)
    {
        int v=edge[i].to;
        if (v==pre) continue;
        dfs(v,u,max(0LL,w+edge[i].w));
    }
}

void init(){
    idex=0;
    memset(head,-1,sizeof(head));
}
int main()
{
    init();remain=0;
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)    scanf("%d",&a[i]);
    for(int i=2; i<=n; i++){
        int v;ll w;
        scanf("%d%lld",&v,&w);
        addedge(i,v,w);
        addedge(v,i,w);
    }
    dfs(1,1,0);
    printf("%d\n",n-remain);
    return 0;
}
