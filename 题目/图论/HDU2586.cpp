//DFS 暴力最短路求解
//另外存在解法：Tarjan LCA
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define maxn 40010
using namespace std;

struct edge
{
    int t;
    int dis;
} temp;
vector<edge> map[maxn]; 
int vis[maxn];
int flag;
int n;
int e; 

void dfs(int t, int dis)
{
    if (map[t].empty()) 
        return;
    if (t == e)
    {
        flag = 1; 
        printf("%d\n",dis);
    }

    int size = map[t].size();
    for (int j = 0; j < size; j++)
    {
        if (!vis[map[t][j].t])
        {
            vis[map[t][j].t] = 1;
            dfs(map[t][j].t, dis + map[t][j].dis);
            if (flag)
                return;
            vis[map[t][j].t] = 0;
        }
    }
}

int main()
{
    int t;
    int m;
    int s;
    int x, y, z;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n - 1; i++)
        {
            scanf("%d %d %d", &x, &y, &z);
            temp.t = y;
            temp.dis = z;
            map[x].push_back(temp);
            temp.t = x;
            temp.dis = z;
            map[y].push_back(temp);
        }

        for (int i = 1; i <= m; i++)
        {
            memset(vis, 0, sizeof(vis));
            flag = 0;
            scanf("%d %d", &s, &e);
            vis[s] = 1;
            dfs(s, 0);
        }

        for (int i = 0; i < n; i++)
        {
            map[i].clear();
        }
    }
    return 0;
}