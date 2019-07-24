//找规律  打表
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll arr[100001];
int main() {
    arr[0]=0;
    int ans=3;
    for(int i=1;i<=100000;i++){
        arr[i]=arr[i-1]+ans;
        ans+=2;
    }
    // for(int i=1;i<=100;i++) printf("%d ",arr[i]); printf("\n");

    int T; scanf("%d",&T);
    for(int k=1;k<=T;k++){
        int n; scanf("%d",&n);
        for(int i=1;i<=100000;i++){
            if(arr[i]>=n) {
                if(i%2==1) printf("Case %d: odd\n",k);
                else printf("Case %d: even\n",k);
                break;
            }
        }
    }
    return 0;
}
