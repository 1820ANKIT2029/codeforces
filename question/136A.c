#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    int output[n];
    for(int i=0; i<n; i++){
        output[arr[i]-1] = i+1;
    }
    for(int i=0; i<n; i++){
        printf("%d ",output[i]);
    }
    printf("\n");
}