#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    char* h= "hate";
    char* l = "love";
    int i = 1;
    while(i<=n){
        printf("I ");
        if(i%2==0){
            printf("%s ",l);
        }
        else{
            printf("%s ",h);
        }
        if(i==n){
            printf("it");
        }
        else{
            printf("that ");
        }
        i++;
    }
    printf("\n");
}