//斐波那契k次幂和2:
//fibo循环节  CRT
//本题mod数为1E9 其循环节为1E9+5E8 不可接受
//但由于模并非质数 因此将其分解质因数 由于每个质因数分别拥有较小的循环节 可以计算在mod各个质因数意义下的答案 
//最后通过中国剩余定理 即可求得模mod意义下的结果 复杂度Omax(循环节logk)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, j, k) for (int i = int(j); i <= int(k); ++ i)
const ll p1 = 1953125;
const ll p2 = 512;
ll qpow(ll a, ll b, ll p) {
    ll c = 1; a %= p;
    while (b) {
        if (b & 1) c = c * a % p;
        a = a * a % p; b >>= 1;
    }
    return c;
}   
void exgcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if (!b) {
        d = 1; x = 1; y = 0;
    }
    else {
        exgcd(b, a % b, d, y, x);
        y -= (a / b) * x;
    }
}
  
ll CRT(ll *a, ll *m, int n) {
    ll A = a[1], M = m[1], d, x, y, M2;
    rep(i, 2, n) {  // k1 * m1 + k2 * m2 = a2 - a1
        exgcd(M, m[i], d, x, y);
        if ((a[i] - A) % d) return -1;
        M2 = M / d * m[i];
        x = (a[i] - A) / d * x % m[i];
        A = (A + x * M % M2) % M2;
        if (A < 0) A += M2;
        M = M2;
    }
    return A;
}
ll inv(ll a, ll p) {
    ll d, x, y;
    exgcd(a, p, d, x, y);
    return (x % p + p) % p;
}
  
int main() {
    ll n, m;
    cin >> n >> m;
    if (n == 0) { cout << 0 << endl; return 0; } 
    

    //分别计算Fibo模 2^9 和 5^9 的循环节
    vector<ll> f1; f1.push_back(0); f1.push_back(1);
    ll t0 = 0, t1 = 1, t2, tmp;
    for (int i = 2; ; ++ i) {
        t2 = (t1 + t0) % p1;
        tmp = qpow(t2, m, p1);
        if (tmp == 1 && f1.back() == 0) {
            break;
        }
        f1.push_back(tmp);
        t0 = t1;
        t1 = t2;
    }
  
    vector<ll> f2; f2.push_back(0); f2.push_back(1);
    t0 = 0, t1 = 1;
    for (int i = 2; ; ++ i) {
        t2 = (t1 + t0) % p2;
        tmp = qpow(t2, m, p2);
        if (t2 == 1 && f2.back() == 0) {
            break;
        }
        f2.push_back(tmp);
        t0 = t1;
        t1 = t2;
    }
    int cyc1 = f1.size() - 1, cyc2 = f2.size() - 1;
  

    //计算在模 2^9  和   5^9 意义下的答案
    rep(i, 1, cyc1) f1[i] = (f1[i] + f1[i - 1]) % p1;
    rep(i, 1, cyc2) f2[i] = (f2[i] + f2[i - 1]) % p2;
    ll a[3], pp[3];
    a[1] = (f1[n % cyc1] + 1ll * f1[cyc1 - 1] * (n / cyc1) % p1) % p1; pp[1] = p1;
    a[2] = (f2[n % cyc2] + 1ll * f2[cyc2 - 1] * (n / cyc2) % p2) % p2; pp[2] = p2; 
    // cout << f1[n % cyc1] << ' ' << f2[n % cyc2] << endl;

    //结合两者  使用中国剩余定理求模 1E9 的答案
    cout << CRT(a, pp, 2) << endl;
    // cout << f1.size() << ' ' << f2.size() << endl;
    return 0;
}