//行列式求值(取模)
#include <bits/stdc++.h>
#define ll long long
#define maxn 205
#define inf 0x3f3f3f3f
using namespace std;

ll B[maxn][maxn];
ll n, mod;
 
inline ll det(long long n, long long mod) {
    ll ans = 1;
	for (int i=0;i<n;i++){
		for (int j=i+1;j<n;j++){
			while (B[j][i]){
				ll t = B[i][i] / B[j][i];
				for (int k=i;k<n;k++){
					B[i][k] = (B[i][k] - B[j][k] * t % mod + mod) % mod;
					swap(B[i][k], B[j][k]);
				}
				ans = -ans;
			}
		}
		if (B[i][i] == 0) return 0;
		ans = (ans * B[i][i]) % mod;
	}
	return (ans + mod) % mod;
}


int main()
{
  while(~scanf("%lld%lld",&n,&mod)){
    for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				scanf("%lld",&B[i][j]);
				B[i][j] %= mod;
			}
		}
    ll ans = det(n, mod);
    printf("%lld\n", ans);
  }
  return 0;
}
