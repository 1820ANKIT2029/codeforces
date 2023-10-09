#include <stdio.h>

int main(){
    int n, k,score_k,output;
    scanf("%d%d",&n,&k);
    int score[n];
    for(int i=0;i<n;i++){
        scanf("%d",&score[i]);
    }
    score_k = score[k-1];
    output = 0;
    for(int i=0;i<n;i++){
        if(score[i]<=0){
            break;
        }
        else{
            if (score[i]>=score_k){
                output++;
            }
        }
    }
    printf("%d\n",output);
}