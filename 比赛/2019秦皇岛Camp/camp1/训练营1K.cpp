#include <bits/stdc++.h>
const int maxn = 4000300;
using std::vector;
struct edge{
	bool operator <(const edge& edg) const{
        return dis < edg.dis;
    }
    int from=0,to=0,dis=0;
    edge(int from,int to,int dis){
		this->dis=dis;
		this->from=from;
		this->to=to;
	};
};
int father[maxn];
int find(int x);
void unite(int x,int y);
int main()
{		
		vector<edge> vecto;
		vecto.clear();
    	int n,m,ans;
    	ans=0;
        
        scanf("%d%d", &n, &m);
        int sta[n+2];
        for (int i = 0; i <=n;i++){
            father[i] = i;
        }
        for(int i=0;i<=n;i++) sta[i]=0;
        for(int p=0;p<m;p++){
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            vecto.push_back(edge(x, y, -w));
            
        }
        std::sort(vecto.begin(), vecto.end());
        for (int j=0;j<vecto.size();j++)
        {	
        	edge len=vecto[j];
        	int lll=find(len.from);
        	int rrr=find(len.to);
        
            if(lll==rrr){
            	if(sta[lll]==0) {
            		ans+=len.dis; sta[lll]=1;
            		
				}
				
			}
			else{
				if((sta[lll]==0&&sta[rrr]==1)||(sta[lll]==1&&sta[rrr]==0)){
					ans+=len.dis;
					unite(len.from,len.to);
					sta[find(len.from)]=1;
					
				}else if(sta[lll]==0&&sta[rrr]==0){
					ans+=len.dis;
					unite(len.from,len.to);
					sta[find(len.from)]=0;
					
				}
			}
        }
        printf("%d\n", -ans);
    
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