#include <stdio.h>

int main(){
    int w;
    scanf("%d",&w);
    if (w == 2){
        printf("NO\n");
    }
    else{
        if(w%2 != 0){
            printf("No\n");
        }
        else{
            printf("Yes\n");
        }
    }
    
}