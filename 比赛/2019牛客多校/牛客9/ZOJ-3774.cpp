//斐波那契k次幂和3：
//递推通项 二次剩余 等比求和
//对mod的性质要求较高  但复杂度极小 O(k) 
//利用通项公式 借助二次剩余和逆元替代通项公式中的根式和除式 二项式系数展开 等比数列求和   
//仅适用于存在5的二次剩余和2的逆元的情况 对mod的性质要求较高  但复杂度非常小仅有O(2k)

//具体原理见solve()
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;

//所需参数
const int P=1000000009;             //本题mod
const int INV2=500000005;           //2对mod的逆元
const int SQRT5=383008016;          //5对mod的二次剩余  也就是模意义下的根号5
const int INVSQRT5=276601605;       //模意义下的1/根号5
const int A=691504013;              //斐波那契的特征方程两根之一  (1+√5)/2
const int B=308495997;              //斐波那契的特征方程两根之一  (1-√5)/2

//最大k值
const int N=100005;
 
ll n,K;
ll fac[N],inv[N];
ll pa[N],pb[N];
 
//预处理 阶乘逆元和 A B的r次幂  r：0~k
inline void Pre(int n){
  fac[0]=1; for (int i=1;i<=n;i++) fac[i]=fac[i-1]*i%P;
  inv[1]=1; for (int i=2;i<=n;i++) inv[i]=(P-P/i)*inv[P%i]%P;
  inv[0]=1; for (int i=1;i<=n;i++) inv[i]=inv[i]*inv[i-1]%P;
  pa[0]=1; for (int i=1;i<=n;i++) pa[i]=pa[i-1]*A%P;
  pb[0]=1; for (int i=1;i<=n;i++) pb[i]=pb[i-1]*B%P;
}
inline ll C(int n,int m){    //对于组合数 阶乘逆元预处理计算
  return fac[n]*inv[m]%P*inv[n-m]%P;
}


//快速幂和求逆元
inline ll Pow(ll a,ll b){
  ll ret=1;
  for (;b;b>>=1,a=a*a%P)
    if (b&1)
      ret=ret*a%P;
  return ret;
}inline ll Inv(ll x){  return Pow(x,P-2);}



//求解fibo前n项K次幂和
//原理：易得fibo通项公式，公式中的根号5和除式通过二次剩余和逆元代替，因此F(n)^k = (1/√5)^k ({[(1+√5)/2]^n - [(1-√5)/2]^n})^k
//      通项中的特征方程两根 模意义下分别为A和B 因此第n项Fibo的K次幂写作 F(n)^k =  INVSQRT5^K [A^n - B^n]^K
//      二项式定理展开获得   [A^n - B^n]^K = Ck0*(a^n)^k + Ck1*(a^n)^k-1*(-b^n) +... + Ckk*(-b^n)^k
//                                       =  Ck0*(a^k)^n + (-1)^1Ck1*(a^k-1)^n*(b)^n +... + Ckk*(b^k)^n 
//                                       =  Σ (-1)^r * C(k,r) * [a^(k-r)]^n *  [b^r]^n
//      对于每一个n都这样表示，那么相同的(-1)^r * C(k,r)对不同n合并后是等比数列，等比数列求这一项在1~n中的贡献和为：
//                                        (-1)^r * C(k,r) * t(t^n - 1)/(t-1)  其中t为 a^(k-r)* b^r
//      所以到了这里本题就明确了，枚举每一个r从0到k，依次计算统计贡献即可。
//      当然对于C(n,k)，我们可以阶乘预处理然后求逆元，至于A^r和B^r同样预处理，这样时间少很多。
//      对于t = 1的情况 不能带入等比数列求和公式（分母为0） 直接特判即可
inline void Solve(){
  ll Ans=0;
  for (int j=0;j<=K;j++){
    ll t=pa[K-j]*pb[j]%P,tem;
    tem=t==1?n%P:t*(Pow(t,n)-1+P)%P*Inv(t-1)%P;
    if (~j&1)
      Ans+=C(K,j)*tem%P,Ans%=P;
    else
      Ans+=P-C(K,j)*tem%P,Ans%=P;
  }
  Ans=Ans*Pow(INVSQRT5,K)%P;
  printf("%lld\n",Ans);
}
 
int main(){
  int T;
  Pre(100000);
  scanf("%d",&T);
  while (T--){
    scanf("%lld%lld",&n,&K);
    Solve();
  }
}
