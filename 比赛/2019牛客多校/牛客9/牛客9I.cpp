//类欧几里得 类型f
//给定n,m   求∑k ((kM)&M) mod(1E9+7) k=[1,n]   
//可以按位分别统计贡献 
//对于m的每一个是1的位
//      计算有多少个km该位也是1,并按照位数加权计入对答案的贡献
//      该位为1的km的个数  就是Σ km/(2<<i)%2  该式又等于Σkm/(2<<i) - Σkm/(2<<i+1)*2
//      转化为了等差数列除以某数求和的经典问题  使用类欧几里得解决
//注意：1.位运算优先级较低 需要加括号再取模  位运算优先级小于+-*/% 但大于+= -= /= *= %=
//      2.当位移运算达到ll数量级时，最先的1必须为1ll
//      3.本题存在ll互乘，因此有可能爆ll，需要使用LL:__int128


AC1：
//模板：类欧几里得求解f
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define LL __int128
#define MOD 1000000007
const ll mod = MOD;
ll n,m,ans;
 
inline ll bin(ll base, ll n, ll p) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}inline ll get_inv(ll x, ll p) {  return bin(x, p - 2, p);  }
const ll Mod=1e9+7;
const ll inv2=get_inv(2,Mod),inv6=get_inv(6,Mod);
LL f(LL a,LL b,LL c,LL n){
    if(a==0)return (n+1)*(b/c)%mod;
    if(a>=c||b>=c)return (f(a%c,b%c,c,n)+n*(n+1)%mod*inv2%mod*(a/c)%mod+(n+1)*(b/c)%mod)%mod;
    LL M=(a*n+b)/c;
    return ((n*M%mod-f(c,c-b-1,a,M-1))%mod+mod)%mod;
}
 
int main()
{
    scanf("%lld%lld",&n,&m);
    for(ll i=0;i<=40;i++)   //按位统计贡献
        if((1ll<<i)&m){  //对于m的每一个是1的位
            //计算有多少个km该位也是1,并按照位数加权计入对答案的贡献
            //该位为1的km的个数  就是Σ km/(2<<i)%2  该式又等于Σkm/(2<<i) - Σkm/(2<<i+1)*2
            //转化为了等差数列除以某数求和的经典问题  使用类欧几里得解决
            (ans+=(((f(m,0,1ll<<i,n)+2*MOD-2*f(m,0,1ll<<(i+1),n))%MOD)<<i)%MOD)%=MOD;
        }
            //注意：位运算优先级较低
            //     当位移运算最终要达到longlong时，最先的1必须为1ll
    printf("%lld\n",ans);



AC2：
//模板：类欧几里得求解fhg
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll __int128
// #define ll long long
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
const ll Mod=1e9+7;
const ll inv2=get_inv(2,Mod),inv6=get_inv(6,Mod);
ll S1(ll x){if(x>=Mod)x%=Mod;return (x*(x+1)%Mod)*inv2%Mod;}
ll S2(ll x){if(x>=Mod)x%=Mod;return (x*(x+1)%Mod*(x+x+1)%Mod)*inv6%Mod;}
ll Sqr(ll x){return x*x%Mod;}
struct node{
	ll f,g,h;
	void clear(){f=g=h=0;}
	node(){}
	node(ll a,ll b,ll c):f(a),g(b),h(c){}
	void out(){printf("%lld %lld %lld\n",f,g,h);}
};

node calc(ll a,ll b,ll c,ll n){
	node ans,res;ans.clear();
	ll m,t1,t2,s1,s2;
	if(!n){ans.f=b/c;ans.g=Sqr(b/c);return ans;}
	if(!a){
		t1=b/c;
		ans.f=(n+1ll)*t1%Mod;
		ans.g=(n+1ll)*Sqr(t1)%Mod;
		ans.h=S1(n)*t1%Mod;
		return ans;
	}
	if(a>=c||b>=c){
		t1=a/c;t2=b/c;
		res=calc(a%c,b%c,c,n);
		s1=S1(n);s2=S2(n);
		ans.f=(((s1*t1%Mod)+(n+1ll)*t2%Mod)%Mod+res.f)%Mod;
		ans.g=(((Sqr(t1)*s2%Mod+(n+1ll)*Sqr(t2)%Mod)%Mod)+((t1*t2%Mod)*2ll*s1%Mod+(t1*2ll*res.h%Mod))%Mod+(res.g+t2*2ll*res.f%Mod)%Mod)%Mod;
		ans.h=((s2*t1%Mod+s1*t2%Mod)+res.h)%Mod;
		return ans;
	}
	m=(n*a+b)/c-1;
	res=calc(c,c-b-1,a,m);
	ll w1=n*(m+1)%Mod,w2=n*(n+1)%Mod,w3=m+1;
	if(w3>=Mod)w3%=Mod;
	ans.f=(w1-res.f)%Mod;if(ans.f<0)ans.f+=Mod;
	ans.g=((w1*w3)%Mod-((res.h*2ll%Mod+res.f)%Mod))%Mod;if(ans.g<0)ans.g+=Mod;
	ans.h=((w2*w3)%Mod-(res.f+res.g)%Mod)%Mod*inv2%Mod;if(ans.h<0)ans.h+=Mod;
	return ans;
}
long long n1, m1, ans1;
signed main()
{
    scanf("%lld%lld",&n1,&m1);
    ans1 = 0;
    for(ll i=0;i<=40;i++)   //按位统计贡献
        if((1ll<<i)&m1) { //对于m的每一个是1的位
            //计算有多少个km该位也是1,并按照位数加权计入对答案的贡献
            //该位为1的km的个数  就是Σ km/(2<<i)%2  该式又等于Σkm/(2<<i) - Σkm/(2<<i+1)*2
            //转化为了等差数列除以某数求和的经典问题  使用类欧几里得解决
            ans1 += (((calc(m1, 0, 1ll << i, n1).f+2ll*Mod-2ll*calc(m1,0,1ll<<(i+1),n1).f)%Mod)<<i)%Mod;
            ans1 %= Mod;
            //注意：1.位运算优先级较低 需要加括号再取模  位运算优先级小于+-*/% 但大于+= -= /= *= %=
            //     2.当位移运算达到ll数量级时，最先的1必须为1ll
            //     3.本题存在ll互乘，因此有可能爆ll，需要使用LL:__int128
        }
    printf("%lld\n",ans1);
}