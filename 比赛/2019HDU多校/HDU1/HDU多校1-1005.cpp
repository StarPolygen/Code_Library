//最短路 +网络流 
//删掉一些边，阻止或延长从1到n的路程，求被删掉边的最小权值和
//预处理出所有最短路，用最短路建图，最小割即可阻断所有最短路 
//由于最短路如果存在焦点，则交点两侧的边长必定也相等。还是一条最短路,因此必须全切掉至不连通，也就是最小割。
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
#include <queue>
#define ll long long
#define int long long
namespace Dinic{
    using namespace std;
    const int maxn=200005;
    const int maxm=300000;
    const long long INF=1E18;
    int n,m;
    int st,en;
    
    struct Edge{
        int next;
        int to;
        long long val;
    } e[maxm*2];
    int head[maxn];
    int cur[maxn];
    long long dis[maxn];
    int tot;
    
    long long dfs(int u,long long flow) {
        if (u==en) {return flow;}
        for (int &i=cur[u];i!=-1;i=e[i].next){
            if ((dis[e[i].to] == dis[u]+1) && (e[i].val!=0)) {
                long long di=dfs(e[i].to, min(flow, e[i].val));
                if (di>0) {
                    e[i].val-=di;
                    e[i^1].val+=di;
                    return di;
                }
            }
        }
        return 0;
    }
    
    
    int bfs() {
        queue<int> Q;
        while (!Q.empty()) {Q.pop();}
        memset(dis,0,sizeof(dis));
        dis[st]=1;
        Q.push(st);
        do {
            int u=Q.front();
            Q.pop();
            for (int i=head[u];i!=-1;i=e[i].next) {
                if ((dis[e[i].to]==0) && (e[i].val>0)) {
                    dis[e[i].to] = dis[u] +1;
                    Q.push(e[i].to);
                }
            }
        } while (!Q.empty());
        if (dis[en]>0) {
            return 1;
        }
        return 0;
    }
    
     long long Dinic(){
        long long ans=0;
        while (bfs()) {
            for (int i=1;i<=n;i++) {
                cur[i]=head[i];
            }
            while (long long d=dfs(st, INF)) {
                ans+=d;
            }
        }
        return ans;
    }
    
    
    inline void addedge(int x,int y,int c) {
        e[tot].next=head[x];
        head[x]=tot;
        e[tot].val=c;
        e[tot].to=y;
        tot++;
        e[tot].next=head[y];
        head[y]=tot;
        e[tot].to=x;
        e[tot].val=0;
        tot++;
        return ;
    }
    
    
    inline void init(int x,int y) {
        n=x;
        m=y;
        tot=0;
        for (int i=0;i<=n;i++) {
            head[i]=-1;
        }
        st=1;
        en=n;
        return;
    }
}

using namespace std;
const int maxn=500000;
const long long INF=1E18;
struct Edge{
    int next;
    int from;
    int to;
    long long w;
} edge[maxn];
int head[maxn];
bool vis[maxn];
int tot;

struct Node{
    long long dis;
    int index;
    bool operator < (const Node &x) const {
        return dis>x.dis;
    }
} node[maxn];
priority_queue <Node> q;

long long f[maxn];
int n,m;


void init() {
    for (int i=1;i<=n;i++) {
        head[i]=0;
        node[i].index=i;
    }
    tot=0;
}
inline void addedge(int x, int y, int w) {
    edge[++tot].next=head[x];
    edge[tot].from=x;
    edge[tot].to=y;
    edge[tot].w=w;
    head[x]=tot;
}
void dijkstra(int x) {
    for (int i=1;i<=n;i++) {
        vis[i]=false;
        node[i].dis=INF;
    }
    while (!q.empty()) {
        q.pop();
    }
    node[x].dis=0;
    q.push(node[x]);
    while (!q.empty()) {
        Node top_node=q.top();
        int u=top_node.index;
        q.pop();
        if (vis[u]) {
            continue;
        }
        vis[u]=true;
        for (int p=head[u];p!=0;p=edge[p].next) {
            int v=edge[p].to;
            if (node[v].dis>node[u].dis+edge[p].w) {
                node[v].dis=node[u].dis+edge[p].w;
                q.push(node[v]);
            }
        }
    }
    for (int i=1;i<=n;i++) {
        f[i]=node[i].dis;
    }
}

long long weight[maxn];


long long Solve() {
    Dinic::init(n,m);
    for (int i=1;i<=n;i++) {
        weight[i]=0;
    }
    for (int i=1;i<=n;i++) {
        for (int p=head[i];p!=0;p=edge[p].next) {
            int u=edge[p].from;
            int v=edge[p].to;
            int w=edge[p].w;
            if (f[u]+w==f[v]) {
//                printf("::%d %d %lld\n", u,v,w);
                weight[v]+=w;
            }
        }
        for (int p=head[i];p!=0;p=edge[p].next) {
            int u=edge[p].from;
            int v=edge[p].to;
            if (weight[v]>0) {
//                printf("!!%d %d %lld\n", u,v,weight[v]);
                Dinic::addedge(u,v,weight[v]);
                weight[v]=0;
            }
        }
    }
    return Dinic::Dinic();
}

signed main() {
    int T;
    scanf("%lld", &T);
    while (T--) {
        scanf("%lld%lld", &n, &m);
        init();
        for (int i=1;i<=m;i++) {
            int x,y,z;
            scanf("%lld%lld%lld", &x,&y,&z);
            addedge(x,y,z);
        }
        dijkstra(1);
        
        
        long long ans=0;
        if (f[n]==INF) {
            ans=0;
        } else {
            ans=Solve();
        }
        
        printf("%lld\n", ans);
        
    }
    return 0;
}

/*
10
3 4
1 2 1
2 3 1
1 3 2
1 3 3     
5 6
1 2 1000000001
2 5 1000000007
1 3 1000000004
3 5 1000000004
1 4 1000000005
4 5 1000000003
3 4
1 2 1
2 3 1
1 3 2
1 3 3
9 10
1 2 2
1 3 4
2 4 5
3 4 3
4 5 8
5 8 3
5 6 2
6 7 5
8 7 4
7 9 10
9 9
1 2 2
1 3 4
2 4 5
3 4 3
5 8 3
5 6 2
6 7 5
8 7 4
7 9 10
9 11
1 2 2
1 2 2
1 3 4
2 4 5
3 4 3
4 5 8
5 8 3
5 6 3
6 7 5
8 7 5
7 9 10
*/