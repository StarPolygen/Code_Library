//博弈 SG打表 本题极易TLE
//C++头文件比G++ bits快3倍左右    O(2)优化-20MS 
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>
#pragma GCC optimize(2)
#define ll long long
using namespace std;

const int N = 101;
const int MAXN = 10001;

//f[N]:可改变当前状态的方式，N为方式的种类，f[N]要在getSG之前先预处理
//SG[]:0~n的SG函数值
//S[]:为x后继状态的集合
int f[N],SG[MAXN]; bool S[MAXN];
void getSG(int n,int k)   ///n求解范围 k是f的长度。
{
    int i,j;
    memset(SG,0,sizeof(SG));
    //因为SG[0]始终等于0，所以i从1开始
    for(i = 1; i <= n; i++){
        //每一次都要将上一状态 的 后继集合 重置
        memset(S,0,sizeof(S));
        for(j = 0; f[j] <= i && j < k; j++)
            S[SG[i-f[j]]] = 1;  //将后继状态的SG函数值进行标记
        for(j = 0; j < n; j++)  
            if(!S[j])   //查询当前后继状态SG值中最小的非零值
            break;
        SG[i] = j;
    }
}


int main() {
    int k,m,l,ach,tmp;
    while(true){
        scanf("%d",&k);
        if(k==0) break;
        for(int i=0;i<k;i++){
            scanf("%d",&f[i]);
        }
        sort(f,f+k);
        getSG(10001,k);
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%d",&l);
            ach=0;
            for(int j=1;j<=l;j++) {
                scanf("%d",&tmp);
                ach^=SG[tmp];
            }
            if(ach) printf("W");
            else printf("L");
        }
        printf("\n");
    }
    return 0;
}