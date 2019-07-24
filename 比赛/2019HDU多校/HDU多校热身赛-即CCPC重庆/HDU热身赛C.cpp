#include<bits/stdc++.h>
using namespace std;

struct backpag{
    int indexx;
    int x;
}arr[100010];

int cmp(const backpag &xx,const backpag &yy){    return xx.x<yy.x;}
int vis[100010];
int main() {
    int cas=1;
    int T;   scanf("%d",&T);
    while(T--)  {
        int n;    scanf("%d",&n);
        for(int i=1;i<=n;i++)    {
            scanf("%d",&arr[i].x);
            arr[i].indexx=i;
            vis[i]=0;
        }

        sort(arr+1,arr+1+n,cmp);
        
        int flag=1,pre=1,cnt1=1,cnt2=1;
        for(int i=1;i<=n;i++) {
            while(cnt1+cnt2<=n-i+1&&pre<arr[i].x)  {
                cnt1=cnt1*2; cnt2=cnt2*2;
                pre++;
            }
            if(cnt1+cnt2>n-i+1) {
                flag=0;
                break;
            }
            if(cnt1) {
                cnt1--;
                vis[arr[i].indexx]=1;
            }
            else  cnt2--;
            if(!cnt1 && !cnt2) break;  
        }
        printf("Case %d: ",cas++);
        if(flag==0 || cnt1 || cnt2) puts("NO");
        else
        {
            puts("YES");
            for(int i=1;i<=n;i++)
            {
                printf("%d",vis[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
