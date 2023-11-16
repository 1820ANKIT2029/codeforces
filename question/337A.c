#include <stdio.h>

void selection_sort(int arr[], int n){
    for(int i=0; i<n; i++){
        int min = i;
        for(int j=i; j<n; j++){
            if(arr[min]>arr[j]){
                min = j;
            }
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}
int main(){
    int n, m;
    scanf("%d%d",&n,&m);
    int arr[m];
    for(int i=0; i<m; i++){
        scanf("%d", &arr[i]);
    }
    selection_sort(arr, m);
    int gap = (m-n);
    int AminusB = arr[n-1] - arr[0];

    for(int i=0; i<=gap; i++){
        int a = arr[n-1+i] - arr[i];
        if (AminusB > a){
            AminusB = a;
        }    
    }

    printf("%d\n", AminusB);
}