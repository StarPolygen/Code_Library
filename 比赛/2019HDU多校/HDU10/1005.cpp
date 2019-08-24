//线段树
// #pragma GCC optimize(3)
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
const int N = 2e5 + 5;
const ll R = 1e18;
const int MOD = 1e9 + 7;

pl a[N];
vector<ll> b, B;
ll smx[N];
int n;

int tree[N << 2], mn[N << 2], mx[N << 2];

inline int has(ll x){
    return lower_bound(ALL(b), x) - b.begin() + 1;
}

inline void init(){
    memset(tree, 0, sizeof(tree));
    memset(mn, 0, sizeof(mn));
    memset(mx, 0, sizeof(mx));
    memset(smx, -1, sizeof(smx));
    b.clear();
    B.clear();
}

void update(int x,int l,int r,int p,int v)
{
    if (l==r){
        tree[x] += v;
        mx[x] = mn[x] = l;
        return;
    }
    int mid = l + r >> 1;
    if (p<=mid)
        update(x << 1, l, mid, p, v);
    else
        update(x << 1 | 1, mid + 1, r, p, v);
    tree[x] = tree[x << 1] + tree[x << 1 | 1];
    mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
    mn[x] = r;
    if (tree[x << 1])
        mn[x] = min(mn[x], mn[x << 1]);
    if (tree[x << 1 | 1])
        mn[x] = min(mn[x], mn[x << 1 | 1]);
}

int query(int x,int l,int r,int p){
    if (l==r) return l;

    int mid = l + r >> 1;
    int lc = x << 1;
    int rc = x << 1 | 1;

    ll le = (tree[x << 1] ? min(abs(b[mn[lc] - 1] - b[p - 1]), abs(b[mx[lc] - 1] - b[p - 1])) : R);
    ll re = (tree[x << 1 | 1] ? min(abs(b[mn[rc] - 1] - b[p - 1]), abs(b[mx[rc] - 1] - b[p - 1])) : R);

    if (tree[x << 1] && le <= re)
        return query(x << 1, l, mid, p);
    else
        return query(x << 1 | 1, mid + 1, r, p);

}

inline ll getnum(){
    char ch;
    ll s = 0;
    while ((ch=getchar())=='\n'|| ch=='\r'|| ch==' ')
        ;
    while (ch<='9' && ch>='0') {
        s = s * 10 + 1ll * (ch - '0');
        ch = getchar();
    }
    return s;
}

int main(){
    // clock_t st = clock();
    int _;
    for (scanf("%d", &_); _;--_)
    {
        n = getnum();
        init();
        REP(i,1,n){
            a[i].sc = getnum();
            a[i].fi = getnum();
            b.pb(a[i].sc);
            b.pb(a[i].fi);
            B.pb(a[i].fi);
        }
        sort(ALL(b));
        sort(ALL(B));
        B.erase(unique(ALL(B)), B.end());
        b.erase(unique(ALL(b)), b.end());
        int len = b.size();

        sort(a + 1, a + 1 + n);

        for (register int i = n; i >= 1;--i)
        {
            smx[i] = max(smx[i + 1], a[i].sc);
        }
        ll fin = R;
        int now = 1;
        int BL = B.size();
        for (register int i = 0; i < BL; ++i)
        {
            int tot = 0, ans1, ans2;

            ll tmp1 = -1, tmp2 = -1;

            if (tree[1]){
                ans1 = query(1, 1, len, has(B[i]));
                tmp1 = b[ans1 - 1];
            }

            while (now <= n && a[now].fi <= B[i]){
                update(1, 1, len, has(a[now++].sc), 1);
                ++tot;
            }
            if (tot>1){
                ans2 = query(1, 1, len, has(B[i]));
                tmp2 = b[ans2 - 1];
            }

            tmp1 = max(smx[now], tmp1);
            if (~tmp2) tmp2 = max(smx[now], tmp2);

            if (~tmp1) {
                fin = min(fin, abs(tmp1 - B[i]));
                if (~smx[now]) fin = min(fin, abs(smx[now] - B[i]));
            }
            if (~tmp2) {
                fin = min(fin, abs(tmp2 - B[i]));
                if (~smx[now]) fin = min(fin, abs(smx[now] - B[i]));
            }
        }
        printf("%lld\n", fin);
    }
    // clock_t et = clock();
    // cout << (double)(et - st) / CLOCKS_PER_SEC << endl;
    return 0;
}