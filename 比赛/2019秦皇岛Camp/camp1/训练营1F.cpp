#include<bits/stdc++.h>
#define ll long long
#define maxn 100100
using namespace std;

struct node{
    int id;
    int val;
};
node arr[maxn];
int att[maxn];
int vis[maxn];
int cmp(node x,node y){
    return x.val<y.val;
}
vector<int> G[maxn];
int main() {
    int n,m;
    scanf("%d %d",&n,&m);
    memset(arr,0,sizeof(arr));
    memset(vis,0,sizeof(vis));
    memset(att,0,sizeof(att));
    for(int i=1;i<=n;i++){
        arr[i].id=i;
        int tmp;
        scanf("%d",&tmp);
        att[i]=tmp;
        arr[i].val=tmp;;
    }
    ll ans=0;
    sort(arr+1,arr+1+n,cmp);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=n;i>=1;i--){
        vis[arr[i].id]=1;
        for(int j=0;j<G[arr[i].id].size();j++){
            int v=G[arr[i].id][j];
            if(vis[v]==0){
                ans+=att[v];
                // printf("%d %d %d\n",arr[i].id,v,ans);
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}