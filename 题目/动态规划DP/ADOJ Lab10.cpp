//二维背包

#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int> 
using namespace std;

#define maxn 110

pii cl[maxn];
int n=0;
int num=0;
int tmp=0;


bool cmp(pii a,pii b){
    return a.second > b.second || (a.second == b.second && a.first > b.first);
}



int main()
{   
    memset(cl,0,sizeof(cl));
    //首先寻找最少的容纳学生的教室数量
    scanf("%d", &n);
    int tot = 0; 
    cl[0].first=cl[0].second=0;
    for (int i = 1; i <= n; i++)
    {   
        scanf("%d%d", &cl[i].first, &cl[i].second);
        tot += cl[i].first;
    }
    sort(cl + 1, cl + n + 1, cmp);
    tmp = tot;
    for (int i = 1; tot > 0; i++)
    {
        num++;
        tot -= cl[i].second;
    }



    //背包质量为num.每个贡献为1         数量限制
    //背包容积为cap，每个贡献为101-bi   容积限制
    //要使需要移动的学生总数最小，则被选取教室已存在学生数最大
    int cap = 101 * num - tmp;    //  printf("tmp: %d  num: %d  cap: %d\n",tmp,num,cap);
    

    //初始化 ：必须选取num个
    //因此设置OPT[i][0][k]=0 其他负无穷
    int OPT[2][num+1][cap+1];
    memset(OPT,0,sizeof(OPT));
    for(int i=0;i<=1;i++){
        for(int j=0;j<num+1;j++){
            for(int k=0;k<cap+1;k++){
                if(j!=0)
                OPT[i][j][k]=-1e9;
            }
        }
    }



    for(int i=1;i<=n;i++){
        for(int j=1;j<=num;j++){
            for(int k=1;k<=cap;k++){
                int bi = (101 - cl[i].second);
                if(bi > k || 1 > j){
                    OPT[i%2][j][k] = OPT[(i-1)%2][j][k];
                }else{
                    OPT[i%2][j][k] = max(OPT[(i-1)%2][j][k], OPT[(i-1)%2][j-1][k-bi] + cl[i].first); 
                }
            }
        }
    }
   
    printf("%d\n",tmp-OPT[n%2][num][cap]);
    return 0;
}