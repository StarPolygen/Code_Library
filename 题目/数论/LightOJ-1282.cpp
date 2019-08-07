//对数 快速幂
//求n^k的前3位和后三位   n 2^31  k 1e7
//后三位：快速幂mod1000即可  前三位：取10对数为 klogn  原数n^k=10^(klogn)=10^(a+b) a为klogn的整数部分 b为klogn的小数部分
//10^a决定n^k有几位 而只有10^b 也就是小数部分决定了每一位上是多少 因此只需要得到10^fmod(klogn,1)即可
#include<bits/stdc++.h>
#define ll long long
using namespace std;

inline ll bin(ll base, ll n, ll p) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}inline ll get_inv(ll x, ll p) {  return bin(x, p - 2, p);  }

int main() {
    int T; scanf("%d",&T); int Cas=0;
    while(T--){
        Cas++;
        ll n,k; scanf("%lld %lld",&n,&k);
        int last3 = (int)bin(n,k,1000);
        double pre3 = pow(10,fmod(k*log10(1.0*n),1));
        printf("Case %d: %d %03d\n",Cas,(int)(pre3*100),last3);
    }
    return 0;
}