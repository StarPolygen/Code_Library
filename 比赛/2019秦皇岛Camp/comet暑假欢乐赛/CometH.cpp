#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const ll mod=1e9+7;

ll arr[100010];
ll sec[100010];
signed main() {
    memset(arr,0,sizeof(arr));
    memset(sec,0,sizeof(sec));
    ll n; scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&arr[i]);
    }
    sort(arr+1,arr+1+n);
    ll tot=1; sec[1]=tot;
    for(int i=2;i<=n;i++){
        if(arr[i]>arr[i-1]){
            tot++;
            sec[i]=tot;
        }
        else sec[i]=tot;
    }
    // for(int i=1;i<=n;i++){
    //     printf("%d ",sec[i]);
    // }
    ll ck=0;ll ans=1;
    for(ll i=n;i>=1;i--){
        ll wa=((n-sec[i]+mod)%mod+1-ck+mod)%mod;
        ans=ans%mod*wa%mod;
        ck++;
    }
    printf("%lld\n",ans);
    return 0;
}