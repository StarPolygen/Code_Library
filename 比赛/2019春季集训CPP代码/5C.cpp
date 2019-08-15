#include<cstring>
#include<cstdio>
#include<iostream> 
using namespace std;

int nxt[100001];
int ans,n,m,T;
char p[100001], s[100001];
int main(){
    while(~scanf("%s%s", p+1,s+1)){
    	
        n = strlen(s+1);
        m = strlen(p+1);
        ans = 0;
        nxt[0] = -1;
        int j = -1;
        for(int i=1; i<=m; i++){
            while(j>=0 && p[j+1]!=p[i]) j = nxt[j];
            nxt[i] = ++j;
        }
        j = 0;
        for(int i=1; i<=n; i++){
            char c = s[(i-1)%n +1];
            while(j>=0 && p[j+1]!=c) j = nxt[j];
            if(++j == m){
                if(i==n) break; 
                j = nxt[j];     
            }
        }
        if(j==0) printf("%d\n", 0);
        else{
            p[j+1] = 0;
            printf("%s %d\n",p+1,j); 
        } 
    }

    return 0;
}


