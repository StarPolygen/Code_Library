#include<bits/stdc++.h>
#define ll long long
using namespace std;

int arr[10][10];
int d[10];
int main() {
    int T;
    scanf("%d", &T);
    while(T--){
        memset(arr, 0, sizeof arr);
        memset(d, 0, sizeof(d));
        for (int i = 1; i <= 5;i++){
            int a, b;
            scanf("%d%d", &a, &b);
            arr[a][b] = 1, arr[b][a] = 1;
            d[a]++;
            d[b]++;
        }
        int two = 0, three = 0, four = 0;
        int th = 0;
        for (int i = 1; i <= 6;i++){
            // printf("%d ", d[i]);
            if(d[i]==2)
                two++;
            if(d[i]==3){
                three++;
                th = i;
            }
            if(d[i]==4)
                four++;
        }
        //  printf("%d %d %d", two, three, four);
        if(four==1){
            printf("2,2-dimethylbutane\n");
            continue;
        }
        else if(three==2){
            printf("2,3-dimethylbutane\n");
            continue;

        }else if(two==4){
            printf("n-hexane\n");
            continue;
        }else if(three==1){
            int two0=0;
            for (int i = 1; i <= 6;i++){
                if(arr[th][i]==1){
                    if(d[i]==2)
                        two0++;
                }
            }
            if(two0==2){
                printf("3-methylpentane\n");
                continue;
            }else{
                printf("2-methylpentane\n");
                continue;
            }
        }else{

        }
       
    }
    return 0;
}