#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#define int long long
using namespace std;
typedef long long ll;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int wx[maxn], wy[maxn];//每个点的顶标值（需要根据二分图处理出来）
int cx[maxn], cy[maxn];//每个点所匹配的点
int visx[maxn], visy[maxn];//每个点是否加入增广路
int cntx, cnty;//分别是X和Y的点数
int Map[10][maxn];//二分图边的权值
int slack[maxn];//边权和顶标最小的差值

bool dfs(int u)//进入DFS的都是X部的点
{
    visx[u] = 1;//标记进入增广路
    for(int v = 1; v <= cnty; v++)
    {
        if(!visy[v] && Map[u][v] != INF)//如果Y部的点还没进入增广路,并且存在路径
        {
            int t = wx[u] + wy[v] - Map[u][v];
            if(t == 0)//t为0说明是相等子图
            {
                visy[v] = 1;//加入增广路

                //如果Y部的点还未进行匹配
                //或者已经进行了匹配，可以从原来的匹配反向找到增广路
                //那就可以进行匹配
                if(cy[v] == -1 || dfs(cy[v]))
                {
                    cx[u] = v;
                    cy[v] = u;//进行匹配
                    return 1;
                }
            }
            else if(t > 0)//此处t一定是大于0，因为顶标之和一定>=边权
            {
                slack[v] = min(slack[v], t);
                //slack[v]存的是Y部的点需要变成相等子图顶标值最小增加多少
            }
        }
    }
    return false;
}

int KM()
{
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    memset(wx, 0, sizeof(wx));//wx的顶标为该点连接的边的最大权值
    memset(wy, 0, sizeof(wy));//wy的顶标为0
    for(int i = 1; i <= cntx; i++)//预处理出顶标值
    {
        for(int j = 1; j <= cnty; j++)
        {
            if(Map[i][j] == INF)continue;
            wx[i] = max(wx[i], Map[i][j]);
        }
    }
    for(int i = 1; i <= cntx; i++)//枚举X部的点
    {
        memset(slack, INF, sizeof(slack));
        while(1)
        {

            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(dfs(i))break;//已经匹配正确
            
            
            int minz = INF;
            for(int j = 1; j <= cnty; j++)
                if(!visy[j] && minz > slack[j])
                    //找出还没经过的点中，需要变成相等子图的最小额外增加的顶标值
                    minz = slack[j];
            //和全局变量不同的是，全局变量在每次while循环中都需要赋值成INF，每次求出的是所有点的最小值
            //而slack数组在每个while外面就初始化好，每次while循环slack数组的每个值都在用到
            //在一次增广路中求出的slack值会更准确，循环次数比全局变量更少
            
                
            //还未匹配，将X部的顶标减去minz，Y部的顶标加上minz
            for(int j = 1; j <= cntx; j++)
                if(visx[j])wx[j] -= minz;
            for(int j = 1; j <= cnty; j++)
                //修改顶标后，要把所有不在交错树中的Y顶点的slack值都减去minz
                if(visy[j])wy[j] += minz;
                else slack[j] -= minz;
        }
    }

    int ans = 0;//二分图最优匹配权值
    for(int i = 1; i <= cntx; i++)
        if(cx[i] != -1)ans += Map[i][cx[i]];
    return ans;
}
int n, k;
signed main()
{
        scanf("%d",&n);
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= 5; j++)
                scanf("%d", &Map[j][i]);
        }
        cntx =5; cnty = n;
        printf("%lld\n", KM());
    
    return 0;
}