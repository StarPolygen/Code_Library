//模拟  时区变化
#include <bits/stdc++.h>
using namespace std;
map<string, int> thismap;
char op[10];
int flag;
void print(int h, int m){
    if (flag == -1)       printf("Yesterday ");
    else if (flag == 0)        printf("Today ");
    else if (flag == 1)        printf("Tomorrow ");
    if (h == 0)        printf("12:%02d AM", m);
    else if (h < 12){
        printf("%d:%02d ", h, m);
        printf("AM");
    }
    else if (h == 12) {
        printf("%d:%02d ", h, m);
        printf("PM");
    }
    else{
        printf("%d:%02d PM", h - 12, m);
    }
    printf("\n");
}
void cal(int h, int m){
    if (h < 0)  {
        h += 24;
        flag = -1;
    }
    else if (h >= 24){
        h -= 24;
        flag = 1;
    }
    print(h, m);
}
char s1[20],s2[20];
int main() {
    thismap["Beijing"] = 8;    thismap["Washington"] = -5;    thismap["London"] = 0;    thismap["Moscow"] = 3;
    int t;    scanf("%d", &t);
    for (int kkkkkkkkk = 1; kkkkkkkkk <= t; kkkkkkkkk++) {
        flag = 0;
        int h, m;
        scanf("%d:%d%s", &h, &m, op);
        scanf("%s",s1); scanf("%s",s2);
        if (op[0] == 'A'){
            if (h == 12)      h = 0;
        }
        else
        {
            if (h != 12)       h += 12;
        }
        h += thismap[s2] - thismap[s1];
        printf("Case %d: ", kkkkkkkkk);
        cal(h, m);
    }
    return 0;
}
