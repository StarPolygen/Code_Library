//签到 模拟
#include<cstdio>
using namespace std;
const int maxn=1000005;


struct Node{
    int pre;
    int next;
    int val;
} a[maxn];

int head;


void dele(int p) {
    if (p==head) {
        return ;
    }
    a[a[p].pre].next=a[p].next;
    a[a[p].next].pre=a[p].pre;
    a[head].pre=p;
    a[p].pre=-1;
    a[p].next=head;
    head=p;
    return ;
}

int main() {
    int n,m;
    scanf("%d%d", &n,&m);
    head=1;
    for (int i=1;i<=n;i++) {
        int x;
        scanf("%d", &x);
        a[i].val=x;
        a[i].pre=i-1;
        a[i].next=i+1;
    }
    a[1].pre=-1;
    a[n].next=-1;
    
    for (int i=1;i<=m;i++) {
        int x;
        scanf("%d", &x);
        dele(x);
    }
    int p=head;
    while (p!=-1) {
        printf("%d ", a[p].val);
        p=a[p].next;
    }
    return 0;
}

/*
5 3
1 2 3 4 5
3
4
3

5 4
1 2 3 4 5
5
5 
5
5
*/