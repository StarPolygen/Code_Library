//同余 不等式 辗转相除 

//a/b=x(mod p) 已知x、p的值， 求存在a使得a<b的最小的b值   (p质数 3~1e15， 1<x<p ab均为正数)
//化简：题目相当于 a≡bx(modp)  a = bx-cp 化简得p/x ≤ b/c ≤ p/(x-1)
//经典模型： 以上问题是一个经典的问题: 应用辗转相除法 可以求出满足p/x ≤ b/c ≤ p/(x-1)最小的b、c

#include<bits/stdc++.h>
#define ll long long
using namespace std;

//辗转相除求最小x,y 满足  pa/pb ≤ x/y ≤ qa/qb
void gao(ll pa, ll pb, ll qa, ll qb, ll &x, ll &y){//  pa/pb ≤ x/y ≤ qa/qb
    ll z = (pa + pb -1) / pb;  //求左边界的上取整
    if( z <= qa / qb) {  //若小于等于右边界，代表两边界中间存在整数z满足条件，则直接返回x=z y=1
        x = z;
        y = 1;
        return;
    }
    pa -= (z - 1) * pb;  qa -= (z - 1) * qb; //否则两端的边界分数之间不存在整数z，则同时减去整数部分
    //并对整个式取倒数化为类似问题递归求解
    gao(qb, qa, pb, pa, y, x);
    x += (z - 1) * y;  //得到初始的x
}


ll x,p,b,c;
int main() {
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%lld %lld",&p,&x);
        gao(p, x, p, x-1, b, c);  //p/x ≤ b/c ≤ p/(x-1)最小的b、c
        ll a = b * x - p * c;     //计算a
        printf("%lld/%lld\n", a, b);

    }
    return 0;
}
