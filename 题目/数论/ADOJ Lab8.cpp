
//ADOJ Lab8
// FFT + 原根 
//利用原根的性质 将乘积同余式转化为加法 FFT 
//代码经过修改 加入了多testcase 
#include <bits/stdc++.h>
#define ll long long
#define maxn 100010
#include <complex>
using namespace std;

int N,P;

//素数筛 
const int MAXSIZE=maxn; 
int Mark[MAXSIZE];     //prime[0]起 
int prime[MAXSIZE];    //判断是否是一个素数  Mark 标记数组 index 素数个数  
int Prime(){	
	int index=0;
    for (int i = 2; i < MAXSIZE; i++){
        if(Mark[i]) continue;//如标记则跳过  
        prime[index++] = i;//否则得到一个素数
        for (int j = i + i; j < MAXSIZE; j += i) Mark[j] = 1;//标记目前得到的素数的i倍为非素数
    }
    return index;
}

//快速幂 
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}


//分解质因数
ll factor[30], f_sz;
void get_factor(ll x) {
    f_sz = 0;
    ll t = sqrt(x + 0.5);
    for (ll i = 0; prime[i] <= t; ++i)
        if (x % prime[i] == 0) {
            factor[f_sz++] = prime[i];
            while (x % prime[i] == 0) x /= prime[i];
        }
    if (x > 1) factor[f_sz++] = x;
} 


//寻找原根
ll find_smallest_primitive_root(ll p) {
    get_factor(p - 1);
    for(int i=2; i<p; i++) {
        bool flag = true;
        for (int j=0; j<f_sz; j++)
            if (bin(i, (p - 1) / factor[j], p) == 1) {
                flag = false;
                break;
            }
        if (flag) return i;
    }
    assert(0); return -1;
} 


//处理原根指数和余数的关系 
int pw[maxn];	//pw是余数对应的指数
int cnt[maxn];  //cnt是不同指数出现的次数 
int rmd[maxn];  //rnk是指数对应的余数


//FFT  
//n需补成 2 的幂 （n必须超过 a 和 b 的最高指数之和）
typedef complex<double> cd;	
const int maxl = 3600180;			//nlogn的最大长度，需要修改
const double PI = acos(-1.0);
cd a[maxl],b[maxl];					//用于储存变换的中间结果
int rev[maxl];						//用于储存二进制反转的结果
void getrev(int bit){
    for(int i=0;i<(1<<bit);i++){	//高位决定二进制数的大小
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    }								//能保证(x>>1)<x,满足递推性质
}
void fft(cd* a,int n,int dft){		//变换主要过程
    for(int i=0;i<n;i++){			//按照二进制反转
        if(i<rev[i])				//保证只把前面的数和后面的数交换,(否则数组会被翻回来)
            swap(a[i],a[rev[i]]);
    }
    for(int step=1;step<n;step<<=1){//枚举步长的一半
        cd wn=exp(cd(0,dft*PI/step));//计算单位复根
        for(int j=0;j<n;j+=step<<1){//对于每一块
            cd wnk(1,0);			//!!每一块都是一个独立序列,都是以零次方位为起始的
            for(int k=j;k<j+step;k++){//蝴蝶操作处理这一块
                cd x=a[k];
                cd y=wnk*a[k+step];
                a[k]=x+y;
                a[k+step]=x-y;
                wnk*=wn;			//计算下一次的复根
            }
        }
    }
    if(dft==-1){					//如果是反变换,则要将序列除以n
        for(int i=0;i<n;i++)
            a[i]/=n;
    }
}
void ini(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(rev,0,sizeof(rev));
}
void getConv(int * arr1, ll len1, int * arr2, ll len2){
	ini();
	int bit=1, s=2;
	for(bit=1;(1<<bit)<len1+len2-1;bit++){//找到可容纳这两个数的乘积的2次幂 
        s<<=1;						
    }
	for(int i=0;i<len1;i++){			//系数分别装入a，b 
        a[i]=(double)(arr1[i]); 
    }
    for(int i=0;i<len2;i++){
    	b[i]=(double)(arr2[i]);
	}
	getrev(bit); fft(a,s,1); fft(b,s,1);//DFT
    for(int i=0;i<s;i++) a[i]*=b[i];	//对应相乘
    fft(a,s,-1);					    //IDFT
}




ll output[maxn];
int arr[maxn];


void init(){
	memset(output,0,sizeof(output));
	memset(pw,0,sizeof(pw));
	memset(cnt,0,sizeof(cnt));
	memset(rmd,0,sizeof(rmd));
}
int main(){
	Prime();
	int T;
	scanf("%d",&T);
	while(T--){
		init();
		scanf("%d%d",&N,&P);
		ll rt=find_smallest_primitive_root(P);//原根 
		for(int i=1;i<=N;i++){
			scanf("%d",&arr[i]);
		}
		ll rem = 1;  
	    for(int i=0;i<=P-2;++i){    //统计指数与余数的对应关系      
	        pw[rem] = i;	 		//一共只有[0,P-2],P-1个
	        rmd[i]= rem;	 
	        rem = rem*rt%P;
	    }
	
		for(int i=1;i<=N;i++){		//统计各指数出现的次数
			int tmp=arr[i]%P;
			if(tmp==0) continue;    //原根无法枚举%p=0的情况 因此卷积中不考虑0的贡献
	        cnt[pw[tmp]]++;
		} 
		
		
		getConv(cnt,P-1,cnt,P-1);
		
		for(int i=0; i<=2*P-4; i++){
			output[i%(P-1)]+=(ll)(a[i].real()+0.5);
		}
		
		ll tot = 1ll*N*N;
		for(int i=0;i<=P-2;i++){
			tot-=output[i];
		} 
		printf("%lld\n",tot);
		for(int i=1;i<=P-1;i++){
			printf("%lld\n",output[pw[i]]);
		}
	}
	
	return 0;
} 
