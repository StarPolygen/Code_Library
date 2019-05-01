#include <iostream>
const int maxn=200;
long double ci[maxn];

int main(){
	int C;
	scanf("%d",&C);
	while(C--){
		for(int i=0;i<maxn;i++) ci[i]=0;
		ci[1]=0;
		ci[2]=1;
		int t;scanf("%d",&t);
		if(t>2){
			for(int i=3;i<=t;i++)
			ci[i]=(i-1)*(ci[i-1]+ci[i-2]);
		}
		long double all=1;
		for(int i=1;i<=t;i++){
			all*=i;
		}
		long double ans=ci[t]/all*100;
		double ans1=(long long)(ans*100+0.5)/100.0;
		printf("%.2f%%\n",ans1);

	}
	
	return 0;

} 
