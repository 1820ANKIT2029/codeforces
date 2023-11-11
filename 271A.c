#include <stdio.h>
#include <math.h>
int distinct(int arr[], int n);

int main(){
    int y;
    scanf("%d", &y);
    
    while(1){
        y++;
        int n = floor(log10(y)) + 1;
        int arr[n];
        int y_2 = y;
        int rem;
        for(int i=0; i<n; i++){
            rem = y_2%10;
            y_2 = y_2/10;
            arr[i] = rem;
        }
        if(distinct(arr, n)){
            break;
        }
    }
    printf("%d\n", y);

}

int distinct(int arr[], int n){
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i] == arr[j]){
                return 0;
            }
        }
    }
    return 1;
}