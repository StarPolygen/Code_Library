#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<math.h>
typedef long long ll;
#define TYPE ll
using namespace std;
const int MAXN=2010;
const ll MOD=1e9+7;
vector<TYPE> stirling_first[MAXN];
void init_stirling_first()
{
    for (ll i = 0; i < MAXN; i++)
        stirling_first[i] = vector<TYPE>((unsigned) i + 1, 0);
    for (ll i = 1; i < MAXN; i++)
    {
        for (ll j = 1; j < i; j++)
        {
#ifdef MOD
            stirling_first[i][j] = ((i - 1) * stirling_first[i - 1][j] % MOD + stirling_first[i - 1][j - 1]) % MOD;
#else
//            stirling_first[i][j] = (i - 1) * stirling_first[i - 1][j] + stirling_first[i - 1][j - 1];
#endif
        }
        stirling_first[i][i] = (TYPE) 1;
    }
}
ll c[MAXN][MAXN];
ll s[MAXN][MAXN];
void combinition_number(){
	 for(int i=0; i<MAXN; i++)
    {
        c[i][0]=c[i][i]=1;
        s[i][i]=1; //其实第一类斯特灵数和组合数是可以一起算的哦 
        for(int j=1; j<i; j++)
        {
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
            s[i][j]=((i-1)*s[i-1][j])%MOD+s[i-1][j-1]%MOD;
        }
    }

}
int main(){
	int t;
	scanf("%d",&t);
//	init_stirling_first();
	combinition_number();
	while(t--){
		int n1,f1,b1;
		scanf("%d%d%d",&n1,&f1,&b1);
		int ans=(s[n1-1][f1+b1-2]*c[f1+b1-2][f1-1])%MOD;
		printf("%d\n",ans);
	} 
	return 0;
}
