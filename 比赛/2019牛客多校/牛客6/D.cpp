//傻逼构造
#include<bits/stdc++.h>
#define ll long long
using namespace std;


int main() {
    int n,p;
    scanf("%d%d",&n,&p);
    int chang=0;
    int c=p;
    while(p>0){
        p/=10;
        chang++;
    }
    // printf("%d\n",chang);
    if(n<chang){
        printf("T_T\n");
    }else if(n==chang){
        printf("%d\n",c);
    }else{
        printf("%d",c);
        for(int i = 0;i<n-chang;i++){
            printf("0");
        }
        printf("\n");
    }
    return 0;
}