#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    int a,b,max,present_person;
    max = 0;
    present_person = 0;

    for(int i=0;i<n;i++){
        scanf("%d%d",&a,&b);
        present_person -= a;
        present_person += b;
        if (present_person>max){
            max = present_person;
        }
    }
    printf("%d\n",max);
}