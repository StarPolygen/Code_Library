//线段树
//Arthor: 被坑的BigBang_019
// #pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define fi first
#define sc second
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
const int N = 1e5 + 5;
const int R = 1e9;

ll c[N];
int tot;
ll d[N];
map<int, ll> hn;
vector<ll> b, H;

struct NODE{
    int h;
    ll c, p;
    NODE(){}
    NODE(ll h, ll c, ll p) : h(h), c(c), p(p){}
} a[N];

void init(){
    b.clear();
    hn.clear();
    H.clear();
    memset(c, 0, sizeof(c));
    memset(d, 0, sizeof(d));
}
void init_hash(){
    sort(H.begin(), H.end());
    H.erase(unique(H.begin(), H.end()), H.end());
    sort(H.begin(), H.end(), [](ll a, ll b) {
        return a > b;
    });
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    tot = b.size();
}
int has(ll x){
    return lower_bound(b.begin(), b.end(), x) - b.begin() + 1;
}
int lb(int x) { return x & -x; }
void add1(int x,ll v){
    for (int i = x; i <= tot; i += lb(i))
    {
        c[i] += v;
    }
}
ll query1(int x){
    if (x<=0)
        return 0;
    ll sum = 0;
    for (int i = x; i > 0; i -= lb(i))
    {
        sum += c[i];
    }
    return sum;
}
void add2(int x,ll v){
    for (int i = x; i <= tot; i += lb(i))
    {
        d[i] += v;
    }
}
ll query2(int x){
    if (x<=0)
        return 0;
    ll sum = 0;
    for (int i = x; i > 0; i -= lb(i))
    {
        sum += d[i];
    }
    return sum;
}
int main(){
    int n;
    while (~scanf("%d",&n)){
        ll sum = 0;
        init();
        for (int i = 1; i <= n;i++)
        {
            int h;
            ll c, p;
            scanf("%d%lld%lld", &h, &c, &p);
            H.pb(h);
            hn[h] += p;
            a[i] = NODE(h, c, p);
            b.pb(c);
            sum += 1ll * p;
        }
        init_hash();
        sort(a + 1, a + 1 + n, [](NODE a, NODE b) {
            return a.h > b.h;
        });
        for (int i = 1; i <= n; i++)
        {
            add1(has(a[i].c), a[i].p);
            add2(has(a[i].c), a[i].p * a[i].c);
        }
        ll ans = -1;
        int now = 0;
        ll high = 0;
        ll cut = 0, last;
        for (int h : H)
        {
            last = cut;
            high = 0;
            vector<NODE> cur;
            while (now < n && a[now + 1].h >= h){
                now++;
                cut += a[now].p * a[now].c;
                cur.pb(a[now]);
                high += a[now].p;
            }
            ll dif;
            ll cost = last;
            if (sum/2==high)
                dif = 1 + (sum & 1);
            else if (sum&1==0){
                dif = sum - 2 * high + 2;
            }else {
                dif = sum - 2 * high + 1;
            }
            if (dif>0){
                int l = 1, r = n, mid, an = -1;
                while (l<=r){
                    mid = l + r >> 1;
                    ll tmp = query1(mid);
                    if (tmp<=dif){
                        l = mid + 1;
                        an = mid;
                    }else{
                        r = mid - 1;
                    }
                }
                if (an==-1)
                    an = 0;
                ll tmp1 = query2(an);
                ll tmp2 = (dif - query1(an)) * b[an];
                cost += tmp1 + tmp2;
            }
            for (NODE t : cur)
            {
                add1(has(t.c), -t.p);
                add2(has(t.c), -t.p * t.c);
            }
            sum -= high;
            ans = ~ans ? min(ans, cost) : cost;
        }
        printf("%lld\n", ans);
    }
    return 0;
}