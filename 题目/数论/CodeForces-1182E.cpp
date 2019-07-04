//矩阵快速幂 好题
//乘法化为指数加法 推得线性递推式 矩阵快速幂解决

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1e9+7;
//矩阵快速幂 
namespace matrix
{
    const int MOD = 1e9+6;
    inline int __add__(int a, const int b) { a += b; return a < MOD ? a : a - MOD; }
    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }

    typedef unsigned long long ull;
    template <typename T>
    class Matrix
    {
    public:
        ull n;
        bool cyclic = false;
        vector<vector<T> > a;
        Matrix() {}
        Matrix(ull n) : n(n) { init(); }
        vector<T> &operator [] (ull i) { return a[i]; }
        Matrix<T> operator * (Matrix &b) const
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
                for (int i  = 0; i < n - 1; i++)
                {
                    res[i + 1][0] = res[i][n - 1];
                    for (int j = 0; j < n - 1; j++) res[i + 1][j + 1] = res[i][j];
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
            for (int i = 0; i < n; i++) res[i][i] = 1;
            Matrix<T> tmp = *this;
            for (; t; t >>= 1)
            {
                if (t & 1) res = res * tmp;
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
        void init() { a = vector<vector<T> >(n, vector<T>(n, 0)); }
    };
}
using matrix::Matrix;


//当相乘会爆long long 时需要配合快速乘使用  将乘法替换为快速乘 
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}

int main(){
    ll n,df1,df2,df3,c;
    scanf("%lld %lld %lld %lld %lld",&n,&df1,&df2,&df3,&c);
    if(n==1)        printf("%lld\n",df1%mod);
    else if(n==2)   printf("%lld\n",df2%mod);
    else if(n==3)   printf("%lld\n",df3%mod);
    else if(n==4)   printf("%lld\n",df1*df2%mod*df3%mod*c%mod*c%mod);
    else{
        //转化矩阵
        Matrix<int> a(3);
        a[0][0]=a[0][1]=a[0][2]=a[1][0]=a[2][1]=1;
        a=a^(n-4);

        //c矩阵转化
        Matrix<int> b(5);
        b[0][0]=b[0][1]=b[0][2]=b[0][3]=1;
        b[1][0]=b[2][1]=b[3][3]=b[3][4]=b[4][4]=1;
        b=b^(n-4);
        Matrix<int> tpc(5);
        tpc[4][0]=2; tpc[3][0]=8; tpc[2][0]=2; tpc[1][0]=6; tpc[0][0]=14;
        Matrix<int> tp(5);
        tp =b*tpc;
        int lc=tp[2][0];

        //f1,f3矩阵转化
        Matrix<int> f1(3);
        f1[2][0]=f1[1][0]=1;f1[0][0]=2;
        Matrix<int> tmp(3);
        tmp =a*f1;
        int l1=tmp[2][0];
        int l3=tmp[1][0];

        //f2矩阵转化
        Matrix<int> f2(3);
        f2[2][0]=1;f2[1][0]=2;f2[0][0]=3;
        tmp =a*f2;
        int l2=tmp[2][0];
        // printf("%d\n",lc);
        ll ans=bin(c,lc,mod)*bin(df1,l1,mod)%mod;
        ans=ans*bin(df2,l2,mod)%mod;
        ans=ans*bin(df3,l3,mod)%mod;
        printf("%lld\n",ans);
        


    
    }
    return 0;
}