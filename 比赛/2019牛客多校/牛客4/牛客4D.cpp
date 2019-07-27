//思维 + 构造
//给定a，求最短序列满足序列中的数都是3的倍数并且相互或答案为a，输出该序列长度和序列本身（多种可能任一即可）
//思路：或自然想到二进制 2的次幂%3的结果具有奇偶性：2的奇数次幂%3=1 偶数次幂%3=2 因此可以按照此规律对a进行二进制表示后将偶数位的1化为2进行处理 将处理后的序列命名为p
//     接下来构造两个序列，他们本身元素之和为3倍数 且相互或可以覆盖p即可  
//     由于题目保证有合法解，先找出一个3,作为序列x，剩余的根据y中元素和%3的结果，从x中不复制，或复制一份1，或2进入y即可构造出x，y
//     将x y还原成对应二进制表示输出即可
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100;
long long dig[maxn];
int w[maxn];
 
struct Node{
    int index;
    int val;
    bool operator < (const Node &x) const {
        return val<x.val;
    }
} arr[maxn];
 
int cnt;
long long ans1,ans2;
 
void init() {
    dig[0]=1;
    for (int i=1;i<=61;i++) {
        dig[i]=dig[i-1]*2;
    }
    ans1=0;
    ans2=0;
}
 
void parse(long long x) {
    cnt=0;
    int k=1;
    while (x) {
        if (x%2==1) {
            w[cnt]=k;
        } else {
            w[cnt]=0;
        }
        x=x>>1;
        k=k*2%3;
        cnt++;
    }
    return ;
}
 
void solve(long long a) {
     
//  for (int i=0;i<cnt;i++) {
//      printf("%d ", w[i]);
//  }printf("\n");
     
    ans1=a;
    ans2=a;
    int sum=0;
    int tot=0;
    for (int i=0;i<cnt;i++) {
        if (w[i]>0) {
            arr[tot].index=i;
            arr[tot].val=w[i];
            tot++;
            sum=sum+w[i];
            sum=sum%3;
        }
    }
    sort(arr,arr+tot);
     
//  for (int i=0;i<tot;i++) {
//      printf("%d %d\n", arr[i].index, arr[i].val);
//  }printf("%d\n",sum);
     
    if (sum==1) {
        if (arr[0].val==1) {
            ans1=ans1-dig[arr[0].index];
            if (arr[1].val==1) {
                ans2=ans2-dig[arr[1].index];
            } else {
                ans2=ans2-dig[arr[1].index]-dig[arr[2].index];
            }
        } else {
            ans1=ans1-dig[arr[0].index]-dig[arr[1].index];
            ans2=ans2-dig[arr[2].index]-dig[arr[3].index];
        }
    } else {
        if (arr[tot-1].val==2) {
            ans1=ans1-dig[arr[tot-1].index];
            if (arr[tot-2].val==2) {
                ans2=ans2-dig[arr[tot-2].index];
            } else {
                ans2=ans2-dig[arr[tot-2].index]-dig[arr[tot-3].index];
            }
        } else {
            ans1=ans1-dig[arr[tot-1].index]-dig[arr[tot-2].index];
            ans2=ans2-dig[arr[tot-3].index]-dig[arr[tot-4].index];
        }
    }
}
 
int main() {
    long long a;
    int T;
    scanf("%d", &T);
    init();
    while (T--) {
        scanf("%lld", &a);
        if (a%3==0) {
            printf("1 %lld\n", a);
            continue;
        }
        parse(a);
        solve(a);
        printf("2 %lld %lld\n", ans1, ans2);
    }
    return 0;
}