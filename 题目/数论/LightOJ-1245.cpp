//数论分块 求Σn/i

#include<bits/stdc++.h>
#define ll long long
using namespace std;


int main() {
    int T,Cas=0;
    scanf("%d", &T);
    while(T--){
        int n;
        Cas++;
        scanf("%d", &n);
        //f(i) = ⌊ n/i ⌋ = v 时  i的取值范围为 [l,r]
        ll ans = 0;
        for (ll l = 1, r, v; l <= n;l=r+1){
            v = n / l;
            r = n / v;
            ans += (r - l + 1) * v;
        }
        printf("Case %d: %lld\n", ans);
    }
    return 0;
}