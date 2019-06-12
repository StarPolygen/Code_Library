#include<bits/stdc++.h>
#define ll long long
#define maxn 110
using namespace std;

char stu[maxn][maxn];
int n;
int ss[27];

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s", &stu[i]);
    }
    for(int i=1;i<=n;i++){
        ss[stu[i][0]-'a']++;
    }
    ll ans=0;
    for(int i=0;i<=26;i++){
        int le=ss[i]/2;
        int ri=ss[i]-le;
        ans+=le*(le-1)/2+ri*(ri-1)/2;
    }
    printf("%lld\n",ans);
    return 0;
}

