#include<bits/stdc++.h>
#define ll long long
const int MAXN=200010;
const int MOD=1e8+7;

int m,p,q,n;
ll fac[MAXN],inv_fac[MAXN];
inline ll C(ll n, ll m) { // n >= m >= 0
    return n < m || m < 0 ? 0 : fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

ll qpow(ll x, ll n)  
{  
    ll res = 1;  
    while(n)  
    {  
        if(n & 1)  
            res = (res * x) % MOD;  
        x = (x * x) % MOD;  
        n >>= 1;
    }  
    return res;  
}  
//½×³ËÄæÔª 
void pre()  
{  
    fac[0] = 1;  
    for(int i = 1; i <= MAXN; i++)  
        fac[i] = (fac[i - 1] * i) % MOD;  
    inv_fac[MAXN] = qpow(fac[MAXN], MOD - 2);  
    for(int i = MAXN - 1; i >= 0; i--)  
        inv_fac[i] = (inv_fac[i + 1] * (i + 1)) % MOD;   
}  



int main(){
	pre();
	while(~scanf("%d%d%d%d",&m,&n,&p,&q)){
		ll ans=((C(m+n,n)*C(m-p+q,q))%MOD-(C(m+q,q)*C(m-p+n,n))%MOD+MOD)%MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
