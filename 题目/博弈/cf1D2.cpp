//博弈
//SG打表找规律
#include<bits/stdc++.h>
#define ll long long
using namespace std;


int main() {
    int T;scanf("%d",&T);
    while(T--){
        ll n,k;
        scanf("%lld%lld",&n,&k);
        if(k%3!=0) {
            if(n%3==0) printf("Bob\n");
            else printf("Alice\n");
        }else if(k!=3){
            ll p=(k/3)-1;
            ll xunhuan=p*3+4;
            ll shengyu=n%xunhuan;
            // printf("xunhuan: %lld  shengyu:%lld\n",xunhuan,shengyu);
            if(shengyu==0||(shengyu!=0&&(shengyu%3)==0)&&shengyu!=(xunhuan-1)) printf("Bob\n");
            else printf("Alice\n");
        }else{
            if(n%4==0) printf("Bob\n");
            else printf("Alice\n");
        }
    }
    return 0;
}