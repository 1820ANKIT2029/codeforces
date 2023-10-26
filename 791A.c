#include <stdio.h>

int main(){
    int limak,bob;
    scanf("%d%d",&limak,&bob);

    int i=1;
    while(1){
        limak = 3*limak;
        bob = 2*bob;
        if (limak>bob){
            break;
        }
        i++;
    }
    printf("%d\n",i);
}