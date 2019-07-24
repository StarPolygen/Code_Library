//牛客2H 
//01矩阵最大子矩阵/直方图最大矩阵（单调栈） + 特判
//准备出成 DSAA-Lab4 Bonus
#include<bits/stdc++.h>
#define ll long long
using namespace std;

char arr[1010][1010];int n,m;
int cur[1010][1010];
int zd=0,cd=0;
void findmost(int row){
    stack<int> s;
    for (int i = 0; i <m; i++) {
        if (s.empty() || cur[row][s.top()] < cur[row][i]) {        
            s.push(i);
            // if(cur[row][i]>cd){
            //     cd=cur[row][i];
            //     printf("cd change to %d, zd %d\n",cd,zd);
            // }     
        } else {        
            int start = s.top(); s.pop();        
            int width = s.empty() ? i : i - s.top() - 1;        
            if(cur[row][start] * width>=zd){
                cd=zd; zd=cur[row][start] * width;
            } else if(cur[row][start] * width>cd){
                cd=cur[row][start]*width;
            }     
            if(cur[row][start] *(width-1) > cd){
                cd=cur[row][start] *(width-1);       
            }
            i--;      
        }    
    }    
    while (!s.empty()) {      
        int start = s.top(); s.pop();      
        int width = s.empty() ? m : m - s.top() - 1;      
        if(cur[row][start] * width>=zd){
            cd=zd; zd=cur[row][start] * width;
        }else if(cur[row][start] * width>cd){
            cd=cur[row][start]*width;
        }       
         if(cur[row][start] *(width-1) > cd){
                cd=cur[row][start] *(width-1);       
            }       
    }    

}
int main() {
    memset(cur,0,sizeof(cur));
    memset(arr,0,sizeof(arr));
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%s",arr[i]);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i==0) cur[i][j]=arr[i][j]=='1'?1:0;
            else{
                if(arr[i][j]=='1') cur[i][j]=cur[i-1][j]+1; 
            }
            
        }
    }
    // printf("\n");
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         printf("%d",cur[i][j]);
    //     }printf("\n");
    // }
    for(int i=0;i<n;i++){
        findmost(i);
        // printf("%d %d\n",zd,cd);
    }
    printf("%d\n",cd);
    return 0;
}