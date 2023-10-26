#include <stdio.h>

int main(){
    int k,n,w;
    scanf("%d%d%d",&k,&n,&w);
    int total_cost = k*((w*(w+1))/2);
    int borrow = 0;
    if(total_cost > n){
        borrow += (total_cost - n);
    }

    printf("%d\n",borrow);
}