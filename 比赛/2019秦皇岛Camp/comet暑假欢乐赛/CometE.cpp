#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;

namespace matrix
{
const int MOD = 1e9 + 7;
inline int __add__(int a, const int b)
{
    a += b;
    return a < MOD ? a : a - MOD;
}
inline int __mul__(long long a, const int b)
{
    a *= b;
    return (int)(a < MOD ? a : a - a / MOD * MOD);
}

typedef unsigned long long ull;
template <typename T>
class Matrix
{
public:
    ull n;
    bool cyclic = false;
    vector<vector<T>> a;
    Matrix() {}
    Matrix(ull n) : n(n) { init(); }
    vector<T> &operator[](ull i) { return a[i]; }
    Matrix<T> operator*(Matrix &b) const
    {
        Matrix<T> res(n);
        if (cyclic)
        {
            res.cyclic = true;
            for (int k = 0; k < n; k++)
                if (a[0][k])
                    for (int j = 0; j < n; j++)
                        if (b[k][j])
                            res[0][j] = __add__(res[0][j], __mul__(a[0][k], b[k][j]));
            for (int i = 0; i < n - 1; i++)
            {
                res[i + 1][0] = res[i][n - 1];
                for (int j = 0; j < n - 1; j++)
                    res[i + 1][j + 1] = res[i][j];
            }
        }
        else
            for (int k = 0; k < n; k++)
                for (int i = 0; i < n; i++)
                    if (a[i][k])
                        for (int j = 0; j < n; j++)
                            res[i][j] = __add__(res[i][j], __mul__(a[i][k], b[k][j]));
        return res;
    }

    Matrix<T> operator^(ull t) const
    {
        assert(n >= 0);
        Matrix<T> res(n);
        res.cyclic = cyclic;
        for (int i = 0; i < n; i++)
            res[i][i] = 1;
        Matrix<T> tmp = *this;
        for (; t; t >>= 1)
        {
            if (t & 1)
                res = res * tmp;
            tmp = tmp * tmp;
        }
        return res;
    }

    void print()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cout << a[i][j] << " \n"[j == n - 1];
    }

private:
    void init() { a = vector<vector<T>>(n, vector<T>(n, 0)); }
};
} // namespace matrix
using matrix::Matrix;

ll bin(ll x, ll n, ll mod)
{
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1)
            ret = ret * x % mod;
    return ret;
}
inline ll get_inv(ll x, ll p) { return bin(x, p - 2, p); }

int main()
{
    ll d, k;
    scanf("%lld %lld", &d, &k);

    Matrix<ll> arr(k + 1);
    Matrix<ll> ac(k + 1);
    Matrix<ll> ans(k + 1);
    for (int i = 0; i < k; i++)
    {
        arr[i][0] = k;
    }
    arr[k][0] = 1;
   
    ll kinv = get_inv(k, mod);

    for (int i = 0; i < k; i++)
    {
        ac[0][i] = kinv;
    }
    ac[0][k] = 1;
    for (int i = 1; i < k; i++)
    {
        ac[i][i - 1] = 1;
    }
    ac[k][k] = 1;
    
    ac = ac ^ (d - k);
    ans = ac * arr;
    if (d > k)
        printf("%lld\n", ans[0][0]);
    else
        printf("%lld\n", k);
    return 0;
}