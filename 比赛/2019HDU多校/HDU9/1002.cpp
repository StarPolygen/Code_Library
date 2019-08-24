//欧拉定理 线段树扫描线
// #pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define sc second
#define pb push_back
#define mp make_pair
#define LEN(X) strlen(X)
#define SZ(X) ((ll)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, N) for (ll I = 0; I < (N); ++I)
#define FORD(I, N) for (ll I = N; ~I; --I)
#define REP(I, A, B) for (ll I = A; I <= (B); ++I)
#define REPD(I, B, A) for (ll I = B; I >= A; --I)
#define FORS(I, S) for (ll I = 0; S[I]; ++I)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

struct LINE{
    ll x, y;
    bool l;
    LINE(ll x, ll y, bool l) : x(x), y(y), l(l){}
    LINE(){}
    bool operator < (const LINE & b) const {
        return y < b.y;
    }
} line[N];

vector<pl> U, D;
vector<ll> b;

ll tree[N << 2];
int tot;

void init(){
    memset(tree, 0, sizeof(tree));
    b.clear();
    U.clear();
    D.clear();
    tot = 0;
}

int has(ll x){
    return lower_bound(ALL(b), x) - b.begin() + 1;
}

void update(int x,int l,int r,int p,ll v){
    if (l==r){
        tree[x] += v;
        return;
    }
    int mid = l + r >> 1;
    if (p<=mid)
        update(2 * x, l, mid, p, v);
    else
        update(2 * x + 1, mid + 1, r, p, v);
    tree[x] = tree[2 * x] + tree[2 * x + 1];
}

ll queryL(int x,int l,int r,int p){
    if (l==r){
        return tree[x];
    }
    int mid = l + r >> 1;
    if (p<=mid)
        return queryL(2 * x, l, mid, p);
    else
        return tree[2 * x] + queryL(2 * x + 1, mid + 1, r, p);
}

ll queryR(int x,int l,int r,int p){
    if (l==r){
        return tree[x];
    }
    int mid = l + r >> 1;
    if (p<=mid)
        return queryR(2 * x, l, mid, p) + tree[2 * x + 1];
    else
        return queryR(2 * x + 1, mid + 1, r, p);
}

int main(){
    int _, n, m, k;
    for (scanf("%d", &_); _;_--)
    {
        init();
        scanf("%d%d%d", &n, &m, &k);
        FOR(i,k){
            ll x, y;
            char ch;
            scanf("%lld %lld %c", &x, &y, &ch);
            if (ch=='U'){
                U.pb(mp(y, x));
            }else if (ch=='D'){
                D.pb(mp(y, x));
            }else{
                line[++tot] = LINE(x, y, (ch == 'L'));
            }
            b.pb(x);
        }
        // line[++tot] = LINE(n, m, 1);
        // b.pb(n);
        // D.pb(mp(m, n));

        sort(ALL(b));
        b.erase(unique(ALL(b)), b.end());
        int len = b.size();

        sort(ALL(U));
        int ul = U.size();
        sort(ALL(D));
        int dl = D.size();

        FOR(i, dl) update(1, 1, len, has(D[i].sc), 1);

        sort(line + 1, line + 1 + tot);

        int nowu = 0, nowd = 0;
        ll ans = 0;
        REP(i, 1, tot){
            ll height = line[i].y;
            while (nowd<dl && D[nowd].fi<height){
                update(1, 1, len, has(D[nowd++].sc), -1);
            }
            while (nowu<ul && U[nowu].fi<=height){
                update(1, 1, len, has(U[nowu++].sc), 1);
            }
            ans += (line[i].l ? queryL(1, 1, len, has(line[i].x)) : queryR(1, 1, len, has(line[i].x)));
        }
        printf("%lld\n", ans + 1);
    }
    return 0;
}