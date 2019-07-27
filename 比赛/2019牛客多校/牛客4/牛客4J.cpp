// 作者：朱
//可以选k条路免费后的最短路
//k层spfa
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define sc second
#define fi first
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
const int N = 1e3 + 5;
priority_queue<pi, vector<pi>, greater<pi> > q;
int cnt, he[N], ne[N * 2], w[N * 2], v[N * 2];
int d[N][N];
bool vis[N][N];
int n, m, k;
void add(int x,int y,int z){
    if (x==y)
        return;
    for (int i = he[x]; i;i=ne[i])
    {
        int p = v[i];
        if (p==y){
            w[i] = min(w[i], z);
            return;
        }
    }
    cnt++;
    ne[cnt] = he[x];
    v[cnt] = y;
    w[cnt] = z;
    he[x] = cnt;
}
void spfa(int s){
    queue<pi> q;
    memset(d, -1, sizeof(d));
    memset(vis, 0, sizeof(vis));
 
    q.push(mp(s, 0));
    d[s][0] = 0;
    vis[s][0] = 1;
    while (!q.empty()){
        pi j = q.front();
        q.pop();
        int x = j.fi;
        int t = j.sc;
        for (int i = he[x]; i; i = ne[i])
        {
            int p = v[i];
            for (int offset = 0; offset < 2;offset++)
            {
                int nt = t + offset;
                if (nt>k) continue;
                if (d[p][nt] == -1 || d[p][nt] > d[x][t] + (offset == 1 ? 0 : w[i])){
                    d[p][nt] = d[x][t] + (offset == 1 ? 0 : w[i]);
                    if (!vis[p][nt]){
                        q.push(mp(p, nt));
                        vis[p][nt] = 1;
                    }
                }
            }
        }
 
        vis[x][j.sc] = 0;
    }
}
int main(){
    int s, t;
    scanf("%d%d%d%d%d", &n, &m, &s, &t, &k);
    for (int i = 1; i <= m;i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
    }
    spfa(s);
    int ans = -1;
    for (int i = 0; i <= k;i++)
    {
        if (~d[t][i])
            ans = ans == -1 ? d[t][i] : min(ans, d[t][i]);
    }
    printf("%d\n", (s == t ? 0 : ans));
    return 0;
}