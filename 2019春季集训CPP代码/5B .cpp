# include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

char maze[10010][80];
int next[10010];
int r,c;

int get_nextc(int cnt){
    int i=0,j=-1;
    next[0]=-1;
    while(i<c){
        if(j==-1||maze[cnt][i]==maze[cnt][j]) {
            i++;
            j++;
            next[i]=j;
        }
        else j=next[j];
    }
    return c-next[c];
}

int get_nextr(int cnt){
    int i=0,j=-1;
    next[0]=-1;
    while(i<r) {
        if(j==-1||maze[i][cnt]==maze[j][cnt]){
            i++;
            j++;
            next[i]=j;
        }
        else j=next[j];
    }
    return r-next[r];
}

int main(){
    while(~scanf("%d%d",&r,&c)) {
        for(int i=0;i<r;i++){
        	scanf("%s",maze[i]);
		}
        int a=0,b=0;
        for(int i=0;i<r;i++){
        	a=max(a,get_nextc(i));
		}
        for(int i=0;i<c;i++){
        	b=max(b,get_nextr(i));
		}
        printf("%d\n",a*b);
    }
    return 0;
}

