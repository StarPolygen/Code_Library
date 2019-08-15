#include <bits/stdc++.h>
#define ll long long
using namespace std;

namespace matrix
{
    const ll MOD = 9223372036854775807;
    inline ll __add__(ll a, const ll b) { a += b; return a < MOD ? a : a - MOD; }
    inline ll __mul__(long long a, const ll b) { a *= b; return (ll) (a < MOD ? a : a - a / MOD * MOD); }

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
                for (ll k = 0; k < n; k++)
                    if (a[0][k])
                        for (ll j = 0; j < n; j++)
                            if (b[k][j])
                                res[0][j] = __add__(res[0][j], __mul__(a[0][k], b[k][j]));
                for (ll i  = 0; i < n - 1; i++)
                {
                    res[i + 1][0] = res[i][n - 1];
                    for (ll j = 0; j < n - 1; j++) res[i + 1][j + 1] = res[i][j];
                }
            }
            else
                for (ll k = 0; k < n; k++)
                    for (ll i = 0; i < n; i++)
                        if (a[i][k])
                            for (ll j = 0; j < n; j++)
                                res[i][j] = __add__(res[i][j], __mul__(a[i][k], b[k][j]));
            return res;
        }

        Matrix<T> operator^(ull t) const
        {
            assert(n >= 0);
            Matrix<T> res(n);
            res.cyclic = cyclic;
            for (ll i = 0; i < n; i++) res[i][i] = 1;
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
            for (ll i = 0; i < n; i++)
                for (ll j = 0; j < n; j++)
                    cout << a[i][j] << " \n"[j == n - 1];
        }

    private:
        void init() { a = vector<vector<T> >(n, vector<T>(n, 0)); }
    };
}
using matrix::Matrix;

int main(){
	ll p,q,n;//p:a+b q:ab 
	ll ans;
	while(true){
		if(scanf("%lld%lld%lld",&p,&q,&n)!=3) break;
		if(n==0) printf("2\n");
		else if(n==1) printf("%lld\n",p);
		else{
			Matrix<ll> mid(2);
			Matrix<ll> ans(2);
			mid[0][0]=0;mid[0][1]=1;mid[1][0]=-q;mid[1][1]=p;
			ans[0][0]=p;ans[0][1]=0;ans[1][0]=p*p-2*q;ans[1][1]=0;
			Matrix<ll> tmp=mid^(n-1);
			ans=tmp*ans;
			printf("%lld\n",ans[0][0]);
			
		}
		
		
		
		
	}
	
	return 0;
}
