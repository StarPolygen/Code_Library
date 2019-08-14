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
const double eps=1e-8;
const double PI=acos(-1.0);
int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }



pair<pi,int> a[100010];
char s[100100][11];

int main() {
    int T,p,t;
    scanf("%d", &T);
    while(T--){
        int n, d;
        scanf("%d %d", &n, &d);
        double rt = 0.1 * n * d;
        double sy = fmod(rt, 1);
        
        int tot = 0;
        for (int i = 1; i <= n;++i){
            scanf("%s", s[i]);
            scanf("%d%d", &p, &t);
            a[++tot] = mp(mp(-p, t),i);
        }
        if(sgn(sy-0.5)!=0){
            printf("Quailty is very great\n");
            continue;
        }
        sort(a + 1, a + n + 1);
        int mc = ceil(rt);
        if(mc>n) {
            printf("Quailty is very great\n");
            continue;
        }
        int p1 = a[mc - 1].fi.fi; int t1=a[mc - 1].fi.sc;
        int p2 = a[mc].fi.fi; int t2=a[mc].fi.sc;
        if(p1==p2 && t1==t2){
            printf("Quailty is very great\n");
            continue;
        }
        else{
            printf("%s\n", s[a[mc].sc]);
        }
    }
    return 0;
}