#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d",&arr[i]);
    }
    int min=0,max=0;
    for(int i=0; i<n; i++){
        if(arr[i]>arr[max]){
            max = i;
        }
        if(arr[i] <= arr[min]){
            min = i;
        }
    }
    int output = 0;
    if(max>min){
        output += max;
        output += (n-min-2);
    }
    else{
        output += max;
        output += (n-min-1);
    }
    printf("%d\n",output);
}