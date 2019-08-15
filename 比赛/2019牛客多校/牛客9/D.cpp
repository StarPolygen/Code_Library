//折半搜索 /状压
//Author: BigBang_019s
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
const int N = 40;
const int MOD = 1e9 + 7;
pair<ull, int> a[N];
ull s;
int n;
bool vis[N];
ull now = 0;
bool fl = 0;
ull sum[N];
vector<ull> fff;
ull fnow;
inline void dfs2(int p){
    if (p<n/2+1){
        fff.pb(fnow);
        return;
    }
    fnow += a[p].fi;
    dfs2(p - 1);
    fnow -= a[p].fi;
    dfs2(p - 1);
}
inline void dfs(int p){
    if (now==s){
        fl = 1;
        return;
    }
    if (p>n)
        return;
    if (now>s){
        return;
    }
    if (p==n/2+1){
        int d = lower_bound(ALL(fff), s - now) - fff.begin();
        if (d>=fff.size() || fff[d]!=s-now)
            return;
    }
    if (now+sum[n]-sum[p-1]<s){
        return;
    }
    now += a[p].fi;
    vis[a[p].sc] = 1;
    dfs(p + 1);
    if (fl)
        return;
    now -= a[p].fi;
    vis[a[p].sc] = 0;
    dfs(p + 1);
}
inline ull getnum(){
    char ch;
    ull s = 0;
    while ((ch=getchar())=='\n' || ch==' '|| ch=='\r')
        ;
    while (ch>='0' && ch<='9'){
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s;
}
int main(){
    // clock_t sst = clock();
    n = getnum();
    s = getnum();
    REP(i,1,n)
    {
        a[i].fi = getnum();
        a[i].sc = i;
    }
    sort(a + 1, a + 1 + n, [](pair<ull, int> a, pair<ull, int> b) {
        return a > b;
    });
    REP(i,1,n){
        sum[i] = sum[i - 1] + a[i].fi;
    }
    dfs2(n);
    sort(ALL(fff));
    dfs(0);
    REP(i,1,n){
        printf("%d", vis[i]);
    }
    // puts("");
    // clock_t et = clock();
    // cout << (double)(et - sst) / CLOCKS_PER_SEC << endl;
    return 0;
}

