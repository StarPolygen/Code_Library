//规律 结论
//4×4的滑块拼图游戏 元素为1-15 以及一个空格用0表示 问是否能在120次移动内到达目标状态
/*1 2 3 4 
  5 6 7 8 
  9 10 11 12 
  13 14 15 0
结论：当有解时必然可以在49步内移动完，因此只要判断无解情况即可
      当将空格看做16,从上到下左到右把元素构成序列，当且仅当该序列逆序对数与空格到右下角的曼哈顿距离同奇同偶时有解，输出"Yes"*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10;
int a[N][N];
vector<int> b;
void work(){
    b.clear();
    int dis = 0;
    for (int i = 1; i <= 4;i++)
    {
        for (int j = 1; j <= 4;j++)
        {
            scanf("%d", &a[i][j]);
            b.push_back(a[i][j] == 0 ? 16 : a[i][j]);
            if (a[i][j]==0){
                dis = abs(4 - i) + abs(4 - j);
            }
        }
    }
    int inv = 0;
    for (int i = 0; i < b.size();i++)
    {
        for (int j = i + 1; j < b.size();j++)
        {
            if (b[i]>b[j]){
                inv++;
            }
        }
    }
    if ((inv&1)==(dis&1)){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
}
int main(){
    int t;
    scanf("%d", &t);
    while (t--){
        work();
    }
    return 0;
}