//分治 构造             Author：Ming
//构造一个2^k阶的1 -1方阵 使得行向量两两內积为0
//思路：2阶 1 -1
/*         1  1
  之后的构造可以以之前的为基石 如2^n+1阶可以由2^n转化而来  假设2^n阶满足条件方阵为A
  2^n+1阶 为  A -A
              A  A 即可
*/
#include<cstdio>
#include<cstring> 
using namespace std;
 
int res[2000][2000];
 
void DQ(int x,int y) {
    if (x==1 && y==1) {
        res[1][1]=1;
        return ;
    }
    DQ(x/2,y/2);
    for (int i=1;i<=x/2;i++) {
        for (int j=1;j<=y/2;j++) {
            res[i+x/2][j+y/2]=res[i][j];
            res[i][j+y/2]=res[i][j];
            res[i+x/2][j]=-res[i][j];
        }
    }
    return ;
}
 
//void debug(int m) {
//  for (int i=1;i<=m;i++) {
//      for (int j=i+1;j<=m;j++) {
//          int sum=0;
//          for (int k=1;k<=m;k++) {
//              sum=sum+res[i][k]*res[j][k];
//          }
//          if (sum!=0) {
//              printf("SHIT!\n");
//          }
//      }
//  }
//}
int main() {
    int m;
    scanf("%d",&m);
    memset(res,0,sizeof(res));
    DQ(m,m);
//  debug(m);
    for (int i=1;i<=m;i++) {
        for (int j=1;j<=m;j++) {
            printf("%d%s", res[i][j], j==m? "\n":" ");
        }
    }
    return 0;
}