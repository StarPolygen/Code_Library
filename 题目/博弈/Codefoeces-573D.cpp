//博弈 奇异局势
//N堆石子 每次取1颗  无石子可取 或 取完之后产生两堆数量一样则输
//易得0 1...n-1是必败态  其他非奇异局势下两者均必有可行操作  最终抵达此状态者输  因此判定总数与此状态间石子数差的奇偶性即可

//本题的难点在于对奇异局势（即博弈过程中不会出现，但初始局势可能为的情况）的特判：
//1.大于等于 2个  0
//2.大于等于 2对 成双
//3.大于等于 1对 成三
//4.成双的棋子-1 存在
//这些情况先手上来就会死 但他们不会在除初始状态外的游戏中出现 因为他们都含有成双 在此之前游戏就已经结束 上一步的人已成输家
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll arr[100010];
int main() {
    int n;
    scanf("%d",&n);
    ll ans=0;
    for(int i=1;i<=n;i++){
        ll tmp;
        scanf("%lld",&tmp);
        arr[i]=tmp;
        ans+=tmp;
    }
    sort(arr+1,arr+n+1);

    //对奇异局势的判断：flag3代表成3个数 cnt代表成双个数 zeo代表0个数 flag4代表是否成双-1存在
    ll flag2=1,flag3=0,cnt=0,zeo=0,flag4=0;
    if(arr[1]==0) zeo++;
    for(int i=2;i<=n;i++){

        if(arr[i]==arr[i-1]) flag2++;
        else flag2=1;

        if(flag2==2) {
            cnt++;
            if(arr[i]==arr[i-2]+1&&i>2) flag4=1; 
        }
        if(flag2==3) flag3=1;

        if(arr[i]==0) zeo++;
    }
    ll all=1ll*(n-1)*n/2;
    
    //处理奇异情况：初始就面对成双且无法祛除:  成三 || 两成双 || 两零 || 成双-1存在  
    //当面临这些情况时，除了初始状态，游戏应当已经结束，因为他们都有成双
    //因此需要对这些  初始面对成双却无法改变  的情况进行特判
    if(flag3==1||cnt>=2||zeo>=2||flag4) printf("cslnb\n");

    //非奇异局势：若棋子之总数大于0-n-1之和  则双方都必有可行步骤  面临0-n-1的人会输 因此判定总数减(n-1)n/2的奇偶性即可
    else{
        ll jud=ans-all;
        if(jud==0||jud%2==0) printf("cslnb\n");
        else printf("sjfnb\n");
    }
    return 0;
}