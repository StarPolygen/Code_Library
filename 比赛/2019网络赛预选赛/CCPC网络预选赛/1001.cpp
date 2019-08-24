//思维 签到
#include<bits/stdc++.h>


ll A, B;

int main(){
    int _;
    for (scanf("%d", &_); _;_--)
    {
        scanf("%lld%lld",&A,&B);
        printf("%lld\n", max((A & B), 1ll));
    }
    return 0;
}