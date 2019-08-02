//十进制快速幂(矩阵)   适用于n极其巨大 如10^10^6情况
//此时不需要使用高精度 也可以获得与普通快速幂（矩阵）相同的复杂度，即O(logn)快速幂 / O(k^3logn)矩阵快速幂

//所谓十进制快速幂，就是计算快速幂时，以10倍增而非2倍增，因此可以处理n极大的情况
//但是对于内部循环，仍然要以2倍增，否则会TLE，此时复杂度为O( log2(10) * log10(n) ) = O(log2(n))

//本题卡常： 如果用结构体内的默认初始化函数 就会TLE 手动赋值即可AC 启示：减少结构体方法的使用 
//          如果采取多余的取模和Long Long也会T                  启示: 减少不必的ll和取模 
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
ll MOD=0;
struct Matrix{
    ll m[2][2];
};
Matrix mul(Matrix a, Matrix b){
    Matrix res;
    res.m[0][0]=res.m[0][1]=res.m[1][1]=res.m[1][0]=0;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                res.m[i][j]=(res.m[i][j]+a.m[i][k]*b.m[k][j]%MOD)%MOD;
            }
        }
    }
    return res;
}
 
Matrix mpow(Matrix a, int t){
    Matrix res; res.m[0][0]=res.m[1][1]=1; res.m[1][0]=res.m[0][1]=0;
    for (; t; t >>= 1)
    {
        if (t & 1) res = mul(res, a);
        a = mul(a, a);
    }
    return res;
}
 
char s[1000010];
int x0,x1,a,b;
Matrix base;
Matrix tran;
Matrix ans;
signed main() {
     
    scanf("%d%d%d%d%s%lld",&x0,&x1,&a,&b,s,&MOD);
    base.m[0][0]=x1; base.m[1][0]=x0; base.m[1][0]=base.m[1][1]=0;
    tran.m[0][0]=a; tran.m[0][1]=b; tran.m[1][0]=1; tran.m[1][1]=0;
 
    //计算转移矩阵的n次矩阵
    ans.m[0][0]=ans.m[1][1]=1; ans.m[0][1]=ans.m[1][0]=0;
    int len=strlen(s);
    for(int i=len-1;i>=0;i--){
        if(s[i]!='0') {
            Matrix tmp = mpow(tran,s[i]-'0');
            ans = mul(ans, tmp);
        }
        tran=mpow(tran, 10);
    }
    ll res = (ans.m[1][0]*x1%MOD+ans.m[1][1]*x0%MOD)%MOD;
    printf("%lld\n",res);
    return 0;
}