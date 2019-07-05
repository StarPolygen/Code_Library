//CF 1061C
//预处理所有因数
//之后DP
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define maxn 1000010
using namespace std;

//f[i]中存储的是长度为i的b子序列个数
int f[maxn],arr[maxn];
vector<int>v[maxn];   //v[i]中是i的因数

int main() {
    int n; scanf("%d",&n);
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
        v[i].clear();
        //分解所有因数  复杂度O(sqrt(n))
        for(int j=1;j<=sqrt(x);j++){
            if(x%j==0){
                v[i].push_back(j);
                if(x!=j*j)v[i].push_back(x/j);
            }
        }
        sort(v[i].begin(),v[i].end());  //由于DP压缩到一维，所以需要排序，为后面的DP做准备
    }


    //DP 统计答案
    ll ans=0;
    f[0]=1;
    for(int i=1;i<=n;i++){
        for(int j=v[i].size()-1;j>=0;j--){  //从大因数更新，以满足无后效性
            f[v[i][j]]=(f[v[i][j]]+f[v[i][j]-1])%MOD;
            ans=(ans+f[v[i][j]-1])%MOD;
        }
    }
    printf("%d\n",ans);
    return 0;
}