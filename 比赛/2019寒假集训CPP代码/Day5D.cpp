#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define N 5001000
#define mod 1000000007
#define ll long long
using namespace std;
template<typename T>inline void read(T &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}

long long f[N],sum[N];


int inv3;
ll fast_exp(ll a,ll b,ll c)
{
    ll res=1;
    while(b)
    {
        if(b&1){
            res=res*a%c;
        }
        a=a*a%c;
        b>>=1;
    }
    return res;
}

//暴力求解前根号n待求积性函数的前缀和 
void get(int maxn)
{
	for(int i=1;i<=maxn;++i){
        f[i]=(f[i]+(1LL*i*i-3*i+2));
        for(int j=2*i;j<=maxn;j+=i){
            f[j]=(f[j]-f[i]);
        }
    }
    for(int i=1;i<=maxn;++i) {
        f[i]=(f[i-1]+f[i])%mod;
    }

}

tr1::unordered_map<ll,int> mp;

ll mul(ll a,ll b){
	return (a*b)%mod;
}
long long djsf(ll n)
{
    if(n<=1e6) return f[n];
    if(mp[n]) return mp[n];
    ll ans=(((mul(n,mul(n,n))-mul(3,mul(n,n))+mod)%mod+2*n)%mod*inv3)%mod;
    for(ll l=2,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        ans=(ans-(r-l+1)*djsf(n/l)%mod+mod)%mod;
        
    }
    
    return mp[n]=ans;

}

int main()
{
    int t;
    read(t);
    inv3=fast_exp(3,mod-2,mod);
    get(1e6);
    while(t--)
    {
        static int n;
        read(n);
        printf("%lld\n",djsf(n));
    }
    return 0;
}
