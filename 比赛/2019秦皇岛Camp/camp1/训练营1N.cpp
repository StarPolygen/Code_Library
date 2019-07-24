#include<bits/stdc++.h>
#define ll long long
#define maxn 502000
using namespace std;

int father[maxn];
int find(int x);
void unite(int x,int y);
void ini();

int find(int x){
    if(x==father[x]) return x;
    return father[x] = find(father[x]);
}
void unite(int x,int y){
    int l=find(x);
    int r=find(y);
    father[r] = l;
}
void ini(){
	for (int i = 0; i < maxn;i++){
            father[i] = i;
    }
}

int sz[maxn];
int main() {
    ini();
    int n,m; scanf("%d%d",&n,&m);
    memset(sz,0,sizeof(sz));
    for(int i=1;i<=m;i++){
        int k;
        scanf("%d",&k);
        vector<int> pt;
        for(int i=1;i<=k;i++){
            int tmp;
            scanf("%d",&tmp);
            pt.push_back(tmp);
        }
        for(int i=0;i<k-1;i++){
                unite(pt[i],pt[i+1]);
        }
    }
    for(int i=1;i<=n;i++){
        sz[find(i)]++;
    }
    for(int i=1;i<=n;i++){
        printf("%d ",sz[find(i)]);
    }
    return 0;
}