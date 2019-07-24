//Dijstra
//各点之间若干路，以及1号点（起点）到各点之间有一些铁路,注意有重边
//问删掉哪些铁路不会改变起点到其他点的最短路长度
//解法：Dij求出到所有点的最短路，及到该点的最短路入度inq[i]
      //对于所有铁路们，若到达点的最短路小于铁路长度，则显然可以删除它而不影响整个图的最短路
      //若到达点的最短路等于铁路长度，那么需要保留一条最短路即可，也就是说只要inq[i]>1那么就可以删除，同时inq[i]--
#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define ll long long
const ll INF = 1e17;
int n, m;

struct Edge
{
    int from, to, dist;
    Edge(int u, int v, int d) : from(u), to(v), dist(d) {}
};

struct HeapNode
{
    int d, u;
    bool operator<(const HeapNode &rhs) const
    {
       return d > rhs.d;
   }
};
vector<Edge> edges;
vector<int> G[maxn];
bool done[maxn];
ll d[maxn];
ll inq[maxn];
struct Dijkstra
{
   void init()
    {
        for (int i = 0; i <= n; i++)
            G[i].clear();
        edges.clear();
        memset(inq, 0, sizeof(inq));
   }
    void AddEdge(int from, int to, int dist)
    {
        edges.push_back(Edge(from, to, dist));
        int mm = edges.size();
        G[from].push_back(mm - 1);
   }
    void dijkstra(int s)
    {
        priority_queue<HeapNode> q;
        for (int i = 0; i <= n; i++)
            d[i] = INF;
        d[s] = 0;
        memset(done, 0, sizeof(done));
        q.push((HeapNode){0, s});
        while (!q.empty())
        {
            HeapNode x = q.top();
           q.pop();
            int u = x.u;
            if (done[u])
               continue;
            done[u] = 1;
           for (int i = 0; i < G[u].size(); i++)
            {
                Edge &e = edges[G[u][i]];
                if (d[e.to] == d[u] + e.dist)
                    inq[e.to]++;
                if (d[e.to] > d[u] + e.dist)
                {
                    d[e.to] = d[u] + e.dist;
                    inq[e.to] = 1;
                    q.push((HeapNode){d[e.to], e.to});
               }
           }
       }
    }
};

struct train
{
    int v;
    ll dist;
} t[maxn];

int main()
{

   int k; int  T;
    scanf("%d%d%d", &n, &m, &k);
    Dijkstra dij;
    dij.init();
    for (int i = 0; i < m; i++)
    {
        int u, v, di;
        scanf("%d%d%d", &u, &v, &di);
        dij.AddEdge(u, v, di);
        dij.AddEdge(v, u, di);
   }
    for (int i = 0; i < k; i++)
    {
        scanf("%d%lld", &t[i].v, &t[i].dist);
        dij.AddEdge(1, t[i].v, t[i].dist);
   }
    dij.dijkstra(1);
    ll ans = 0;
    for (int i = 0; i < k; i++)
    {
        if (t[i].dist == d[t[i].v])
            if (inq[t[i].v] > 1)
            {
                ans++;
                inq[t[i].v]--;
           }
        if (t[i].dist > d[t[i].v])
            ans++;
   }
    printf("%lld\n", ans);
    return 0;
}
