#include <stdio.h>
#include <stdlib.h>

int main(){
    int problem_no,output,sum,a,b,c;
    scanf("%d",&problem_no);
    output = 0;
    for(int i=0;i<problem_no;i++){
        scanf("%d%d%d",&a,&b,&c);
        sum = a+b+c;
        if (sum>=2){
            output++;
        }
    }
    printf("%d\n",output);
}