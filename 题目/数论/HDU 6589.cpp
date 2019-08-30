//母函数 NTT卷积
//对数组进行三种操作：1.用mod下前缀和替代数组的值  2.用隔2的mod下前缀和代替数组的值 3.用隔3个3个代替
//通过对母函数的分析可以发现 （每次操作后新的母函数）是（原序列的母函数）*ΣX^ki 其中k是类型 i是位置 因此由母函数的形式可得知 操作的顺序与结果无关
//因此可以对于每一种操作都统计次数 批量处理
//问题转化为快速求m次前缀和的问题
//可以发现m次前缀和后的结果序列 和原序列A的关系是   
//m次：c[1]*a[1]，c[1]*a[2]+c[2]*a[1]，c[1]*a[3]+c[2]*a[2]+c[3]*a[1]，c[1]*a[4]+c[2]*a[3]+c[3]*a[2]+c[4]*a[1]，c[1]*a[5]+c[2]*a[4]+c[3]*a[3]+c[4]*a[2]+c[5]*a[1]...
//可以发现是一个卷积的形式  C[i]=C(m+i-2,i-1) O(m)组合数预处理 之后NTT处理卷积即可


#include<bits/stdc++.h>
#define maxn 200020
using namespace std;
typedef long long ll;
const ll mod = 998244353;  //一般只有三种：98244353,1004535809,469762049 
const ll _g = 3;    //模数的原根 


//前置模板
inline ll bin(ll x, ll n,ll p) {
    ll ret = p != 1;
    for (x %= p; n; n >>= 1, x = x*x%p)
        if (n & 1) ret = ret*x%p;
    return ret;
}
inline ll get_inv(ll x, ll p) { return bin(x, p - 2, p); }



//NTT    NTT结果将会保存在第一个原始数组f内，并将原始数据覆盖掉
const int maxl = maxn<<2; 
int rev[maxl];
inline void NTT(int *a,int len,int f){//此处的len是已经对齐的，对齐工作在mul里完成
    for(int i=0;i<len;++i)if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int i=1;i<len;i<<=1){
        int w1=bin(_g,((mod-1)/(i<<1)*f+mod-1)%(mod-1),mod);
        for(int j=0;j<len;j+=(i<<1)){
            int w=1;
            for(int k=0;k<i;++k,w=1ll*w*w1%mod){
                int x1=a[j+k],x2=1ll*w*a[j+i+k]%mod;
                a[j+k]=(x1+x2)%mod;
                a[j+i+k]=(x1+mod-x2)%mod;
            }
        }
    }
    if(!(~f)){
        int invlen=get_inv(len,mod);
        for(int i=0;i<len;++i)a[i]=1ll*a[i]*invlen%mod;
    }
}
inline void mul(int *a,int *b,int n){//此处的参数n为原始数组的有用长度之和
    int len=1,bit=0;
    while(len<=n)len<<=1,++bit;
    for(int i=0;i<len;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    NTT(a,len,1),NTT(b,len,1);
    for(int i=0;i<len;++i)a[i]=1ll*a[i]*b[i]%mod;
    NTT(a,len,-1);
}

//NNT直接对原始数组操作，因此原始数组大小为maxl,最终结果在f内 
int f[maxl],g[maxl],arr[maxl];
inline void init(){
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
}


//预处理组合
inline void pre(int m,int n){
    g[1]=1;
    for(int i=2;i<=n;++i){
        g[i]=1ll*g[i-1]*(m+i-2)%mod*get_inv(i-1,mod)%mod;    //这里忘了乘以1ll wa了
    }
}
int main(){
    int T;scanf("%d",&T);
    int num1,num2,num3;
    while(T--){
        init();
        int n,m; scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i){
            scanf("%d",&f[i]);
            arr[i]=f[i];
        }

        //分别统计三种操作个数
        num1=num2=num3=0;
        for(int i=1;i<=m;++i){
            int tmp;
            scanf("%d",&tmp);
            if(tmp==1) ++num1;
            else if(tmp==2) ++num2;
            else ++num3;
        }


        //操作一
        pre(num1,n);
        mul(f,g,2*n+2);
        for(int i=2;i<=n+1;++i){
            arr[i-1]=f[i];
        }
        init();

        
        //操作二
        pre(num2,n); int tot=0;
        //mod2 为0
        for(int i=1;i<=n;++i){
            if(i%2==0) f[++tot]=arr[i];
        }
        mul(f,g,2*n+2);
        for(int i=2;i<=n+1;++i) arr[2*i-2]=f[i];
        init();

        //mod2 为1
        pre(num2,n); tot=0;
        for(int i=1;i<=n;++i){
            if(i%2==1) f[++tot]=arr[i];
        }
        mul(f,g,2*n+2);
        for(int i=2;i<=n+1;++i) arr[2*i-3]=f[i];
        init();


        //操作三
        pre(num3,n); tot=0;
        for(int i=1;i<=n;++i) if(i%3==0) f[++tot]=arr[i];
        mul(f,g,2*n+2);
        for(int i=2;i<=n+1;++i) arr[3*i-3]=f[i];
        init();

        pre(num3,n); tot=0;
        for(int i=1;i<=n;++i) if(i%3==1) f[++tot]=arr[i];
        mul(f,g,2*n+2);
        for(int i=2;i<=n+1;++i) arr[3*i-5]=f[i];
        init();

        pre(num3,n); tot=0;
        for(int i=1;i<=n;++i) if(i%3==2) f[++tot]=arr[i];
        mul(f,g,2*n+2);
        for(int i=2;i<=n+1;++i) arr[3*i-4]=f[i];
        init();



        ll ans=0;
        for(int i=1;i<=n;++i) ans=ans^(1ll*i*arr[i]);
        printf("%lld\n",ans);

    }
    return 0;
} 