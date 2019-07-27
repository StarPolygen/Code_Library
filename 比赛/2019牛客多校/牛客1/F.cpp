//数学题
//当时猜结论 猜了若干次
//赛后需要补一下哈
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
struct NODE{
    ll x, y;
    NODE(){}
    NODE(ll x,ll y):x(x),y(y){}
} p1, p2, p3;
ll cross_product(NODE p0,NODE p1,NODE p2){
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}
int main(){
    int x1, y1, x2, y2, x3, y3;
    while(~scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3)){
        p1 = NODE(x1, y1);
        p2 = NODE(x2, y2);
        p3 = NODE(x3, y3);
        ll ans = cross_product(p1, p2, p3);
        printf("%lld\n", 11 * abs(ans));
    }
    return 0;
}