#include<bits/stdc++.h>
#define ll long long
using namespace std;

char arr[100][100];
struct node{
    char tag;
    int num;
    node(){tag='0';num=0;}
    node(char _tag, int _num) : tag(_tag), num(_num) {}
};
node cnt[5];
int cmp(node a,node b){
    return a.num > b.num;
}
int main() {
    memset(arr,0,sizeof(arr));
    memset(cnt,0,sizeof(cnt));
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    cnt[1]=node('A',a);
    cnt[2]=node('B',b);
    cnt[3]=node('C',c);
    cnt[4]=node('D',d);
    sort(cnt+1,cnt+4+1,cmp);

    node rk1=cnt[1];
    node rk2=cnt[2];
    node rk3=cnt[3];
    node rk4=cnt[4];
    int hang=2,lie=2;
    rk1.num--;    //此处取出一个rk1
    rk2.num--;    //此处取出一个rk2
    rk3.num--;
    rk4.num--;
    while(rk2.num!=0&&rk1.num!=0){
        if(lie==50){
            lie=2; hang++;
        }
        if((hang+lie)%2==0){
            arr[hang][lie]=rk1.tag;
            lie++;
            rk1.num--;
        }else{
            arr[hang][lie]=rk2.tag;
            lie++;
            rk2.num--;
        }
    }
    
    int hang2=hang+3; int lie2=2;
    while(rk4.num!=0&&rk3.num!=0){
        if(lie2==50){
            lie2=2; hang2++;
        }
        if((hang2+lie2)%2==0){
            arr[hang2][lie2]=rk3.tag;
            lie2++;
            rk3.num--;
        }else{
            arr[hang2][lie2]=rk4.tag;
            lie2++;
            rk4.num--;
        }
    }
    
    for(int i=1;i<=50;i++) arr[1][i]=rk3.tag;
    for(int i=1;i<=hang;i++) arr[i][1]=rk3.tag;
    for(int i=1;i<=hang;i++) arr[i][50]=rk3.tag;
    if(lie<50) for(int i=lie;i<=50;i++) arr[hang][i]=rk3.tag;
    for(int i=1;i<=50;i++) arr[hang+1][i]=rk3.tag;

    for(int i=1;i<=50;i++) arr[hang+2][i]=rk1.tag;
    for(int i=hang+3;i<=hang2;i++) arr[i][1]=rk1.tag;
    for(int i=hang+3;i<=hang2;i++) arr[i][50]=rk1.tag;
    if(lie2<50) for(int i=lie2;i<=50;i++) arr[hang2][i]=rk1.tag;
    for(int i=1;i<=50;i++) arr[hang2+1][i]=rk1.tag;

    node ac[2]; int tot=0;
    node wa[2]; int tot2=0;
    if(rk1.num!=0)   ac[tot++]=rk1; 
    if(rk2.num!=0)   ac[tot++]=rk2;
    if(rk3.num!=0)   ac[tot++]=rk3;
    if(rk4.num!=0)   ac[tot++]=rk4;
    for(int i=1;i<=50;i++) arr[hang2+2][i]=rk2.tag;
    if(tot==2){
        int hang3=hang2+3; int lie3=1;
        char zuihou;
        while(ac[0].num!=0&& ac[1].num!=0){
            if(lie3==50){
                lie3=1; hang3++;
            }
            if((hang3+lie3)%2==0){
                arr[hang3][lie3]=ac[0].tag;
                lie3++;
                ac[0].num--;
                if(ac[0].num==0) zuihou=ac[0].tag;
            }else{
                arr[hang3][lie3]=ac[1].tag;
                lie3++;
                ac[1].num--;
                if(ac[1].num==0) zuihou=ac[1].tag;
            }
        }
        node shengyu;
        if(ac[0].num!=0) shengyu=ac[0];
        else shengyu=ac[1];
        for(int i=lie3;i<=50;i++) arr[hang3][i]=zuihou;
        for(int i=hang3+1;i<=50;i++){
            if((i-hang3-1)%2==0){
                for(int j=1;j<=50;j++) arr[i][j]=rk4.tag;
                continue;
            }
            for(int j=1;j<=50;j++){
                if(j%2==0&&shengyu.num!=0){
                    arr[i][j]=shengyu.tag;
                    shengyu.num--;
                }else{
                    arr[i][j]=rk4.tag;
                }
            }
        }
    }
    else if(tot==1){
        for(int i=hang2+3;i<=50;i++){
            if((i-hang2-3)%2==0){
                for(int j=1;j<=50;j++){
                    arr[i][j]=rk4.tag;
                }
                continue;
            } 
            for(int j=1;j<=50;j++){
                if(j%2==0&&ac[0].num!=0){
                    arr[i][j]=ac[0].tag;
                    ac[0].num--;
                }else{
                    arr[i][j]=rk4.tag;
                }
            }
        }
    }
    else{
        for(int i=1;i<=50;i++) arr[hang2+3][i]=rk4.tag;
    }
   

    


    printf("50 50\n");
    for(int i=1;i<=50;i++){
        for(int j=1;j<=50;j++){
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}