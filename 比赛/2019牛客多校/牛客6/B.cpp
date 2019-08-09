//结论题
//实数域内 只有1次 和 2次δ<0的多项式不能因式分解
#include<bits/stdc++.h>
#define ll long long
using namespace std;

inline ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
} 
ll factor[30], f_sz, factor_exp[30];
void get_factor(ll x)
{
    f_sz = 0;
    memset(factor, 0, sizeof(factor));
    memset(factor_exp, 0, sizeof(factor_exp));

    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            factor[f_sz] = i;
            factor_exp[f_sz] = 0;
            while (x % i == 0)
            {
                x /= i;
                factor_exp[f_sz]++;
            }
            f_sz++;
        }
    if (x > 1)
    {
        factor[f_sz] = x;
        factor_exp[f_sz] = 1;
        f_sz++;
    }
}
ll arr[200];
int main() {
    int T;scanf("%d",&T);
    while(T--){
        int n; scanf("%d",&n);
        memset(arr,0,sizeof(arr));
        int n1=n; int flag=1;
        for(int i=n;i>=0;i--){
            scanf("%lld",&arr[i]);
            if(flag==1 && arr[i]==0){
                n1--;
            }else{
                flag=0;
            }
        }
        // printf(" %d saddas\n",n1);
        if(n1<=1) { printf("Yes\n");}
        else if(n1==2){
            ll a,b,c;
            a=arr[2]; b=arr[1]; c=arr[0];
            if(1ll*b*b-4ll*a*c<0) printf("Yes\n");
            else printf("No\n");
        }
        else{
            ll an = 0; int gg=1;
            for(int i=n1-1;i>=0;i--){
                if(arr[i]<0) arr[i]*=-1;
                if(arr[i]!=0 && gg==1){
                    an=arr[i]; gg=0;
                }else{
                    if(arr[i]!=0){
                        an = gcd(an,arr[i]);
                    }
                }
            }
            // printf("%lld\n",an);
            if(an == 0 || an == 1){
                printf("No\n"); continue;
            }
            else{
                get_factor(an);
                for(int i=0;i<f_sz;i++){
                    ll ss=1ll*factor[i]*factor[i];
                    if(arr[n1]%factor[i]!=0 && arr[0]%ss!=0){
                        printf("Yes\n"); break;
                    }else{
                        printf("No\n"); break;
                    }
                }
            }
        }
    }
    return 0;
}