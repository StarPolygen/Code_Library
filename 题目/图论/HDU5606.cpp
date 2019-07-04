//DFS 
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>
#define maxn 100100
#define ll long long
using namespace std;
const double eps = 1e-8;
int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }

int ans=0;
bool vis[maxn];
vector<int> G[maxn];
void dfs(int v){
    vis[v] = true;
    ans++;
    for(int i = 0; i < G[v].size(); i++){
        if(vis[G[v][i]] == false){
            dfs(G[v][i]); // 如果该顶点未访问，深度遍历之
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        // memset(arr,0,sizeof(arr));
        memset(vis,0,sizeof(vis));
        for(int i=0;i<maxn;i++){
            G[i].clear();
        }
        int all=0;
        for(int i=1;i<=n-1;i++){
            int a,b; double w;
            scanf("%d%d%lf",&a,&b,&w);
            if(sgn(w-0)==0) {
                G[a].push_back(b);
            }
        }
        for(int i=1;i<=n;i++){
            if(!vis[i]) {
                ans=0;
                dfs(i);
                if(ans%2==1) all^=ans;
                // printf("%d\n",ans);
            }
        }
        printf("%lld\n",all);
    }
    return 0;
}
