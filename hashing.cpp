#include<iostream>
#include "LinkedListHeader.h"
using namespace std;



int main(){
    int A[] = {1, 25,32,58,78,96,21,35,48};
    LinkedList<int> Hash[10];
    int i = 0;
    while(i<=8){
       Hash[A[i]%10].Insert_sorted(A[i]);
    i++;
    }
    for(i = 0;i<10;i++){
    Hash[i].Display();
    cout<<endl;
    }
   return 0; 
}
