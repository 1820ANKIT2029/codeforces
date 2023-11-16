#include <stdio.h>

int main(){
    int n, h;
    scanf("%d%d",&n,&h);
    int a[n];
    int output = 0;
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        if (a[i]>h){
            output += 2;
        }
        else{
            output++;
        }
    }
    printf("%d\n",output);
}