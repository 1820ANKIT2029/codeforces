#include <stdio.h>

void sort(int arr[], int n){
    for(int i=0; i<n; i++){
        int min=i;
        for(int j=i; j<n; j++){
            if(arr[min] < arr[j]){
                min = j;
            }
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    int sum = 0;
    int sum_2 = 0;
    for(int i=0; i<n; i++){
        scanf("%d",&arr[i]);
        sum += arr[i];
    }
    sort(arr, n);
    for(int i=0; i<n; i++){
        sum_2 += arr[i];
        sum -= arr[i];
        if(sum_2 > sum){
            printf("%d\n",i+1);
            return 0;
        }
    }
}