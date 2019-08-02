#include<bits/stdc++.h>
#define ll long long
using namespace std;


int main() {
    int t;
    scanf("%d",&t);
    while(t--){
        ll n,k; scanf("%lld%lld",&k,&n);
        if(k==1) {printf("%lld\n",n-1); continue;}
        ll kp=n*(k-1)+1;
        ll ceng=0;ll tot=1;ll x=1;
        while(tot<n){
            x*=k;
            tot+=x;
            ceng++;
        }
        ll ans=0;
        ll niu=pow(k,ceng);
        if(niu==kp) ans=2*ceng-2;
        else{
            if(niu>=kp-pow(k,ceng-1)*(k-1)) ans=2*ceng+1-2;
            else ans=2*ceng;
        } 
        printf("%lld\n",ans);
    }
    return 0;
}