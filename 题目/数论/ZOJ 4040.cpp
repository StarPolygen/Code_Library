//分解质因数 
//ZOJ 4040
//Given an integer N, calculate the smallest positive integer that is not a sum of distinct divisors of N 
//算法： 分解质因数 逐步加入质因数扩展寻找所求
//使用模板：O(1)快速乘 快速幂 欧几里得  素性测试和大数分解 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


//O(1)快速乘 
ll mul(ll u, ll v, ll p) {
    return (u * v - ll((long double) u * v / p) * p + p) % p;
}

//快速幂 
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = mul(x,x,mod))
        if (n & 1) ret = mul(ret,x,mod);
    return ret;
}

//欧几里得
inline ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
} 



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

mt19937 mt(time(0));
ll pollard_rho(ll n, ll c) {
    ll x = uniform_int_distribution<ll>(1, n - 1)(mt), y = x;
    auto f = [&](ll v) { ll t = mul(v, v, n) + c; return t < n ? t : t - n; };
    while (1) {
        x = f(x); y = f(f(y));
        if (x == y) return n;
        ll d = gcd(abs(x - y), n);
        if (d != 1) return d;
    }
}



ll fac[100], fcnt;//素因子及个数 
void get_fac(ll n, ll cc = 19260817) {
    if (n == 4) { fac[fcnt++] = 2; fac[fcnt++] = 2; return; }
    if (primeQ(n)) { fac[fcnt++] = n; return; }
    ll p = n;
    while (p == n) p = pollard_rho(n, --cc);
    get_fac(p); get_fac(n / p);
}


int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		fcnt=0;
		ll n;
		scanf("%lld",&n);
		if(n%2==1){
			printf("2\n");continue;
		}
		get_fac(n);
		sort(fac,fac+fcnt); 
		ll ans=1; ll tans=ans; ll last=1,temp=1;
		for(int i=0;i<fcnt;i++){
			if(fac[i]==last) {
				temp*= fac[i];
			}else{
				temp=last=fac[i];
				tans=ans;
			}
			if(ans +1<temp) break;
			ans+=tans*temp;	
		}
		printf("%lld\n",ans+1);
	}
	
	return 0;
}
 

 
