//交互式模拟
#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
 

int A[10] = {0, 4, 8, 15, 16, 23, 42};
const int sum = 108;
map<int, int> ma;
int B[10]; //答案数组
int vis[10];

//检验获得的最终答案的合法性 
bool check()
{
    memset(vis,0,sizeof(vis));
    ma[4] = 1;
    ma[8] = 2;
    ma[15] = 3;
    ma[16] = 4;
    ma[23] = 5;
    ma[42] = 6;
    int tmp = 0;
    for (int i = 1;i <= 5;i++)
    {
        
        if (ma[B[i]] == 0||vis[B[i]]!=0)  //最终获得的序列是每项出现且仅出现1次，否则有问题
            return false;
        tmp += B[i];
        vis[B[i]]++;
    }
    B[6] = sum - tmp;
    return true;
}
 


int main()
{
 
    int ab, bc, cd, de;
    cout << '?' << ' ' << 1 << ' ' << 2 << endl;
    fflush(stdout);
    scanf("%d", &ab);
    cout << '?' << ' ' << 2 << ' ' << 3 << endl;
    fflush(stdout);
    scanf("%d", &bc);
    cout << '?' << ' ' << 3 << ' ' << 4 << endl;
    fflush(stdout);
    scanf("%d", &cd);
    cout << '?' << ' ' << 4 << ' ' << 5 << endl;
    fflush(stdout);
    scanf("%d", &de);
    //可以证明获得ab，cd,de,ef可以唯一确定当前序列

    //根据已得信息，枚举所有可能性，当满足每个元素出现且仅出现一次即可
    for (int i = 1;i <= 6;i++)
    {
        if (ab % A[i] != 0)  continue;
        B[1] = A[i];
        B[2] = ab / B[1];
        if (bc % B[2] != 0)  continue;
        B[3] = bc / B[2];
        if (cd % B[3] != 0)  continue;
        B[4] = cd / B[3];
        if (de % B[4] != 0)  continue;
        B[5] = de / B[4];
        if (check()) break;
    }
    fflush(stdout);
    cout << '!' << ' ';
    for (int i = 1;i <= 6;i++)
        cout << B[i] << ' ' ;
    cout << endl;
 
    return 0;
}