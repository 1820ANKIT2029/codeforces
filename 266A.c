#include <stdio.h>

int main(){
    int input_no;
    scanf("%d",&input_no);
    char store[input_no+1];
    scanf("%s",store);
    int sum = 0;

    for(int i=0;i<input_no;i++){
        if (store[i] == store[i+1]){
            sum++;
        } 
    }
    printf("%d\n",sum);

}