//并查集 组合数
//Author：BigBang_019
// #pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define sc second
#define pb push_back
#define mp make_pair
#define LEN(X) strlen(X)
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, N) for (int I = 0; I < (N); ++I)
#define FORD(I, N) for (int I = N; ~I; --I)
#define REP(I, A, B) for (int I = A; I <= (B); ++I)
#define REPD(I, B, A) for (int I = B; I >= A; --I)
#define FORS(I, S) for (int I = 0; S[I]; ++I)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
const int N = 1e5 + 5;
const int MOD = 1e9 + 7;
  
__int128_t ans, C[N][5];
__int128_t allS;
__int128_t sz[N];
 
int f[N];
int n;
  
int find(int x){
    return (x == f[x] ? x : f[x] = find(f[x]));
}
int make(int x,int y){
    x = find(x);
    y = find(y);
    f[x] = y;
    sz[y] += sz[x];
    return sz[y];
}
void init(){
    for (int i = 1; i <= n;i++)
    {
        f[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i <= n; i++)
    {
        C[i][0] = 1;
        for (int j = 1; j <= 4; j++)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            // cout << i << " " << j << " " << ll(C[i][j]) << endl;
        }
    }
}
void print(__int128_t x)
{
    if (x>9)
        print(x / 10);
    putchar('0' + x % 10);
}
int main(){
    int m;
    scanf("%d%d", &n, &m);
    init();
    ans = C[n][4];
    allS = 0;
    print(ans);
    puts("");
    while (m--){
        int x, y;
        scanf("%d%d", &x, &y);
        x = find(x), y = find(y);
        if (x!=y){
            __int128_t A = sz[x];
            __int128_t B = sz[y];
  
            ans -= C[A][1] * C[B][1] * C[n - A - B][2];
            ans += C[A][1] * C[B][1] * allS;
            ans -= C[A][1] * C[B][1] * C[A][2];
            ans -= C[A][1] * C[B][1] * C[B][2];
 
            allS -= C[A][2];
            allS -= C[B][2];
            allS += C[make(x, y)][2];
        }
        print(ans);
        puts("");
    }
    return 0;
}
