//单调栈  
//单调栈由于单调性   扫一遍可以求小于当前元素的左右最近（最小）元素，或者次近,次次近....最远（最大）

#include<bits/stdc++.h>
#define ll long long
#define maxn 50100
using namespace std;

int L[maxn],R[maxn],a[maxn];
int main() {
    int t;
    scanf("%d",&t); int cas=0;
    while(t--){
        cas++;
        int n;
        scanf("%d",&n);
        memset(L,0,sizeof(L));
        memset(R,0,sizeof(R));
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        stack<int> S;
        for(int i=1;i<=n;i++){
            while(!S.empty() && a[S.top()]<a[i])
                L[i]=S.top(),S.pop();
            S.push(i);
        }
        for(int i=n;i>=1;i--){
            while(!S.empty() && a[S.top()]<a[i])
                R[i]=S.top(),S.pop();
            S.push(i);
        }
        printf("Case %d:\n",cas);
        for(int i=1;i<=n;i++){
            printf("%d %d\n",L[i],R[i]);
        }

    }
    return 0;
}