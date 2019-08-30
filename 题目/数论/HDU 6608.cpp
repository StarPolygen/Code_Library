//素性测试 威尔逊定理 素数分布
//求比素数P小的最大素数Q 的阶乘模P
//素数分布：接近无穷时 π(n)=n/logn   因此得到枚举不会很多 复杂度满足暴力
//威尔逊定理：P为素数 等价于 （P-1）！=-1 modP
//因此从P-1出发依次枚举Q进行素性检验 并同时从（P-1）！出发维护Q！ modP即可 
//注意枚举的i是longlong 且由于mod可能大于3E9需要使用快速乘
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;

//O(1)快速乘 
ll mul(ll u, ll v, ll p) {
    return (u * v - ll((long double) u * v / p) * p + p) % p;
}
inline ll bin(ll base, ll n, ll p) {
    ll res = 1;
    while (n) {
        if (n & 1) res = mul(res , base , p);
        base = mul(base , base , p);
        n >>= 1;
    }
    return res;
}inline ll get_inv(ll x, ll p) {  return bin(x, p - 2, p);  }


//素性检验
bool checkQ(ll a, ll n) {
    if (n == 2 || a >= n) return 1;
    if (n == 1 || !(n & 1)) return 0;
    ll d = n - 1;
    while (!(d & 1)) d >>= 1;
    ll t = bin(a, d, n);  // 不一定需要快速乘
    while (d != n - 1 && t != 1 && t != n - 1) {
        t = mul(t, t, n);
        d <<= 1;
    }
    return t == n - 1 || d & 1;
}

bool primeQ(ll n) {
    static vector<ll> t = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if (n <= 1) return false;
    for (ll k: t) if (!checkQ(k, n)) return false;
    return true;
}




int main() {
    int T; scanf("%d",&T);
    while(T--){
        ll n; scanf("%lld",&n);
        LL mod=n-1;
        for(ll i=n-1;i>=0;i--){
            mod=mod*get_inv(i,n)%n;
            if(primeQ(i-1))
            break;
        }
        ll ans=(ll)mod;
        printf("%lld\n",ans);
    }
    return 0;
}