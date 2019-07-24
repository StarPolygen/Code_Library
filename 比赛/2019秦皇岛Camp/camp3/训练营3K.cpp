//FFT 
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
#include <queue>
#include <complex>
#define ll long long
#define maxn 4000010


//n需补成 2 的幂 （n必须超过 a 和 b 的最高指数之和）
//卷积系数储存在a[i].real()中,作为整数使用时需要（ll）(a[i].real()+0.5) 
using namespace std;
typedef complex<double> cd;
//！！nlogn的最大长度，需要根据题意计算和修改	
const int maxl = 3600180;					
const double PI = acos(-1.0);
cd a[maxl],b[maxl];							//用于储存变换的中间结果
int rev[maxl];								//用于储存二进制反转的结果
void getrev(int bit){
    for(int i=0;i<(1<<bit);i++){			//高位决定二进制数的大小
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    }										//能保证(x>>1)<x,满足递推性质
}
void fft(cd* a,int n,int dft){				//变换主要过程
    for(int i=0;i<n;i++){					//按照二进制反转
        if(i<rev[i])						//保证只把前面的数和后面的数交换,(否则数组会被翻回来)
            swap(a[i],a[rev[i]]);
    }
    for(int step=1;step<n;step<<=1){		//枚举步长的一半
        cd wn=exp(cd(0,dft*PI/step));		//计算单位复根
        for(int j=0;j<n;j+=step<<1){		//对于每一块
            cd wnk(1,0);					//!!每一块都是一个独立序列,都是以零次方位为起始的
            for(int k=j;k<j+step;k++){		//蝴蝶操作处理这一块
                cd x=a[k];
                cd y=wnk*a[k+step];
                a[k]=x+y;
                a[k+step]=x-y;
                wnk*=wn;					//计算下一次的复根
            }
        }
    }
    if(dft==-1){							//如果是反变换,则要将序列除以n
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
	for(bit=1;(1<<bit)<len1+len2-1;bit++){ 
        s<<=1;						
    }
	for(int i=0;i<len1;i++){			
        a[i]=(double)(arr1[i]); 
    }
    for(int i=0;i<len2;i++){
    	b[i]=(double)(arr2[i]);
	}
	getrev(bit); fft(a,s,1); fft(b,s,1);
    for(int i=0;i<s;i++) a[i]*=b[i];	
    fft(a,s,-1);					    
}


int n1,n2;
int ans[maxl];
char s[maxl],t[maxl];
int  c1[maxl],c2[maxl];
void cal(char c){
    memset(c1,0,sizeof(c1));
    memset(c2,0,sizeof(c2));
    for (int i = 0; i < n1; i++) {
        if (s[i] == c) c1[i] = 1; 
        else c1[i] = 0;
        // printf("%d ",c1[i]);
    }
    // printf("\n");
	for (int i = 0; i < n2; i++) {
        if (t[i] == c) c2[i] = 1;
        else c2[i] = 0;
        // printf("%d ",c2[i]);
    }
    // printf("\n");
    getConv(c1,n1,c2,n2);
    for(int i=0; i<n1+n2-1;i++)
    ans[i]+=(int)(a[i].real()+0.5);
}
//以下是FFT实现高精度乘法(仅限正数)的代码，只需要将得到的系数按照十进制输出即可

int main(){
    ini();
    memset(s,0,sizeof(s));
    memset(t,0,sizeof(t));
    scanf("%s",s);	
    int len=strlen(s);
    n1=n2=len;
    for(int i=0;i<=len;i++){
        t[i]=s[i];
    }
    //处理s字符串，以便之后适配
    for (int i = 0; i < n1; i++) {
        if (s[i] == 'B') s[i] = 'A';
        else if (s[i] == 'A') s[i] = '0';
	}




    //翻转t字符串
	strrev(t);

    // printf("%s\n",s);
    // printf("%s\n",t);

    //FFT计算分别贡献
    cal('A'); 

    for (int i = n1-2; i >= 0; i--) 
    printf("%d\n",ans[i]);
    return 0;
}
