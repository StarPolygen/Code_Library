#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for (ll i = 0; (i) < (n); (i)++)
#define _rep(i, n) for (ll i = 1; (i) <= (n); (i)++)
#define MOD 1000
#define MAXN 2010
#define TYPE ll






// bell triangle
vector<TYPE> bell[MAXN]; // bell(i) = bell[i][i]
void init_bell()
{
    for (ll i = 0; i < MAXN; i++)
        bell[i] = vector<TYPE>((unsigned) i + 1, 0);
    bell[1][1] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        bell[i][1] = bell[i - 1][i - 1];
        for (ll j = 2; j <= i; j++)
        {
#ifdef MOD
            bell[i][j] = (bell[i][j - 1] + bell[i - 1][j - 1]) % MOD;
#else
//            bell[i][j] = bell[i][j - 1] + bell[i - 1][j - 1];
#endif
        }
    }
}


int main(){
	int T;
	scanf("%d",&T);
	init_bell();
	while(T--){
		int n;
		scanf("%d",&n);
		printf("%lld\n",bell[n+1][1]);
	}
} 
