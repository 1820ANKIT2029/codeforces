#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d",&arr[i]);
    }
    int max = 1;
    int sum=1;
    for(int i=1; i<n; i++){
        if(arr[i-1]<=arr[i]){
            sum++;
            if(sum>max){
                max = sum;
            }
        }
        else{
            sum = 1;
        }
    }
    printf("%d\n", max);
}