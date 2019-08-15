#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
 #define INFL 0x3f3f3f3f3f3f3f3f
 #define zero_(x,y) memset(x , y , sizeof(x))
 #define zero(x) memset(x , 0 , sizeof(x))
 #define MAX(x) memset(x , 0x3f ,sizeof(x))
 #define ll long long
const int maxn = 1000000;
using std::vector;
struct edge{
	bool operator <(const edge& edg) const{
        return dis < edg.dis;
    }
    int from=0,to=0;ll dis=0;
    edge(int from,int to,ll dis){
		this->dis=dis;
		this->from=from;
		this->to=to;
	};
};
vector<edge> vecto;
int father[maxn];
int find(int x);
void unite(int x,int y);
int main()
{
    	int T,n,m;
		ll ans;
    	ans=0;
        vecto.clear();
        for (int i = 0; i < maxn;i++){
            father[i] = i;
        }
        scanf("%d%d", &n, &m);
        ll ai[n+1];ll mi=INFL;int miindex=0;
		for(int i=1;i<=n;i++){
			ll tmpp=0;
			scanf("%lld",&tmpp);
			ai[i]=tmpp;
			if(mi>tmpp){
				mi=tmpp;
				miindex=i;
			}
		} 
		for(int i=1;i<=n;i++){
			
				vecto.push_back(edge(i, miindex, ai[i]+mi));
				vecto.push_back(edge(miindex, i, ai[i]+mi));
		
		}
        for(int p=0;p<m;p++){
            int x, y;
			ll w;
            scanf("%d%d%lld", &x, &y, &w);
            vecto.push_back(edge(x, y, w));
            vecto.push_back(edge(y, x, w));
        }
        std::sort(vecto.begin(), vecto.end());
        for (int i=0;i<vecto.size();i++)
        {	
        	int lll=find(vecto[i].from);
        	int rrr=find(vecto[i].to);
            if(lll!=rrr){
                unite(vecto[i].from, vecto[i].to);
                ans = ans+vecto[i].dis;
            }
        }
        printf("%lld\n", ans);
}
int find(int x){
    if(x==father[x]) return x;
    return father[x] = find(father[x]);
}
 
void unite(int x,int y){
    int l=find(x);
    int r=find(y);
    father[r] = l;
}

