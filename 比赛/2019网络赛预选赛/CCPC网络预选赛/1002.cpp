//权值线段树 节点pos 区间第k小
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
const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

int a[N];
int mx[N << 2];
int n;
void update(int x,int l,int r,int p,int pos){
    if (l==r){
        mx[x] = pos;
        return;
    }
    int mid = l + r >> 1;
    if (p<=mid)
        update(x << 1, l, mid, p, pos);
    else
        update(x << 1 | 1, mid + 1, r, p, pos);
    mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
}

int query(int x,int l,int r,int k,int pos){
    if (l==r){
        return l;
    }
    int mid = l + r >> 1;
    if (k>mid){
        if (mx[x << 1 | 1] <= pos) return -1;
        else return query(x << 1 | 1, mid + 1, r, k, pos);
    }else {
        if (mx[x << 1] <= pos){
            if (mx[x << 1 | 1] <= pos)
                return -1;
            else
                return query(x << 1 | 1, mid + 1, r, k, pos);
        }else{
            ll res = query(x << 1, l, mid, k, pos);
            if (~res) return res;
            else if (mx[x << 1 | 1] > pos) return query(x << 1 | 1, mid + 1, r, k, pos);
            else return -1;
        }
    }
}

void init(){
    memset(mx, 0, sizeof(mx));
}

int main(){
    int _;
    for (scanf("%d", &_); _;--_)
    {
        int q;
        scanf("%d%d", &n, &q);
        init();
        REP(i,1,n){
            scanf("%d", a + i);
            update(1, 1, n + 1, a[i], i);
        }
        update(1, 1, n + 1, n + 1, n + 1);
        int ans = 0;
        FOR(i,q){
            int op;
            int x, k;
            scanf("%d%d", &op, &x);
            x ^= ans;
            if (op==1){
                if (a[x]<=n){
                    update(1, 1, n + 1, a[x], n + 1);
                    a[x] = n + 1;
                }
            }else{
                scanf("%d", &k);
                k ^= ans;
                ans = query(1, 1, n + 1, k, x);
                printf("%d\n", ans);
            }
        }

    }
    return 0;
}