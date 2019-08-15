#include <bits/stdc++.h>
using namespace std;
const long long mod = 192600817;
long long qianzhui[40010];
long long fibo[40010];

int main(){
	memset(qianzhui,0,sizeof(qianzhui));
	memset(fibo,0,sizeof(fibo));
	fibo[1]=fibo[2]=1;
	qianzhui[1]=1,qianzhui[2]=2;
	for(int i=3;i<=40005;i++){
		fibo[i]=(fibo[i-1]+fibo[i-2])%mod;
		qianzhui[i]=(qianzhui[i-1]+(fibo[i]*fibo[i])%mod)%mod;
	}
	int Q;int a,b,c,d;
	while(~scanf("%d",&Q)){
		for(int j=1;j<=Q;j++){
			scanf("%d %d %d %d",&a,&b,&c,&d);
			int from=a*4+b+1;
			int to = c*4+d+1;
			if(from>to){
				int tmp=to;
				to=from;
				from=tmp;
			}
			printf("%lld\n",(qianzhui[to]-qianzhui[from-1]+mod)%mod) ;
			
		}
	}
	return 0;
}
