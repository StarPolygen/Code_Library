//数论 唯一分解定理
//屡屡TLE 主要原因是分解质因数的模板缺少一个剪枝 if(prime[i] >x) break;
//新收获：由质因数 推得 所有因数模板
//优化：  分解质因数的模板新剪枝
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll a,b;


const int MAXSIZE=1e6+5; 
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
//前置模板：素数筛
//带指数 
ll factor[30], f_sz, factor_exp[30];
void get_factor(ll x) {
    f_sz = 0;
    ll t = sqrt(x + 0.5);
    for (ll i = 0; prime[i] <= t; ++i){
        if(prime[i] >x) break;
        if (x % prime[i] == 0) {
            factor_exp[f_sz] = 0;
            while (x % prime[i] == 0) {
                x /= prime[i];
                ++factor_exp[f_sz];
            }
            factor[f_sz++] = prime[i];
        }
    }
    if (x > 1) {
        factor_exp[f_sz] = 1;
        factor[f_sz++] = x;
    }
}
//求解因数对个数
ll getnum(){
    ll num=1;
    for(int i=0;i<f_sz;i++){
        num*=(factor_exp[i]+1);
    }
    return num/2;
}


ll ans=0;
void dfs(int cur,int n,long long num){ //第几个数，该数第几个，总共多少个数 ,是否组合数 
	if(cur>=n)
		return;
	dfs(cur+1,n,num);
	for(int i=1;i<=factor_exp[cur];i++){
		num*=factor[cur];
        if(num>=b) return; //当题目要求小于b的因数个数时
		ans+=1;
	    dfs(cur+1,n,num);
	}
}
ll getless(){
    ans=0;
    dfs(0,f_sz,1);
    if(b!=1) ans++;
    return ans;
}

int main() {
    Prime();
    int T; scanf("%d",&T);
    for(int i=1;i<=T;i++){
        scanf("%lld %lld",&a,&b);
        if(b>=sqrt(a)){
            printf("Case %d: 0\n",i); continue;
        }
        memset(factor,0,sizeof(factor)); memset(factor_exp,0,sizeof(factor_exp));
        get_factor(a);
        ll num=getnum();
        //debug1 成对个数
        // printf("num: %lld\n",num);
        //debug2 排除个数
        // printf("ans: %lld\n",getless());

        printf("Case %d: %lld\n",i,num-getless());
    }
    return 0;
}