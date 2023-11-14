#include <stdio.h>

int main(){
    int n, m;
    scanf("%d%d",&n, &m);
    int turns = n>m?m:n;

    if(turns%2==0){
        printf("Malvika\n");
    }
    else{
        printf("Akshat\n");
    }
}