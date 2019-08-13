//概率 递推/DP
//Author: 小明
//从1几开始升级 每次升级有pi概率从i升到下一级i+1 否则退回到Xi级 无论成功与否都花费Ci代价 若干查询问从a到b级期望花费几何？
/*F[i]:从0开始第一次到达i级的花费期望
F[i]=F[i-1] + ai*pi + (F[i]+ai-F[xi])*(1-pi)
化简得  F[i]=F[i-1]+F[xi]*(pi-1)/pi+ai/pi
*/
/*或另一递推式:
E[i]:从i-1到i的期望
F[i]: 从0开始第一次到达i级的花费期望：
E[i]=(ai*pi)+(1-pi)*(F[i-1]-F[xi]+E[i]+ai)
F[i]=F[i-1]+E[i]
*/
#include<cstdio>
#include<cstring>

using namespace std;
const int maxn=1000000;
const long long mod=1E9+7;

typedef long long ll;

ll p[maxn];
ll rp[maxn];
ll pp[maxn];

int x[maxn];
ll a[maxn];
ll f[maxn];

inline int getnum(){
    char ch;int s=0;
    while ((ch=getchar())=='\n'||ch=='\r' || ch==' ')
        ;
    while (ch>='0' && ch<='9') {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s;
}

long long quickpow(long long x,long long n) {
    long long res=1;
    x=x%mod;
    while(n)
    {
        if(n%2==1)res=(res*x)%mod;
        n=n/2;
        x=(x*x)%mod;
    }
    return res;
}

ll gcd(ll a,ll b) {
    return b == 0? a : gcd(b,a%b);
}

//F[i]=F[i-1]+F[xi]*(pi-1)/pi+ai/pi;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n,q;
        n=getnum();
        q=getnum();
        for (int i=1;i<=n;i++) {
            long long r,s;
            r=getnum();
            s=getnum();
            x[i]=getnum();
            a[i]=getnum();
            
            long long rr=s-r;
            long long ss=quickpow(s,mod-2);
            p[i]=r*ss%mod;
            rp[i]=rr*ss%mod;
            pp[i]=quickpow(p[i],mod-2);
        }
        f[0]=0;
        f[1]=0;
        for (int i=1;i<=n;i++) {
            f[i+1]=f[i]*pp[i]%mod-f[x[i]]*rp[i]%mod*pp[i]%mod+mod+a[i]*pp[i]%mod;
            f[i+1]=f[i+1]%mod;
        }
        for (int i=1;i<=q;i++) {
            int l,r;
            scanf("%d%d", &l,&r);
            ll ans=(mod+f[r]-f[l])%mod;
            printf("%lld\n", ans);
        }
        
//        for (int i=1;i<=n+1;i++) {
//            printf("%lld ", f[i]);
//        }printf("\n");
        
    }
    return 0;
}

/*
2
5 5
1 1 1 2
1 1 1 3
1 1 1 4
1 1 1 1
1 1 1 5
1 2
2 3
3 4
4 5
5 6
3 2
1 1 1 2
1 2 1 3
1 3 3 4
1 4
3 4
*/ 