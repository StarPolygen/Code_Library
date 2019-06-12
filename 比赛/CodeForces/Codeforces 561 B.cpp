#include<bits/stdc++.h>
#define ll long long
using namespace std;

char ac[]="aeiou";

int main() {
    int k;
    scanf("%d",&k);
    int flag=1;
    if(k<25) {
        flag=-1;
    }
    else{
        int ak=1;
        for(ak=1;ak<=sqrt(k)+1;ak++){
            if((k%ak)==0&&ak>=5) break;
        } 
        // printf("%d%d",ak,oyh);
        int oyh=k/ak;
        if(oyh<5||ak<5||(k%ak)!=0) {
            flag=-1;
        }else if(flag==1){
            for(int i=0;i<oyh;i++){
                for(int j=0;j<ak;j++){
                   printf("%c",ac[(i+j)%5]);
                }
                // printf("\n");
            }
        }
    }
    if(flag==-1) printf("-1\n");
    return 0;
}