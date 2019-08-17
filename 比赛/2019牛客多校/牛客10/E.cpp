//递归 希尔伯特曲线 
//编码 分形
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
const ll MOD = 1e9 + 7;
 
int n;
ll k;
pair<string, pl> a[N];
 
string dfs(ll x,ll y,ll sz){
    if (!sz){
        return "";
    }
    ll midx = (1 << (sz - 1));
    ll midy = (1 << (sz - 1));
    if (x<=midx){
        if (y<=midy){
            return "1" + dfs(y, x, sz - 1);
        }else{
            y -= midy;
            return "4" + dfs(midy - y + 1, midx - x + 1, sz - 1);
        }
    }else{
        x -= midx;
        if (y<=midy){
            return "2" + dfs(x, y, sz - 1);
        }else{
            y -= midy;
            return "3" + dfs(x, y, sz - 1);
        }
    }
}
 
int main(){
    scanf("%d%lld", &n, &k);
    FOR(i,n){
        scanf("%lld%lld", &a[i].sc.fi, &a[i].sc.sc);
        a[i].fi = dfs(a[i].sc.fi, a[i].sc.sc, k);
    }
    sort(a, a + n);
    FOR(i,n){
        printf("%lld %lld\n", a[i].sc.fi, a[i].sc.sc);
    }
    return 0;
}