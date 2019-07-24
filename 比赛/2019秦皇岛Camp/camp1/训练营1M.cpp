#include<bits/stdc++.h>
#define ll long long
using namespace std;

struct edge{
    int u,v,w;
    edge(int _u,int _v,int _cost):u(_u),v(_v),w(_cost){}
};
vector<edge> ES;
int arr[100200];
int main() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        ES.push_back(edge(a,b,c));
    }
    for(int i=1;i<=k;i++){
        int tmp;
        scanf("%d",&tmp);
        arr[tmp]++;
    }
    ll mins=1000000000000;
    int ans=-1;
    for(int i=0;i<ES.size();i++){
        if(arr[ES[i].u]!=0&&arr[ES[i].v]==0&&mins>ES[i].w){
            mins=ES[i].w;        
            ans=ES[i].v;  
        }else if(arr[ES[i].v]!=0&&arr[ES[i].u]==0&&mins>ES[i].w){
            mins=ES[i].w;        
            ans=ES[i].u;
        }
    }
    if(k==0||ans==-1) printf("-1\n");
    else printf("%d\n",mins);
    return 0;
}