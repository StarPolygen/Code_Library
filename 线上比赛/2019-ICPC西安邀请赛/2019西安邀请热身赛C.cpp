//2019西安邀请热身赛C
//写一个计算器，包含（）单目运算符+-~ 二目运算*+-&^|,输入表达式输出结果，题上给了优先级
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int ,int> 
using namespace std;

char str[1010]; stack<char> op; stack<int> num;

int priority(char opt){
    if(opt == '(') return 0;
    if(opt == '|') return 1;
    if(opt == '^') return 2;
    if(opt == '&') return 3;
    if(opt == '+'|| opt == '-') return 4;
    if(opt == '*') return 5;
    if(opt == '/') return 6;
    if(opt == '~') return 7;
}

void calc() {
    int x,y,z;   char opt;
    if(num.size() >= 1 && !op.empty()){
        opt = op.top(); op.pop();
        if(opt == '~'){
            y = num.top(); num.pop();
            num.push(~y);
        } else if(num.size() >= 2){
            y = num.top(); num.pop();
            x = num.top(); num.pop();
            if(opt == '+')  z = x + y;
            if(opt == '-')  z = x - y;
            if(opt == '*')  z = x * y;
            if(opt == '&')  z = x & y;
            if(opt == '^')  z = x ^ y;
            if(opt == '|')  z = x | y;
            if(opt == '/')  z = x * y;
            num.push(z);
        }
        // printf("???\n");
    }
}

char tmp[1010];

void work(){
    scanf("%s", tmp);
    int nn = strlen(tmp);
    int sgn = 1; 
    for(int i = 0; i < nn; i++){
        if(tmp[i] == '-' || tmp[i] == '+'){
            if(i >= 1 && (tmp[i-1]==')' || isdigit(tmp[i-1]))){
                continue;
            }
            else sgn *= tmp[i] == '-'? -1 : 1;
            if(isdigit(tmp[i+1]) || tmp[i+1] == '~' || tmp[i+1] == '('){
                tmp[i] = sgn == 1? '+' : '-';
                sgn = 1;  
            } else {
                tmp[i] = '?';
            }
        }
    }

    //debug
    // for(int i = 0; i < nn; i++){
    //     printf("%c", tmp[i]);
    // }
    // printf("\n");


    for(int i = 0; i < nn; i++) {
        if(tmp[i] == '+' || tmp[i] == '-'){
            if(i == 0) {
                if(tmp[i] == '+') tmp[i] = 'z';
                else if(tmp[i] == '-') tmp[i] = 'f';
                continue;
            }
            
            for(int j = i-1; j >= 0; j--){
                if(isdigit(tmp[j]) || tmp[j] == ')'){
                    break;
                }
                else if(tmp[j] == '?' && j!=0){
                    continue;
                } 
                else{
                    if(tmp[i] == '+') tmp[i] = 'z';
                    else if(tmp[i] == '-') tmp[i] = 'f';
                }
                j--;
            }
        }
    }
    

    //debug
    // for(int i = 0; i < nn; i++){
    //     printf("%c", tmp[i]);
    // }
    // printf("\n");



    int len = 0;
    for(int i = 0; i < nn; i++){
        if(tmp[i] == '?') continue;
        else if(tmp[i] == 'z'){
            str[len++] = '1';
            str[len++] = '/';
        }
        else if(tmp[i] == 'f'){
            str[len++] = 'p';
            str[len++] = '/';
        }
        else{
            str[len++] = tmp[i]; 
        }
    }


    //debug
    // printf(">>>\n");
    // for(int i = 0; i < len; i++){
    //     printf("%c", str[i]);
    // }
    // printf("\n");

    for(int i = 0; i < len; i++) {
        if(isdigit(str[i]) || str[i] == 'p') {
            if(str[i] == 'p') num.push(-1);
            else num.push(str[i]-'0');
            i++;
        }
        
        char opt = str[i];

        if(i >= len) break;

        if(opt == '(') op.push(opt);
        else if(opt == ')'){
            while(!op.empty()) {
                if(op.top() == '(') {op.pop(); break;}
                calc();
            }
        } else {
            while(!op.empty() && priority(opt) <= priority(op.top())) calc();
            op.push(opt);
        }
        // printf("<<<\n");
        
    }
    while(!op.empty()) calc();
    printf("%d\n", num.top());
    while(!num.empty()) num.pop();

}

int main() {
    int T;
    scanf("%d",&T);
    while(T--){
        work();
    }
    return 0;
}
/*
输入：
11
+--+6*(-~7|4)+-2&~3
-2+1
--3+2
+3+2
-+(2)+(-3)
-3*-3*-3
-(-(-8))*2
-+-+-(-2^++3)*++5&-+7|~+-9
4-++2*3
~(5*+8)*7
9*9*9*9*9*9*9*9*9*9

输出：
68
-1
5
5
-5
-27
-16
9
-2
-287
-808182895