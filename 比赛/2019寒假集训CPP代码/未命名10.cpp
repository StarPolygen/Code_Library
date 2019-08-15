#include <bits/stdc++.h>
#include <algorithm>

#define maxn 100010
using namespace std;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		int hang[n];
		int lie[n];
		for(int i=0;i<n;i++){
			int tmm1,tmm2;
			scanf("%d%d",&tmm1,&tmm2);
			hang[i]=tmm1;
			lie[i]=tmm2;
		}
		sort(hang,hang+n);
		sort(lie,lie+n);
	
		priority_queue<pair<int,int> > pq;
		priority_queue<pair<int,int> > pq2;
		int tmp=hang[0];int tmpnum=1;
		for(int i=1;i<n;i++){
			if(hang[i]==tmp) tmpnum++;
			else{
				pair<int,int> b(-tmp,tmpnum);
//				printf("\n%d %d\n",b.first,b.second);
				pq.push(b);
				tmp=hang[i];
				tmpnum=1;
				
			}
			if(i==n-1){
				pair<int,int> final(-tmp,tmpnum);
				pq.push(final);
			}
//			printf("%d\n",i);
		}
		 
//		while(!pq.empty()){
//			pair<int,int> bn=pq.top();
//			printf("%d %d\n",bn.first,bn.second);
//			pq.pop();
//		}
		tmp=lie[0];tmpnum=1;
		for(int i=1;i<n;i++){
			if(lie[i]==tmp) tmpnum++;
			else{
				pair<int,int> b(-tmp,tmpnum);
				pq2.push(b);
				tmp=lie[i];
				tmpnum=1;
				if(i==n-1){
					pair<int,int> final(-tmp,tmpnum);
					pq2.push(final);
				}
			}
		}
		long long ans=0;
		
		while(!(pq2.empty()||pq.empty())){
			pair<int,int> an=pq2.top();
			pair<int,int> bn=pq.top();
//			printf("lie:%d num:%d\n",-an.first,an.second);
//			printf("hang:%d num:%d\n\n",-bn.first,bn.second);
			if(-an.first>-bn.first) pq.pop();
			if(an.first==bn.first) {
				ans+=1ll*an.second*bn.second;
				pq.pop();
				pq2.pop();
			}
			else pq2.pop();
//			printf("%d\n",ans);
		}
		printf("%lld\n",ans);
	}
	return  0;
}
