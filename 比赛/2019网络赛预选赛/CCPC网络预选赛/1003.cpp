//SAM
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define sc second
#define pb push_back
#define mp make_pair
#define LEN(X) strlen(X)
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, N) for (int I = 0; I < (N); ++I)
#define FORD(I, N) for (int I = N; ~I; --I)
#define REP(I, A, B) for (int I = A; I <= (B); ++I)
#define REPD(I, B, A) for (int I = B; I >= A; --I)
#define FORS(I, S) for (int I = 0; S[I]; ++I)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int n, q;

struct Q{
    int p, l, r, k;
    Q(){}
    Q(int p, int l, int r, int k) : p(p), l(l), r(r), k(k){}
};

vector<Q> qu[N];

int fn[N];

int cnt, he[N], ne[N], v[N];

void add(int x,int y){
    cnt++;
    ne[cnt] = he[x];
    v[cnt] = y;
    he[x] = cnt;
}

int tree[N << 2];

int ans[N];

void update(int x,int l,int r,int p,int v){
    if (l==r){
        tree[x] += v;
        tree[x] = min(tree[x], 1);
        return;
    }
    int mid = l + r >> 1;
    if (p<=mid) update(x << 1, l, mid, p, v);
    else update(x << 1 | 1, mid + 1, r, p, v);
    tree[x] = tree[x << 1] + tree[x << 1 | 1];
}
int query(int x,int l,int r,int k){
    if (l==r){
        return l;
    }
    int mid = l + r >> 1;
    if (k <= tree[x << 1]) return query(x << 1, l, mid, k);
    else return query(x << 1 | 1, mid + 1, r, k - tree[x << 1]);
}


struct SAM
{
    int nxt[N][27], fa[N], len[N];
    int sz[N];
    int root, tot, last;
    int endpos[N];
    bool T;//T=1位置不同的相同子串算多个;T=0本质相同的子串只算一次
    int newnode(int l)
    {
        ++tot;
        fa[tot] = -1;
        for (int i = 0; i < 27; ++i)
            nxt[tot][i] = -1;
        len[tot] = l;
        return tot;
    }
    void init()
    {
        memset(endpos, 0, sizeof(endpos));
        dfn = 0;
        tot = -1;
        last = root = newnode(0);
    }
    void extend(int x,int pos)
    {
        int p = last;
        int cur = newnode(len[p] + 1);
        sz[cur] = 1;
        endpos[cur] = pos;
        fn[pos] = cur;
        while (p != -1 && nxt[p][x] == -1)
        {
            nxt[p][x] = cur;
            p = fa[p];
        }
        if (p == -1)
            fa[cur] = root;
        else
        {
            int q = nxt[p][x];
            if (len[q] == len[p] + 1)
                fa[cur] = q;
            else
            {
                int tmp = newnode(len[p] + 1);
                memcpy(nxt[tmp], nxt[q], sizeof(nxt[q]));
                fa[tmp] = fa[q];
                fa[q] = fa[cur] = tmp;
                while (p != -1 && nxt[p][x] == q)
                {
                    nxt[p][x] = tmp;
                    p = fa[p];
                }
            }
        }
        last = cur;
    }
    int dfs_in[N], dfs_out[N], dfn, id[N];
    int son[N];
    int hev[N];
    void dfs1(int x){
        id[dfs_in[x] = ++dfn] = x;
        hev[x] = 1;
        son[x] = 0;
        int mx = 0;
        for (int i = he[x]; i;i=ne[i])
        {
            int p = v[i];
            dfs1(p);
            if (mx<hev[p]){
                son[x] = p;
                mx = hev[p];
            }
            hev[x] += hev[p];
        }
        dfs_out[x] = dfn;
    }
    void dfs2(int x){
        for (int i = he[x]; i; i = ne[i])
        {
            int p = v[i];
            if (p==son[x]) continue;
            dfs2(p);
            for (int i = dfs_in[p]; i <= dfs_out[p];i++)
            {
                int t = id[i];
                if (endpos[t]) update(1, 1, n, endpos[t], -1);
            }
        }
        if (son[x])
            dfs2(son[x]);
        for (int i = he[x]; i;i=ne[i])
        {
            int p = v[i];
            if (p==son[x]) continue;
            for (int i = dfs_in[p];i<=dfs_out[p];i++)
            {
                int t = id[i];
                if (endpos[t]) update(1, 1, n, endpos[t], 1);
            }
        }
        if (endpos[x])
            update(1, 1, n, endpos[x], 1);
        for (auto q: qu[x])
        {
            ans[q.p] = tree[1] >= q.k ? query(1, 1, n, q.k) - (q.r - q.l) : -1;
        }
    }
    void work(){
        REP(i,1,q){
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            int x = fn[r];
            while (len[fa[x]] >= (r - l + 1)){
                x = fa[x];
            }
            qu[x].pb(Q(i, l, r, k));
        }

        for (register int i = 1; i <= tot;++i)
        {
            add(fa[i], i);
        }
        dfs1(0);
        dfs2(0);
    }

} sam;

char s[N];

inline void init(){
    sam.init();
    scanf(" %s", s + 1);
    for (register int i = 1; i <= n;++i)
    {
        sam.extend(s[i] - 'a', i);
    }
    for (register int i = 0; i <= sam.tot;++i)
    {
        qu[i].clear();
    }
    memset(tree, 0, sizeof(tree));
    cnt = 0;
    memset(he, 0, sizeof(he));
}

int main(){
    // clock_t st = clock();
    int _;
    for (scanf("%d", &_); _;--_)
    {
        scanf("%d%d", &n, &q);
        init();
        sam.work();
        REP(i,1,q){
            printf("%d\n", ans[i]);
        }
    }
    // clock_t et = clock();
    // cout << (double)(et - st) / CLOCKS_PER_SEC << endl;
    return 0;
}