//二次剩余
//给定mod意义下的x+y 和 xy 求解x、y (x小于等于y)
//解法：借用二次剩余的思想 解方程即可
#include<bits/stdc++.h>
#define ll long long
using namespace std;


int Pow(int a,int b,int p)
{
    int res=1;
    for(;b;a=1LL*a*a%p,b>>=1)
        if(b&1) res=1LL*a*res%p;
    return res;
}

bool Legendre(int a,int p)
{
    return Pow(a,p-1>>1,p)==1;
}

ll modsqr(int a,int p)
{
    int x;
    int i,k,b;
    if(p==2) x=a%p;
    else if(p%4==3) x=Pow(a,p+1>>2,p);
    else
    {
        for(b=1;Legendre(b,p);++b);
        i=p-1>>1;
        k=0;
        do
        {
            i>>=1;
            k>>=1;
            if(!((1LL*Pow(a,i,p)*Pow(b,k,p)+1)%p)) k+=p-1>>1;
        }while(!(i&1));
        x=1LL*Pow(a,i+1>>1,p)*Pow(b,k>>1,p)%p;
    }
    if(p-x<x) x=p-x;
    if(x==p-x)
        return x;
    else return p-x;
}
const ll mod = 1000000007;
int main() {
    int T;
    scanf("%d", &T);
    while(T--){
        ll he, ji;
        scanf("%lld %lld", &he, &ji);
        ll chas2 =( (((he * he%mod - ji+ mod) % mod-ji+mod)%mod-ji+mod)%mod-ji+mod)%mod;
        if(chas2==0){
            ll x1 = he / 2; ll x2 = (he + mod) / 2;
            if(2*x1 == he){
                printf("%lld %lld\n", x1, x1);
                continue;
            }
            else if(2*x2 == (he+mod)){
                printf("%lld %lld\n", x1, x1);
                continue;
            }
            else{
                printf("-1 -1\n");
            }
        }
        if(!Legendre(chas2,mod)) 
        {
            puts("-1 -1");
            continue;
        }
        ll cha1 = modsqr(chas2, mod);
        ll cha2 = mod - cha1;
        ll he1 = he;
        ll he2 = he + mod;
        ll a1 = (he1 + cha1) / 2;
        ll b1 = (he1 - cha1) / 2;
        ll a2 = (he1 + cha2) / 2;
        ll b2 = (he1 - cha2) / 2;
        ll a3 = (he2 + cha1) / 2;
        ll b3 = (he2 - cha1) / 2;
        ll a4 = (he2 + cha2) / 2;
        ll b4 = (he2 - cha2) / 2;
        if((a1+b1)%mod==he && a1*b1%mod==ji && a1>=0 && b1>=0){
            printf("%lld %lld\n", min(a1, b1), max(a1, b1));
            continue;
        }
        if((a2+b2)%mod==he && a2*b2%mod==ji && a2>=0 && b2>=0){
            printf("%lld %lld\n", min(a2, b2), max(a2, b2));
            continue;
        }
        if((a3+b3)%mod==he && a3*b3%mod==ji && a3>=0 && b3>=0){
            printf("%lld %lld\n", min(a3, b3), max(a3, b3));
            continue;
        }
        if((a4+b4)%mod==he && a4*b4%mod==ji && a4>=0 && b4>=0){
            printf("%lld %lld\n", min(a4, b4), max(a4, b4));
            continue;
        }
        printf("-1 -1\n");
    }
    return 0;
}