#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char a_1[101],a_2[101];
    int x=0;
    scanf("%s",a_1);
    scanf("%s",a_2);
    for(int i=0;i<strlen(a_1);i++){
        x = tolower(a_1[i]) - tolower(a_2[i]);
        if (x > 0){
            break;
        }
        else if(x < 0){
            break;
        }
    }
    if (x > 0){
        printf("1\n");
    }
    else if(x == 0){
        printf("0\n");
    }
    else{
        printf("-1\n");
    }
    
}