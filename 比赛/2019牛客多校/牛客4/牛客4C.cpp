//作者： 朱
//线段树 + 单调栈
// #pragma GCC optimize(2)
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define sc second
#define fi first
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
const int N = 3e6 + 5;
int n;
ll a[N], b[N], s[N], l[N], r[N];
stack<pair<int, int>> st;
ll mx[N * 4], mn[N * 4];
void up(int x){
    mx[x] = max(mx[x * 2], mx[2 * x + 1]);
    mn[x] = min(mn[2 * x], mn[2 * x + 1]);
}
void build(int x,int l,int r){
    if (l==r){
        mn[x] = mx[x] = s[l];
        return;
    }
    int mid = l + r >> 1;
    build(2 * x, l, mid);
    build(2 * x + 1, mid + 1, r);
    up(x);
}
ll queryMX(int x,int l,int r,int ql,int qr){
    if (ql<=l && qr>=r){
        return mx[x];
    }
    int mid = l + r >> 1;
    if(qr<=mid)
        return queryMX(2 * x, l, mid, ql, qr);
    else if (ql>mid)
        return queryMX(2 * x + 1, mid + 1, r, ql, qr);
    else {
        return max(queryMX(2 * x, l, mid, ql, qr), queryMX(2 * x + 1, mid + 1, r, ql, qr));
    }
}
ll queryMN(int x,int l,int r,int ql,int qr){
    if (ql<=l && qr>=r){
        return mn[x];
    }
    int mid = l + r >> 1;
    if (qr<=mid)
        return queryMN(2 * x, l, mid, ql, qr);
    else if (ql>mid)
        return queryMN(2 * x + 1, mid + 1, r, ql, qr);
    else
        return min(queryMN(2 * x, l, mid, ql, qr), queryMN(2 * x + 1, mid + 1, r, ql, qr));
}
int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n;i++)
    {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n;i++)
    {
        scanf("%lld", &b[i]);
        s[i] = s[i - 1] + b[i];
    }
    for (int i = 1; i <= n;i++)
    {
        while (!st.empty() && st.top().fi > a[i])
        {
            int pos = st.top().sc;
            r[pos] = i;
            st.pop();
        }
        st.push(mp(a[i], i));
    }
    while (!st.empty()){
        int pos = st.top().sc;
        r[pos] = n + 1;
        st.pop();
    }
    for (int i = n; i >= 1;i--)
    {
        while (!st.empty() && st.top().fi > a[i]){
            int pos = st.top().sc;
            l[pos] = i;
            st.pop();
        }
        st.push(mp(a[i], i));
    }
    while (!st.empty()){
        int pos = st.top().sc;
        l[pos] = 0;
        st.pop();
    }
    s[0] = 0;
    build(1, 0, n);
    ll ans = 0;
    bool fl = 0;
    ll mxs, mns, tmp;
    for (int i = 1; i <= n;i++)
    {
        int lr = l[i], rr = r[i];
        if (a[i]>0){
            mxs = queryMX(1, 0, n, i, rr - 1);
            mns = queryMN(1, 0, n, lr, i - 1);
            tmp= a[i] * (mxs - mns);
            if (!fl) {
                ans = tmp;
                fl = 1;
            }else{
                ans = max(tmp, ans);
            }
        }else{
            mns = queryMN(1, 0, n, i, rr - 1);
            mxs = queryMX(1, 0, n, lr, i - 1);
            tmp = a[i] * (mns - mxs);
            if (!fl){
                ans = tmp;
                fl = 1;
            }else{
                ans = max(ans, tmp);
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}