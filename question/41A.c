#include <stdio.h>
#include <string.h>

int main(){
    char t[101], s[101];
    scanf("%s%s",t,s);
    int output = 1;
    int len = strlen(t);

    for(int i=0;i<len;i++){
        if (t[i] != s[len-i-1]){
            output = 0;
            break;
        }
    }
    if (output==1){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
}