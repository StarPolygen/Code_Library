#include<bits/stdc++.h>
const int maxn=50010;
int D[maxn];
int lowbit(int x){return x&(-x);}
void add(int x,int k,int n){
	while(x<=n){
		D[x]+=k;
		x+=lowbit(x); 
	}
}
int querypf(int x){
	int sum=0;
	while(x>0){
		sum+=D[x];
		x-=lowbit(x);
	}
	return sum;
}
int query(int L,int R){
	return querypf(R)-querypf(L-1);
}
int main(){
	int t;
	scanf("%d",&t);
	for(int ac=1;ac<=t;ac++){
		int n; scanf("%d",&n);
		for(int i=0;i<=n+1;i++) D[i]=0;
		for(int i=1;i<=n;i++){
			int tmp;
			scanf("%d",&tmp);
			add(i,tmp,n);
		}

		printf("Case %d:\n",ac);
		while(1){
			getchar();
			char a[7];int i,j,k;
			scanf("%s",&a);
			if(a[0]=='A') {
				scanf("%d%d",&i,&j);	
				add(i,j,n);
			}else if(a[0]=='S'){
				scanf("%d%d",&i,&j);
				add(i,-j,n);
			}else if(a[0]=='Q'){
				scanf("%d%d",&i,&j);
				printf("%d\n",query(i,j));
			}
			if(a[0]=='E') break;
		}
	}
	return 0;
}
