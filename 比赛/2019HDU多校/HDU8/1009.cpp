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

using namespace std;
const double eps = 1e-8;
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0)return -1;
    else return 1;
}
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int x1, x2, y1, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int xx, xd, yx, yd;
        if(x1<x2){
            xx = x1;
            xd = x2;
        }else{
            xx = x2;
            xd = x1;
        } 
        if(y1<y2){
            yx = y1;
            yd = y2;

        }else{
            yx = y2;
            yd = y1;
        }
        int xx1, xd1, yx1, yd1;
        xx1 = xx;
        xd1 = xd;
        yx1 = yx;
        yd1 = yd;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if(x1<x2){
            xx = x1;
            xd = x2;
        }else{
            xx = x2;
            xd = x1;
        } 
        if(y1<y2){
            yx = y1;
            yd = y2;

        }else{
            yx = y2;
            yd = y1;
        }

        //读入完毕 构造两矩形篱笆的边界
        //重合：2
        if(xx1==xx&&yx1==yx&&xd1==xd&&yd1==yd){
            printf("2\n");
            continue;
        }
        //一个在一个内部 可能为3或4
        if(xx1>=xx && xx1<=xd && yx1 >= yx && yx1 <= yd && xd1>=xx && xd1<=xd && yd1>=yx && yd1<=yd){
            if((yd1 == yd && yx1==yx && xd1 < xd && xx1 > xx)||(xd1==xd&&xx1==xx&&yd1<yd&&yx1>yx))
                printf("4\n");
            else printf("3\n");
            continue;
        }
        if(xx>=xx1 && xx<=xd1 && yx >= yx1 && yx <= yd1 && xd>=xx1 && xd<=xd1 && yd>=yx1 && yd<=yd1){
            if((yd1 == yd && yx1==yx && xd1 > xd && xx1 < xx)||(xd1==xd&&xx1==xx&&yd1>yd&&yx1<yx))
                printf("4\n");
            else 
            printf("3\n");
            continue;
        }
        //相交面积为0 3
        if(!(max(xx1,xx)<min(xd,xd1)&&max(yx1,yx)<min(yd1,yd))){
            printf("3\n");
            continue;
        }
        //十字形
        if(xx1 > xx && xx1 <xd && xd1 > xx && xd1 < xd && yx1 <yx && yd1 > yd){
            printf("6\n");
            continue;
        }
        if(xx > xx1 && xx <xd1 && xd > xx1 && xd < xd1 && yx <yx1 && yd > yd1){
            printf("6\n");
            continue;
        }
        //凸字形
        int ch = 0;
        int fl = 0;
        if(xx1==xx && 1ll*(yx-yx1)*(yd-yd1)<0)
        {   ch++;
            fl = 1;
        }
        if (xd1 == xd && 1ll*(yx-yx1)*(yd-yd1)<0 )
        {   ch++;
            fl = 2;
        }
        if (yx1 == yx && 1ll*(xx-xx1)*(xd-xd1)<0)
        {   ch++;
            fl = 3;
        }
        if (yd1 == yd && 1ll*(xx-xx1)*(xd-xd1)<0)
        {   ch++;
            fl = 4;
        }
        if (ch == 1)
        {
            printf("5\n");
            continue;
        }
        else{
            printf("4\n");
        }

    }
    return 0;
}