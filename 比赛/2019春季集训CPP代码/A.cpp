#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9+7;

long long Mode(long long a, long long b, long long mode)

{

	long long sum = 1;

	while (b) {

		if (b & 1) {

			sum = (sum * a) % mode;

			b--;

		}

		b /= 2;

		a = a * a % mode;

	}

	return sum;

}

int main(){
	
	long long n;
	
	while(~scanf("%lld",&n)){
		long long x=Mode(2,n,mod);
		long long ans=(((n-1)%mod*x)%mod+1)%mod;
		printf("%lld\n",ans);

	}
		return 0;
} 
