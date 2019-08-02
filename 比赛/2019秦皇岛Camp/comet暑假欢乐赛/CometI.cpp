#include<bits/stdc++.h>
#define ll long long
using namespace std;


int main() {
    ll n,m,k;
    scanf("%lld%lld%lld",&n,&m,&k);
    if(k<=(n-1)*(m-1)) printf("%lld\n",n+m-2);
    else{
        printf("-1\n");
    }
    return 0;
}