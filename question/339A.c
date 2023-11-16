#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int compare(const void* num1, const void* num2) // comparing function  
{  
    int a = *(int*) num1;  
    int b = *(int*) num2;  
    if(a > b){  
        return 1;  
    }  
    else if(a < b){  
        return -1;  
    }  
    return 0;  
}  

int main(){
    char s[101];
    scanf("%s",s);
    int len = strlen(s);
    int k = ceil(((float)len)/2);
    int num_arr[k];
    for(int i=0,j=0;i<len;i+=2,j++){
        num_arr[j] = atoi(&s[i]);
    }

    qsort(num_arr,k,sizeof(int),compare);

    printf("%d",num_arr[0]);
    for(int i=1;i<k;i++){
        printf("+%d",num_arr[i]);
    }
    printf("\n");

}
