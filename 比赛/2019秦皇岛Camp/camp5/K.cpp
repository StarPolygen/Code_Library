//模拟
//魔方旋转
#include <bits/stdc++.h>
using namespace std;
#define maxn 50
int arr[maxn],vans[maxn],n,ans;
int cal(int *arr);
void dfs(int num,int * arr);
int main(){
    while(~scanf("%d",&n)){
        for(int i=0;i<24;i++)   scanf("%d",&arr[i]);
        ans=0;
        dfs(1,arr);
        printf("%d\n",ans);
    }
   return 0;
}
int rota[6][24]={ //转换矩阵
    {6,1,12,3,5,11,16,7,8,9,4,10,18,13,14,15,20,17,22,19,0,21,2,23},
    {20,1,22,3,10,4,0,7,8,9,11,5,2,13,14,15,6,17,12,19,16,21,18,23},
    {0,1,11,5,4,16,12,6,2,9,10,17,13,7,3,15,14,8,18,19,20,21,22,23},
    {0,1,8,14,4,3,7,13,17,9,10,2,6,12,16,15,5,11,18,19,20,21,22,23},
    {2,0,3,1,6,7,8,9,23,22,10,11,12,13,14,15,16,17,18,19,20,21,5,4},
    {1,3,0,2,23,22,4,5,6,7,10,11,12,13,14,15,16,17,18,19,20,21,9,8}};
int cal(int * arr) {  //计算形
    int res=0;
    if(arr[0]==arr[1]&&arr[0]==arr[2]&&arr[0]==arr[3])         res++;
    if(arr[16]==arr[17]&&arr[16]==arr[18]&&arr[16]==arr[19])   res++;
    if(arr[20]==arr[21]&&arr[20]==arr[22]&&arr[20]==arr[23])   res++;
    if(arr[4]==arr[5]&&arr[4]==arr[10]&&arr[4]==arr[11])       res++;
    if(arr[6]==arr[7]&&arr[6]==arr[12]&&arr[6]==arr[13])       res++;
    if(arr[8]==arr[9]&&arr[8]==arr[14]&&arr[8]==arr[15])       res++;
    return res;
}
void dfs(int num,int * arr){
    ans=max(ans,cal(arr));
    if(num>n)  return;
    int vans[maxn]; 
    for(int i=0;i<6;i++){
        for(int j=0;j<24;j++)
            vans[j]=arr[rota[i][j]];
        dfs(num+1,vans);
    }
}