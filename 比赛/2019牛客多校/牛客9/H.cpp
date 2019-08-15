//主席树
//BIgBang_019可以秒
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
const int MOD = 1e9 + 7;
const int R = 100000;

int T[N], cnt[N * 24], lc[N * 24], rc[N * 24], tot;
ll sum[N * 24];


void update(int &rt,int last,int l,int r,int p){
    rt = ++tot;
    int now = tot;
    cnt[now] = cnt[last] + 1;
    sum[now] = sum[last] + p;
    if (l==r) return;
    int mid = l + r >> 1;
    lc[now] = lc[last];
    rc[now] = rc[last];
    if (p<=mid) update(lc[now], lc[last], l, mid, p);
    else update(rc[now], rc[last], mid + 1, r, p);
}
pair<ll,int> query(int now,int last,int l,int r,double hei){
    if (l==r){
        return l <= hei ? mp(sum[now] - sum[last], cnt[now] - cnt[last]) : mp(0ll, 0);
    }
    int mid = l + r >> 1;
    ll ls = sum[lc[now]] - sum[lc[last]];
    int lt = cnt[lc[now]] - cnt[lc[last]];
    if (hei>mid){
        pair<ll, int> res = query(rc[now], rc[last], mid + 1, r, hei);
        return mp(res.fi + ls, res.sc + lt);
    }else{
        return query(lc[now], lc[last], l, mid, hei);
    }
}
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    REP(i,1,n){
        int x;
        scanf("%d", &x);
        update(T[i], T[i - 1], 1, R, x);
    }
    while (m--){
        int ql, qr, x, y;
        scanf("%d%d%d%d", &ql, &qr, &x, &y);
        double H = sum[T[qr]] - sum[T[ql - 1]];
        double l = 0, r = R, mid;
        double left = H - x * H / y;
        while (r-l>1e-8){
            mid = (l + r) / 2;
            pair<ll, int> res = query(T[qr], T[ql - 1], 1, R, mid);
            int cutn = qr - ql + 1 - res.sc;
            double qleft = res.fi + cutn * mid;
            if (qleft>=left){
                r = mid;
            }else{
                l = mid;
            }
        }
        printf("%.12f\n", r);
    }
    return 0;
}
