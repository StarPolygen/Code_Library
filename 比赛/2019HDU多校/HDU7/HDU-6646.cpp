//字符串Hsh /分类讨论+大数
//Author: BigBang_019
#pragma GCC optimize(3)
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
const int N = 1e6 + 5;
const int base = 10;
const int R = 1e5 + 1;
const int MOD = 1222827239;

char s[3][N];
ll L[3];
ll V[3];
map<ll, int> fn;

void align(char *s,int tolen){
    s[tolen] = '\0';
    int len = strlen(s);
    REP(i,len,tolen-1){
        s[i] = '0';
    }
}
void makehash(char *s,ll &V){
    ll ans = 0;
    int len = strlen(s);
    FOR(i,len){
        ans = (1ll * ans * base + s[i] - '0') % MOD;
    }
    V = ans;
}
ll qp(ll a,int k){
    ll ans = 1;
    while (k){
        if (k&1) ans = 1ll*ans * a % MOD;
        a = 1ll*a * a % MOD;
        k >>= 1;
    }
    return ans;
}
void work(ll C,ll fr,ll ba,int &x){
    ll dif = ((C - fr) % MOD + MOD) % MOD;
    ll inv = qp(dif, MOD - 2);
    auto it = fn.find(1ll * ba * inv % MOD);
    if (it!=fn.end()){
        x = it->second;
        return;
    }
    x = -1;
}

int main(){
    // freopen("E:\\vscode\\c++\\in.txt", "r", stdin);
    // freopen("E:\\vscode\\c++\\out.txt", "w", stdout);
    // clock_t st = clock();
    ll po = 1;
    fn[po] = 0;
    REP(i,1,R){
        fn[po = 1ll * po * 10 % MOD] = i;
    }
    int _;
    for (scanf("%d", &_); _;_--)
    {
        int len = 0;
        memset(L, 0, sizeof(L));
        FOR(i, 3) {
            scanf(" %s", s[i]);
            len = max(len, (int)strlen(s[i]));
        }
        FOR(i, 3) {
            L[i] = len - strlen(s[i]);
            align(s[i], len);
            makehash(s[i], V[i]);
        }
        int x;
        int a, b, c;
        a = L[0], b = L[1], c = L[2];
        work(V[2], V[0], V[1], x);
        if (~x){
            b -= x;
            int d = min(0, min(a, min(b, c)));
            printf("%d %d %d\n", a - d, b - d, c - d);
            continue;
        }
        work(V[2], V[1], V[0], x);
        if (~x){
            a -= x;
            int d = min(0, min(a, min(b, c)));
            printf("%d %d %d\n", a - d, b - d, c - d);
            continue;
        }

        V[2] = 1ll*V[2] * 10 % MOD;
        L[2]++;
        a = L[0], b = L[1], c = L[2];
        work(V[2], V[0], V[1], x);
        if (~x){
            b -= x;
            int d = min(0, min(a, min(b, c)));
            printf("%d %d %d\n", a - d, b - d, c - d);
            continue;
        }
        work(V[2], V[1], V[0], x);
        if (~x){
            a -= x;
            int d = min(0, min(a, min(b, c)));
            printf("%d %d %d\n", a - d, b - d, c - d);
            continue;
        }
        printf("-1\n");
    }
    // clock_t et = clock();
    // cout << (double)(et - st) / CLOCKS_PER_SEC << endl;
    // fclose(stdin);
    // fclose(stdout);
    return 0;
}