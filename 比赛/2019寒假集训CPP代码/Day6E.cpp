#include<iostream>
int dp[70];
int sum[70];
int main(){
	for(int i=0;i<70;i++){
		dp[i]=sum[i]=0;
	}
	int n;
	dp[1]=1;
	dp[2]=1;
	dp[3]=1;
	sum[1]=1;sum[2]=2;sum[3]=3;
	for(int i=1;i<=n;i++){
		dp[i]=all[i-3]+1;
		sum[i]=sum[i-1]+dp[i];
	}
	while(~scanf("%d",&n)){
		printf("%d\n",sum[n]);
	}
	return 0;
}
