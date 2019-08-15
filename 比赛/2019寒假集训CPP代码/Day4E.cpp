#include<bits/stdc++.h>
using namespace std;

int main(){
	priority_queue<pair<long long,long long> > a;
	long long n;scanf("%lld",&n);
	for(long long i=1;i<=n;i++){
		long long x; scanf("%lld",&x);
		pair<long long ,long long> b(-x,-i);
		a.push(b);
	}
	priority_queue<pair<long long,long long> > b;
	
	while(a.size()!=0){
		if(a.size()>1){
			pair<long long ,long long> tmp1=a.top();a.pop(); 
			pair<long long ,long long> tmp2=a.top();a.pop();
			if(tmp1.first==tmp2.first){
				pair<long long ,long long> tmp3(tmp1.first*2,min(tmp1.second,tmp2.second));
				a.push(tmp3);
				
			}else{
				
				a.push(tmp2);
					
				pair<long long,long long> c(tmp1.second,tmp1.first);
				
				b.push(c);
			}
		}
		else{
			pair<long long,long long> ttm=a.top(); a.pop();
			pair<long long,long long> c(ttm.second,ttm.first);
			b.push(c);
		}
	}
	long long si=b.size();
	printf("%lld\n",si);
	while(b.size()!=0){
		pair<long long,long long> tt=b.top(); b.pop();
		printf("%lld ",-tt.second);
	}
	return 0;
}
