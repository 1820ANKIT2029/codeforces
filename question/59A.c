#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char word[101];
    scanf("%s",word);
    int l,u;
    l=0;
    u=0;

    for(int i=0;i<strlen(word);i++){
        if(islower(word[i])){
            l++;
        }
        else{
            u++;
        }
    }

    if(l>=u){
        for(int i=0;i<strlen(word);i++){
            printf("%c",tolower(word[i]));
        }
        printf("\n");
    }
    else{
        for(int i=0;i<strlen(word);i++){
            printf("%c",toupper(word[i]));
        }
        printf("\n");
    }
}