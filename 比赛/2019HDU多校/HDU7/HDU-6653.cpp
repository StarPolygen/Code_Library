//大讨论
#include <bits/stdc++.h>
#define ll long long
using namespace std;
 
 
ll a, b, x, y;

//基础子问题 前方或左方
ll solve1(ll x) {
    if (x <= 0) return 0;
    ll ans = min(a, b) * x;
    return ans;
}

//当前位置的正上下左右  采取策略
ll zbz1(ll x, ll y) {
    ll ans = solve1(x-1);
    return ans;
}
ll zbz2(ll x, ll y) {  
    ll ans = a + solve1(1-x);
    ans = min(ans, solve1(-x));
    return ans;
}
ll zbz3(ll x, ll y) { 
    ll ans = solve1(y);
    return ans;
}
ll zbz4(ll x, ll y) { return solve1(-1-y);}
 
//象限1234 以正上下左右为子问题决策
ll xiangxian1(ll x, ll y) {
    if (y == 0) return zbz1(x, y);
    else if (x == 0) return zbz3(x, y);
    ll ans = 1e18;
    if (y <= x) {
        ans = y * a + zbz1(x-y, 0);
        ans = min(ans, b + (y-1) * a + zbz1(x-y+1, 0));
    } else {
        ans = b + (x-1) * a + zbz2(x-y, 0);
        ans = min(ans, (x - 1) * a + zbz2(x-y-1, 0));
        
    }
    ans = min(ans, (y) * b + zbz1(x, 0));
    ans = min(ans, (x-1) * b + zbz2(-y, 0));
 
    return ans;
}
 
ll xiangxian2(ll x, ll y) {
    if (y == 0) return zbz2(x, y);
    else if (x == 0) return zbz3(x, y);
    ll ans = xiangxian1(y, 1-x) + a;
    ans = min(ans, xiangxian1(y+1, -x));
    return ans;
}
 
ll xiangxian4(ll x, ll y) {
    ll ans = xiangxian1(-y, x-1);
    ans = min(ans, a * 3 + xiangxian1(1-y, x));
    return ans;
}
 
ll xiangxian3(ll x, ll y) {
    ll ans = a + xiangxian2(y, -1-x);
    ans = min(ans, xiangxian1(-x+1, -y-1));
    return ans;
}
 
int main() {
    int t;   scanf("%d", &t);
    for (int kk=0; kk<t; ++kk)
    {
        scanf("%lld%lld%lld%lld", &a, &b, &x, &y);
        ll ans = 0;
        //大讨论
        //正上下左右 在坐标轴上
        if (x > 0 && y == 0) ans = zbz1(x, y);
        else if (x < 0 && y == 0) ans = zbz2(x, y);
        else if (x == 0 && y > 0) {  ans = zbz3(x, y); }
        else if (x == 0 && y < 0) ans = zbz4(x, y);
        //否则按照在1234象限一一讨论
        else if (x > 0 && y > 0) ans = xiangxian1(x, y);
        else if (x < 0 && y > 0) ans = xiangxian2(x, y);
        else if (x < 0 && y < 0) ans = xiangxian3(x, y);
        else
            ans = xiangxian4(x, y);
        printf("%lld\n", ans);
    }
    return 0;
}