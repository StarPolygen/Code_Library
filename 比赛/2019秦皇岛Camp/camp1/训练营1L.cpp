#include<bits/stdc++.h>
#define ll long long
#define maxn 10000
using namespace std;

int f[maxn];
int main() {
    int n; scanf("%d",&n);
    bool ac=false;
    for(int i=1;i<=n;i++){
        scanf("%d",&f[i]);
    }
    for(int i=1;i<=n;i++){
        if(f[f[f[i]]]==i)  ac=true;
    }
    if(ac) printf("YES\n");
    else printf("NO\n");
    return 0;
}