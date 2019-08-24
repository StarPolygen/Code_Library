//贪心

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

priority_queue<pi, vector<pi>, greater<pi>> q;
pi c[N];

int main(){
    int _;
    for (scanf("%d", &_); _;_--){
        int n;
        scanf("%d", &n);
        while (!q.empty()) q.pop();
        ll ans = 0;
        FOR(i,n){
            int a, b;
            scanf("%d%d", &a, &b);
            c[i] = mp(b, a);
        }
        sort(c, c + n, [](pi a, pi b) {
            return a > b;
        });
        FOR(i,n){
            q.push(mp(c[i].fi, i));
        }
        FOR(i,n){
            int a = c[i].sc;
            pi now, skip = mp(-1, -1);
            while (!q.empty() && a){
                now = q.top();
                q.pop();
                if (now.sc==i){
                    skip = now;
                    continue;
                }
                if (now.fi>=a){
                    now.fi -= a;
                    ans += 1ll * a;
                    a = 0;
                }else{
                    a -= now.fi;
                    ans += 1ll * now.fi;
                    now.fi = 0;
                }
                if (now.fi){
                    q.push(now);
                }
            }
            if (~skip.sc){
                q.push(skip);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}