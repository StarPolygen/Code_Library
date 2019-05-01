#include<iostream>
#include<bits/stdc++.h>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;
char str[maxn];
map<char, char>mp;
int nxt[maxn];

void get_next(char* s)
{	
	int len=strlen(s);
    int i,j;
    i=0;
    j=-1;
    nxt[0]=-1;
    while(i<len)
    {
        if(j==-1||s[i]==s[j])
        {
            ++i;
            ++j;
            nxt[i]=j;
        }
        else
            j=nxt[j];
    }
}


int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
        mp.clear();
        getchar();
        for(int i = 0; i < 26; i++){
            char c;
            scanf("%c", &c);
            mp[c] = 'a' + i;
        }

        scanf("%s", str);
        int len = strlen(str);
        
        for(int i=0;i<len;i++){
        	str[i]=mp[str[i]];
		}
        get_next(str);
        int skr=nxt[len];
        while(skr > (len + 1) / 2){
            skr=nxt[skr];
        }
		int ans=len-skr;
        for(int i = 0; i < ans; i++){
            printf("%c", str[i]);
        }
        for(int i = 0; i < ans; i++){
            printf("%c", mp[str[i]]);
        }
        printf("\n");
    }
    return 0;
}
