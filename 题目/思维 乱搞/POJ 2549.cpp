//POJ 2549
//思维题  给定集合，求满足a+b+c=d的最大的d，abcd都是集合中的*不同*元素
//分别求出所有a+b 和 d-c  并将他们分别排序 归并比较 过程中维护最大的d即可

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
#define maxn 1000010
#define ll long long
using namespace std;

struct node{
    node(){}
    node(int a,int b,int val){
        this->a=a;
        this->b=b;
        this->val=val;
    }
    int a,b,val;
};

int cmp(node a,node b){
    return a.val<b.val;
}

node cha[maxn];
node he[maxn];
int arr[1010];
int main() {
    int n;
    while(scanf("%d",&n)){
        if(n==0) break;
        memset(cha,0,sizeof(cha));
        memset(he,0,sizeof(he));
        memset(arr,0,sizeof(arr));

        for(int i=1;i<=n;i++){
            scanf("%d",&arr[i]);
        }
        int tot1=0,tot2=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==j) continue;
                if((arr[i]-arr[j])<= -536870913) continue;
                cha[tot1++]=node(i,j,arr[i]-arr[j]);
                he[tot2++]=node(i,j,arr[i]+arr[j]);
            }
        }
        sort(cha,cha+tot1,cmp);
        sort(he,he+tot2,cmp);


// printf("%d\n%d\n",tot1,tot2);
//         for(int i=0;i<tot1;i++){
            
//             printf("%d %d %d\n",arr[cha[i].a],arr[cha[i].b],cha[i].val);
//         }
//     printf("\n\n");
//         for(int i=0;i<tot2;i++){
//             printf("%d %d %d\n",arr[he[i].a],arr[he[i].b],he[i].val);
//         }


        int maxd= -536870913;
        for(int i=0;i<tot1;){
            for(int j=0;j<tot2;){
                if(cha[i].val==he[j].val){
                    if(cha[i].a!=he[j].a&&cha[i].b!=he[j].a&&cha[i].a!=he[j].b&&cha[i].b!=he[j].b){ 
                        maxd=max(maxd,arr[cha[i].a]);
                    }
                    i++;
                }
                else if(cha[i].val<he[j].val){
                    i++;
                }
                else j++;
                if(i==tot1||j==tot2) goto S;
            }
        }
        S:
        if(maxd==-536870913) printf("no solution\n");
        else printf("%d\n",maxd);

    }
    

    return 0;
}

/*
5
2 
3 
5 
7 
12
5
2 
16 
64 
256 
1024
0
8
*/