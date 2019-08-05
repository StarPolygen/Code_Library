//打表 规律
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;

int arr[100020];

int main() {
    int T; scanf("%d",&T);
    int N,x,y;
    arr[0]=arr[1]=0; arr[2]=1;
    for(int i=3;i<=100100;i++){
        arr[i]=(arr[i-1]+arr[i-3])%mod;
        // printf("%d ",arr[i]);
    }
    // printf("\n");
    while(T--){
        scanf("%d%d%d",&N,&x,&y);
        int s=abs(x-y);
        if(N==2||N==3){
            if(s==0) printf("0\n");
            else printf("1\n");
            continue;
        }
        if(x==1||y==1||x==N||y==N){
            if(s==(N-1)){
                printf("%d\n",((arr[s-1]*2+arr[s-2])%mod+arr[s-3])%mod);
            }else{
                printf("%d\n",arr[s+1]);
            }
        }else{
            printf("%d\n",arr[s]);
        }

    }
    return 0;
}