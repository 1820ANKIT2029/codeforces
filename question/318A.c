#include <stdio.h>

int main(){
    unsigned long long int n,k;
    scanf("%llu%llu",&n,&k);
    unsigned long long int size_o;
    unsigned long long int size_e;
    size_o = n%2==0?n/2:(n/2 + 1);
    size_e = n - size_o;
    if(k<=size_o){
        printf("%llu\n", 2*(k-1) + 1);
    }
    else{
        printf("%llu\n", 2*(k-size_o));
    }

}