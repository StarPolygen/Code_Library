//博弈  手动推P,N状态
//初始态为1，s，o轮流进行操作，s先手，操作是轮流乘以2~9的数，先大于等于n的人获胜
//2-9为N ——> 10-18为P,因为任意操作会回到N ——> 19-162为N 因为存在操作到达P 以此类推
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll ans[18];
int main() {
    ans[1]=9;
    for(int i=2;i<=17;i++){
        if(i%2==0) ans[i]=ans[i-1]*2;
        else ans[i]=ans[i-1]*9;
    }
    ll n;
    while(~scanf("%d",&n)){
        for(int i=1;i<17;i++){
            if(n<=ans[i]){
                if(i%2==1) printf("Stan wins.\n");
                else printf("Ollie wins.\n");
                break;
            }
        }
    }
    return 0;
}