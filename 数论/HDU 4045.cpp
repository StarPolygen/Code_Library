//HDU 4045 
//组合 + 第二类斯特灵数 
#include <iostream>
#include <vector>
#define MOD 1000000007
#define MAXN 1010
#define ll long long
#define TYPE long long
using namespace std;



//组合数预处理
ll C[MAXN][MAXN];
void init_C(int n) {
    for(int i=0; i<n; i++) {
        C[i][0] = C[i][i] = 1;
        for(int j=1; j<i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
}



//第二类斯特灵数
ll S[MAXN][MAXN];
void init_stirling_second(){
    S[0][0] = 1;
    for (int i=1; i< MAXN;i++)
        for (int j=1; j<i + 1; j++) S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % MOD;
}


int n, r, k, m;
int main()
{
    init_stirling_second();
    init_C(MAXN);
    while (scanf("%d%d%d%d", &n, &r, &k, &m) != EOF)
    {
        int reserve = n - ((r - 1) * k + 1);
        if(reserve < 0) {
        	printf("0\n");
        	continue;
        }
        ll stp1 = C[reserve+r][r];
        ll stp2 = 0;
        for (int i = 1; i <= m; i++)
        {
            stp2 = (stp2 + S[r][i]) % MOD;
        }
        ll ans = (stp1 * stp2) % MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
