//牛客2018 多校B Filling Pools
//施罗德数
#include<bits/stdc++.h>
#define ll long long
#define MAXN 262155 
#define MOD 998244353
using namespace std;

//快速幂
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}
inline ll get_inv(ll x, ll p) { return bin(x, p - 2, p); }

ll Bigcatalan[MAXN];
void init_Bigcatalan(){
    Bigcatalan[0]=Bigcatalan[1]=1,Bigcatalan[2]=3;
    for(int i=3;i<MAXN;i++){
        Bigcatalan[i]=(Bigcatalan[i-1]*(6*i-3)%MOD - Bigcatalan[i-2]*(i-2)%MOD+MOD)%MOD*get_inv(i+1,MOD)%MOD;
    }
}


int main() {
    init_Bigcatalan();
    int n;
    scanf("%d",&n);
    if(n==1) printf("1\n");
    else printf("%lld\n",Bigcatalan[n-1]*2%MOD);
    return 0;
}