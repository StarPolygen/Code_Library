//CF 1117D
//矩阵快速幂加速 DP
//n，m(1e18) ；有一些魔法石，一个魔法石可以分裂成m个普通宝石，每个宝石站一个单位空间；问有多少序列使得占n个空间
//思路：普通石只能以m个一组的形式存在
//f(n)=f(n-1)+f(n-m)       加一个魔法石或者加m个普通石
//f(0)=f(1)=.....f(m-1)=1  只能都为魔法石#include<bits/stdc++.h>
#define ll long long
#define mod 1e9+7
using namespace std;
 
namespace matrix
{
    const int MOD = 1e9+7; 
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



int main() {
    ll N,M;
    scanf("%lld%lld",&N,&M);
    
    //原始矩阵
    Matrix<int> ori(M);
    for(int i=0;i<M;i++){
        ori[i][0]=1;
    }

    //转化矩阵
    Matrix<int> tran(M);
    for(int i=0;i<M;i++){
        if(i==0) tran[i][0]=tran[i][M-1]=1;
        else tran[i][i-1]=1;
    }
    tran =tran^(N-M+1);
    tran =tran*ori;

    if(N<M) printf("1\n");
    else if(N==M) printf("2\n");
    else printf("%d\n",tran[0][0]);

    return 0;
}