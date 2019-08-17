//递归
//字符串作为fibonacci 求第n个字符串的k位之后10个字符
//按照fibonacci的构造规则 递归查询即可
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
typedef pair<ll, ll> pi;
typedef pair<ll, ll> pl;
const ll N = 5e3 + 5;
const ll MOD = 1e9 + 7;
const ll B = 56;
ll f[N];
string t1 = "COFFEE";
string t2 = "CHICKEN";
ll maxn;
void dfs(ll x,ll k){
    if (x==1){
        for (ll i = k - 1; i < t1.size();i++)
        {
            putchar(t1[i]);
            if (--maxn==0)
                break;
        }
        return;
    }
    if (x==2){
        for (ll i = k - 1; i < t2.size();i++)
        {
            putchar(t2[i]);
            if (--maxn==0)
                break;
        }
        return;
    }
    if (k<=f[x-2]){
        dfs(x - 2, k);
    }else{
        dfs(x - 1, k - f[x - 2]);
    }
}
int main(){
    f[1] = 6;
    f[2] = 7;
    for (ll i = 3; i <= B;++i)
    {
        f[i] = f[i - 1] + f[i - 2];
    }
    ll _;
    for (scanf("%lld", &_); _;_--)
    {
        ll n;
        ll k;
        scanf("%lld%lld", &n, &k);
        maxn = n > 56 ? 10 : min(10ll, f[n] - k + 1);
        ll tot = maxn;
        while (n - 1 > 56)
        {
            n -= 2;
        }
        dfs(n, k);
        while (maxn!=0){
            dfs(n, k + tot - maxn);
        }
        puts("");
    }
    return 0;
}