#include <stdio.h>

int main(){
    char teams[101];
    scanf("%s", teams);
    int sum = 0;
    int i=0;
    int flag = 0;
    char a = teams[0];
    while(teams[i]!='\0'){
        if(a==teams[i]){
            sum++;
        }
        else{
            sum = 0;
            a = teams[i];
            sum++;
        }
        if(sum == 7){
            printf("YES\n");
            return 0;
        }
        i++;
    }
    printf("NO\n");
}