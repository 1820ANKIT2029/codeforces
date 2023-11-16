#include <stdio.h>

int main(){
    int num,A,D;
    scanf("%d",&num);
    char game[num+1];
    scanf("%s", game);
    A=0;
    D=0;
    for(int i=0;i<num;i++){
        if(game[i] == 'A'){
            A++;
        }
        else{
            D++;
        }
    }
    if(A>D){
        printf("Anton\n");
    }
    else if(A<D){
        printf("Danik\n");
    }
    else{
        printf("Friendship\n");
    }
}