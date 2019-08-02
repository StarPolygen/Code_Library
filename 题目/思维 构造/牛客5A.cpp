//基础构造题 
//给定n n在1到100 要求构造一个数满足 1）数位个数不超过1e4  各数位之和被n整除  数本身被n整除
//可以将n复读n遍 必定满足以上三个条件
#include<bits/stdc++.h>
#define ll long long
using namespace std;


int main() {
    int T,n; scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            printf("%d",n);
        }
        printf("\n");
    }
    return 0;
}