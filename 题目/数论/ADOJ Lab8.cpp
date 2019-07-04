
//ADOJ Lab8
// FFT + ԭ�� 
//����ԭ�������� ���˻�ͬ��ʽת��Ϊ�ӷ� FFT 
//���뾭���޸� �����˶�testcase 
#include <bits/stdc++.h>
#define ll long long
#define maxn 100010
#include <complex>
using namespace std;

int N,P;

//����ɸ 
const int MAXSIZE=maxn; 
int Mark[MAXSIZE];     //prime[0]�� 
int prime[MAXSIZE];    //�ж��Ƿ���һ������  Mark ������� index ��������  
int Prime(){	
	int index=0;
    for (int i = 2; i < MAXSIZE; i++){
        if(Mark[i]) continue;//����������  
        prime[index++] = i;//����õ�һ������
        for (int j = i + i; j < MAXSIZE; j += i) Mark[j] = 1;//���Ŀǰ�õ���������i��Ϊ������
    }
    return index;
}

//������ 
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}


//�ֽ�������
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


//Ѱ��ԭ��
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


//����ԭ��ָ���������Ĺ�ϵ 
int pw[maxn];	//pw��������Ӧ��ָ��
int cnt[maxn];  //cnt�ǲ�ָͬ�����ֵĴ��� 
int rmd[maxn];  //rnk��ָ����Ӧ������


//FFT  
//n�貹�� 2 ���� ��n���볬�� a �� b �����ָ��֮�ͣ�
typedef complex<double> cd;	
const int maxl = 3600180;			//nlogn����󳤶ȣ���Ҫ�޸�
const double PI = acos(-1.0);
cd a[maxl],b[maxl];					//���ڴ���任���м���
int rev[maxl];						//���ڴ�������Ʒ�ת�Ľ��
void getrev(int bit){
    for(int i=0;i<(1<<bit);i++){	//��λ�������������Ĵ�С
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    }								//�ܱ�֤(x>>1)<x,�����������
}
void fft(cd* a,int n,int dft){		//�任��Ҫ����
    for(int i=0;i<n;i++){			//���ն����Ʒ�ת
        if(i<rev[i])				//��ֻ֤��ǰ������ͺ����������,(��������ᱻ������)
            swap(a[i],a[rev[i]]);
    }
    for(int step=1;step<n;step<<=1){//ö�ٲ�����һ��
        cd wn=exp(cd(0,dft*PI/step));//���㵥λ����
        for(int j=0;j<n;j+=step<<1){//����ÿһ��
            cd wnk(1,0);			//!!ÿһ�鶼��һ����������,��������η�λΪ��ʼ��
            for(int k=j;k<j+step;k++){//��������������һ��
                cd x=a[k];
                cd y=wnk*a[k+step];
                a[k]=x+y;
                a[k+step]=x-y;
                wnk*=wn;			//������һ�εĸ���
            }
        }
    }
    if(dft==-1){					//����Ƿ��任,��Ҫ�����г���n
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
	for(bit=1;(1<<bit)<len1+len2-1;bit++){//�ҵ����������������ĳ˻���2���� 
        s<<=1;						
    }
	for(int i=0;i<len1;i++){			//ϵ���ֱ�װ��a��b 
        a[i]=(double)(arr1[i]); 
    }
    for(int i=0;i<len2;i++){
    	b[i]=(double)(arr2[i]);
	}
	getrev(bit); fft(a,s,1); fft(b,s,1);//DFT
    for(int i=0;i<s;i++) a[i]*=b[i];	//��Ӧ���
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
		ll rt=find_smallest_primitive_root(P);//ԭ�� 
		for(int i=1;i<=N;i++){
			scanf("%d",&arr[i]);
		}
		ll rem = 1;  
	    for(int i=0;i<=P-2;++i){    //ͳ��ָ���������Ķ�Ӧ��ϵ      
	        pw[rem] = i;	 		//һ��ֻ��[0,P-2],P-1��
	        rmd[i]= rem;	 
	        rem = rem*rt%P;
	    }
	
		for(int i=1;i<=N;i++){		//ͳ�Ƹ�ָ�����ֵĴ���
			int tmp=arr[i]%P;
			if(tmp==0) continue;    //ԭ���޷�ö��%p=0����� ��˾���в�����0�Ĺ���
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
