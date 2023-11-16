#include <stdio.h>

int main(){
    char text[101];
    scanf("%s",text);
    for(int i=0; text[i]!='\0'; i++){
        if(text[i]=='H' || text[i]=='Q' || text[i]=='9'){
            printf("YES\n");
            return 0;
        }
    }
    printf("NO\n");
}