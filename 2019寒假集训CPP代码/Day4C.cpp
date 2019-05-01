#include <bits/stdc++.h>
const int maxn=200000+10;
struct Edge{
	int x,y;
} edge[maxn];
int main(){
	int n,m,k;
	int rank[n+1];
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",rank[i]);
	}
	for(int i=1;i<=m;i++){
		int from,to;
		scanf("%d%d",&from,&to);
		edge[i].x=from;
		edge[i].y=to;
	}
	return 0;	
}
