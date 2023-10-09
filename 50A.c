#include <stdio.h>
#include <math.h>

int main(){
    int m, n, output;
    scanf("%d%d",&m,&n);
    output = floor((m*n)/2);
    printf("%d\n",output);
}