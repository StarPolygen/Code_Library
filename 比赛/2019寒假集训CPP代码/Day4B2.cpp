#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
using namespace std;
const int maxn = 50000+10;
int n,m;
int s[maxn],top;
struct node
{
    int l,r;
    int ls,rs,ms;
} a[maxn<<2];

void init(int l,int r,int i)
{
    a[i].l = l;
    a[i].r = r;
    a[i].ls = a[i].rs = a[i].ms = r-l+1;
    if(l!=r)
    {
        int mid = (l+r)>>1;
        init(l,mid,i*2);
        init(mid+1,r,2*i+1);
    }
}

void insert(int i,int t,int x)
{
    if(a[i].l == a[i].r)
    {
        if(x==1)  a[i].ls = a[i].rs = a[i].ms = 1;//ÐÞ¸´
        else  a[i].ls = a[i].rs = a[i].ms = 0;//ÆÆ»µ
        return ;
    }
    int mid = (a[i].l+a[i].r)>>1;
    if(t<=mid) insert(2*i,t,x);
    else insert(2*i+1,t,x);
	a[i].ls = a[2*i].ls;
    a[i].rs = a[2*i+1].rs;
    a[i].ms = max(max(a[2*i].ms,a[2*i+1].ms),a[2*i].rs+a[2*i+1].ls);
    if(a[2*i].ls == a[2*i].r-a[2*i].l+1)  a[i].ls += a[2*i+1].ls;
    if(a[2*i+1].rs == a[2*i+1].r-a[2*i+1].l+1)   a[i].rs += a[2*i].rs;
}
 

int query(int i,int t)
{
    if(a[i].l == a[i].r || a[i].ms == 0 || a[i].ms == a[i].r-a[i].l+1)
        return a[i].ms;
    int mid = (a[i].l+a[i].r)>>1;
    if(t<=mid){
        if(t>=a[2*i].r-a[2*i].rs+1)
            return query(2*i,t)+query(2*i+1,mid+1);
        else
            return query(2*i,t);
    }
    else{
        if(t<=a[2*i+1].l+a[2*i+1].ls-1)
            return query(2*i+1,t)+query(2*i,mid);
        else
            return query(2*i+1,t);
    }
}
 
int main()
{
    int i,j,x;
    char ch[2];
    while(~scanf("%d%d",&n,&m)){
        top = 0;
        init(1,n,1);
        while(m--) {
            scanf("%s",ch);
            if(ch[0] == 'D'){
                scanf("%d",&x);
                s[top++] = x;
                insert(1,x,0);
            }
            else if(ch[0] == 'Q'){
                scanf("%d",&x);
                printf("%d\n",query(1,x));
            }
            else{
                if(x>0){//
	                x = s[--top];
                    insert(1,x,1);
                }
            }
        }
    }
    return 0;
}

