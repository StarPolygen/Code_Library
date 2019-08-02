#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll arr[100010];
int main() {
    memset(arr,0,sizeof(arr));
    ll n,k;
    scanf("%lld %lld",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&arr[i]);
    }
    ll ans=0;
    for(int i=2;i<=n;i++){
        if(i>n) break;
        if(abs(arr[i]-arr[i-1])<k) {ans++; i++;}
    }
    printf("%lld\n",ans);
    return 0;
}