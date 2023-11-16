#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    float x = 0;
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
        
    }
    for(int i=0; i<n; i++){
        x += arr[i];
    }
    float output;
    output = x/n;
    printf("%f\n", output);
}