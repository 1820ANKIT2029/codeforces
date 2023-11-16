#include <stdio.h>

int main(){
    int x;
    scanf("%d",&x);
    int step=0;

    if(x>5){
        step = x/5;
        x -= (5*step);
    }
    if(x>0){
        step += 1;
    }
    
    printf("%d\n",step);
}