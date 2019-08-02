#include<bits/stdc++.h>
#define ll long long
using namespace std;


int main() {
    ll n,mod;
    scanf("%lld %lld",&n,&mod);
    if(n>3) printf("0\n");
    else{
        if(n==0||n==1) printf("%lld\n",1ll%mod);
        else if(n==2) printf("%lld\n",2ll%mod);
        else if(n==3){
            ll ans=1;
            for(int i=720;i>=1;i--){
                ans=ans*i%mod;
            }
            printf("%lld\n",ans);
        }  
    }
    return 0;
}