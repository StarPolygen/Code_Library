#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=3010;
const ll mod=998244353;
ll arr[maxn];
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}
inline ll get_inv(ll x, ll p) { return bin(x, p - 2, p); }
int main() {
    arr[0]=0;
    arr[1]=0;
    ll inv3=get_inv(3,mod);
    for(int i=2;i<maxn;i++){
        arr[i]=(arr[i-1]*(i-1)%mod*get_inv(i,mod)%mod+(i-1)*inv3%mod)%mod;
    }
    int a;
    while(~scanf("%d",&a)){
        printf("%lld\n",arr[a]);
    }
    return 0;
}