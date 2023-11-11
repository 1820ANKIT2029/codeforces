#include <stdio.h>

int main(){
    int n,group;
    scanf("%d",&n);
    int arr[2*n];
    group = 1;
    for(int i=0; i<n; i++){
        int p;
        scanf("%d",&p);
        arr[2*i] = p%10;
        p = p/10;
        arr[2*i+1] = p;
    }
    for(int i=1; i<2*n; i++){
        if(arr[i-1]==arr[i]){
            group++;
        }
    }
    printf("%d\n",group);
}