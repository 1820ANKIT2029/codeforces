#include <stdio.h>
void swap(char* a, char* b);

int main(){
    int n, t;
    scanf("%d%d",&n,&t);
    char arr[n+1];
    scanf("%s",arr);
    for(int i=0; i<t;i++){
        int j=1;
        while(j<n){
            if(arr[j-1]=='B' && arr[j]=='G'){
                swap(&arr[j-1], &arr[j]);
                j+=2;
            }
            else{
                j++;
            }
        }
    }
    printf("%s\n",arr);
}

void swap(char* a, char* b){
    char temp = *a;
    *a = *b;
    *b = temp;
}