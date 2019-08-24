//贪心 
#include<cstdio>
#include<cstring>

using namespace std;
const int maxn=100000;

char ch[maxn];


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", ch);
        int n=strlen(ch);
        int p=0;
        while (p<n && ch[p]=='y') {
            p++;
        }
        if (p<n && ch[p]=='z') {
            ch[p]='b';
        }
        printf("%s\n", ch);
    }
    return 0;
}

/*
6
a
zbc
yzasd
yyzz
yyzaz
yabc
*/