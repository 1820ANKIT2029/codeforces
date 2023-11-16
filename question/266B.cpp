#include <iostream>
#include <string>
using namespace std;
void swap(char* a, char* b);

int main(){
    int n, t;
    cin>>n>>t;
    string arr;
    cin>> arr;
    for(int i=0; i<t;i++){
        int j=0;
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
    for(char i : arr){
        cout<<i;
    }
    cout<<"\n";
}

void swap(char* a, char* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
