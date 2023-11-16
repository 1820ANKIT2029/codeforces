#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    int matrix[5][5];
    int one_r,one_c;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            scanf("%d",&matrix[i][j]);
            if (matrix[i][j]==1){
                one_r = i+1; one_c = j+1;
            }
        }
    }
    int output = abs(3-one_r) + abs(3-one_c);
    printf("%d\n",output);
}