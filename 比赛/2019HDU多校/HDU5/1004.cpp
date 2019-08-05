//模拟 计算几何
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define fi first
#define sc second
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pi;
const int N = 2e6 + 5;
const int MOD = 1e9 + 7;
ll C;
int n;
ll gcd(ll a,ll b){ return (b ? gcd(b, a % b) : a); }
struct LINE{
    ll a, b;
    ll s, m;
    LINE(){}
    LINE(ll a, ll b) : a(a), b(b) {
        s = -b;
        m = a;
        ll d = gcd(abs(s), abs(m));
        s /= d;
        m /= d;
        if (m<0){
            m *= -1;
            s *= -1;
        }
    }
    bool operator < (const LINE &b ) const {
        return s * b.m < b.s * m;
    }
};
vector<LINE> line;
vector<pi> ans;
int main(){
    int _;
    for (scanf("%d", &_); _;_--)
    {
        line.clear();
        ans.clear();
        scanf("%d%lld", &n, &C);
        for (int i = 1; i <= n;i++)
        {
            ll a, b;
            scanf("%lld%lld", &a, &b);
            line.pb(LINE(a, b));
        }
        sort(line.begin(), line.end());

        ll A = 0, B = 0;
        bool fl = 1;
        for (LINE l : line)
        {
            A += -l.a;
            B += -l.b;
        }

        for (int i = 0; i < line.size();i++)
        {
            if (A==0){
                if (C==B){
                    fl = 0;
                    break;
                }
                continue;
            }
            ll m = A, s = C - B;
            if (m<0){
                m *= -1;
                s *= -1;
            }
            if (s*line[i].m<=m*line[i].s){
                if (i==0 || line[i-1].s*m<line[i-1].m*s){
                    ans.pb(mp(s, m));
                }
            }
            A += 2 * line[i].a;
            B += 2 * line[i].b;
        }
        if (fl){
            ll m = A, s = C - B;
            if (m<0){
                m *= -1;
                s *= -1;
            }
            if (line[line.size()-1].s*m<line[line.size()-1].m*s){
                ans.pb(mp(s, m));
            }
            printf("%d", ans.size());
            sort(ans.begin(), ans.end(), [](pi a, pi b) {
                return a.fi * b.sc < a.sc * b.fi;
            });
            for (pi p : ans)
            {
                ll a = p.fi, b = p.sc;
                ll d = gcd(abs(a), abs(b));
                if (b/d<0){
                    d *= -1;
                }
                printf(" %lld/%lld", a / d, b / d);
            }
        }else {
            printf("-1");
        }
        puts("");
    }
    return 0;
}