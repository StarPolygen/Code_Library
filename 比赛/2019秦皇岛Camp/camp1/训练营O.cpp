#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define maxn  200200
int arr[maxn];
vector<int> G[maxn];
bool vis[maxn];
bool flag=true;
void dfs(int v){
    vis[v] = true;
    for(int i = 0; i < G[v].size(); i++){
        if(vis[G[v][i]] == false){
            arr[G[v][i]]=arr[v]*-1; 
            dfs(G[v][i]);
            
        }else{
            if(arr[G[v][i]]!=arr[v]*-1){
                flag=false;
            }
        }
    }
}
int main() {
    int n,m;

    memset(arr,0,sizeof(arr));
    memset(vis,false,sizeof(vis));
    for(int i=0;i<maxn;i++) G[i].clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]) arr[i]=1,dfs(i);
    }
    if(!flag) printf("-1\n");
    else {
        int tot1=0,tot2=0;
        int ans1[maxn],ans2[maxn];
        for(int i=1;i<=n;i++){
           if(arr[i]==-1) ans1[tot1++]=i;
           else if(arr[i]==1) ans2[tot2++]=i;
        }
        if(tot1==0||tot2==0) printf("-1\n");
        else{
        printf("%d\n",tot1);
        sort(ans1,ans1+tot1);
        for(int i=0;i<tot1;i++) printf("%d ",ans1[i]);
        printf("\n");
        printf("%d\n",tot2);
        sort(ans2,ans2+tot2);
        for(int i=0;i<tot2;i++) printf("%d ",ans2[i]);
        }
    }


    // printf("\n");
    // for(int i=1;i<=n;i++) printf("%d ",arr[i]);
    return 0;
}