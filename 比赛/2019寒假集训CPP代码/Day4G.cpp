#include<bits/stdc++.h>
#define N 50100
using namespace std;
bool vis[N];
int prim[N],cnt,mu[N],sum[N];
long long g[N];
void get_mu(int n)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]){prim[++cnt]=i;mu[i]=-1;}
        for(int j=1;j<=cnt&&prim[j]*i<=n;j++)
        {
            vis[prim[j]*i]=1;
            if(i%prim[j]==0)break;
            else mu[i*prim[j]]=-mu[i];
        }
    }
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+mu[i];
    for(int i=1;i<=n;i++)
    {
        long long ans=0;
        for(int l=1,r;l<=i;l=r+1)
        {
            r=(i/(i/l));
            ans+=1ll*(r-l+1)*1ll*(i/l);
        }
        g[i]=ans;
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    get_mu(50000);
    while(t--)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        int max_rep;max_rep=min(n,m);
        long long ans;ans=0;
        for(int l=1,r;l<=max_rep;l=r+1)
        {
            r=min(n/(n/l),m/(m/l));
            ans+=(sum[r]-sum[l-1])*1ll*g[n/l]*1ll*g[m/l];
        }
        printf("%lld\n",ans);
    }
    return 0;
}
