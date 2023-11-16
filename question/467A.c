#include <stdio.h>

int main(){
    int n,sum;
    scanf("%d",&n);
    sum = 0;
    for(int i=0; i<n; i++){
        int p, q;
        scanf("%d%d",&p,&q);
        if((q-p)>=2){
            sum += 1;
        }
    }
    printf("%d\n",sum);
}