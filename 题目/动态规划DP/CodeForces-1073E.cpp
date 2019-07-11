//数位DP 状态压缩
//不同于一般的统计个数 本题统计贡献 因此需要保存两维
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

int arr[20];//上界数的数位拆分结果
struct Point{
	ll num,sum;
	Point(){num = -1;sum = 0;};
	Point(ll num, ll sum):num(num),sum(sum){}
}dp[20][1025];  //dp[len][x]: 当前有len位数字还不确定，在此之前0~9每个数字出现的状态为x
ll pdd[20];

ll a,b,k;
 
Point dfs(int pos,int state,bool lead,bool limit)
{
    //个位数时  满足条件的个数仅为一,而贡献已被统计过
    if(pos<=-1) return lead?Point(0,0):Point(1,0); 
    //记忆化：统计过且未达上界 直接返回
	if(!lead && !limit &&dp[pos][state].num!=-1) return dp[pos][state];
	
    //limit需要单独计算  或之前未统计过需要重新计算
	int up = limit?arr[pos]:9;
	Point ans(0,0); //初始化ans
	for(int i=0;i<=up;i++){//套路：上界约束

		Point next(0,0);
		if(!((state>>i)&1) && !( lead && i==0)){        //状态转移
			int n_state = state|1<<i;
			if(__builtin_popcountll(n_state)>k) continue;//剪枝：跳过错误状态
			next = dfs(pos-1,n_state, lead && i==0,i==up && limit);
		}else{
			next = dfs(pos-1,state, lead && i==0,i==up && limit);
        }
		ans.num = (ans.num+next.num)%mod;               //统计贡献：符合条件的个数增加
		ans.sum = (ans.sum+next.sum+pdd[pos]*i%mod*next.num%mod)%mod;//当前数位的贡献增加

	}

    //记录
	if(!lead && !limit) dp[pos][state] = ans;           //如果这一位 不含上界或前导 则作为完整的数 可以记录下来  
	return ans;
}
 
ll solve(ll x){
	int i=0;
	while(x>0){
		arr[i++] = x%10;
		x/=10;
	}
	Point ans = dfs(i-1,0,true,true);
	return ans.sum;
}
 
void init(){
	memset(pdd,0,sizeof(pdd));
    memset(dp,0,sizeof(dp));
}

int main(){
	pdd[0]=1;
	for(int i=1;i<20;++i) pdd[i]=pdd[i-1]*10%mod;
	scanf("%lld%lld%lld",&a,&b,&k);
    printf("%lld\n",(solve(b)-solve(a-1)+mod)%mod);
	return 0;	
}