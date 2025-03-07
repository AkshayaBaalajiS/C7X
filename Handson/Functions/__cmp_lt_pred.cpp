#include <iostream>
#include <c7x.h>

using namespace std;

int main()
{
    cout<<"This is the program to understand the cmp_lt_pred for all type of input ";

    int16 arr_1 (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
    cout<<"\nArray 1 = ";
    arr_1.print();

    int16 arr_2 (0,3,2,5,4,7,6,9,8,11,12,13,1,14,15,17);
    cout<<"Array 2 = ";
    arr_2.print();

    // predicate vector is 
    __vpred pred_vec  = __cmp_lt_pred(arr_1,arr_2); 
    pred_vec.print();  // for the 16 elements 16 *4 = 64 ele came and each ele took 4 bits 

    cout<<"\n|-------------------------------------------------------------------------------------\n";
    
    int8 arr_3 (1,2,3,4,5,6,7,8);
    cout<<"\nArray 3 = ";
    arr_3.print();

    int8 arr_4 (0,3,2,5,4,7,6,9);
    cout<<"Array 4 = ";
    arr_4.print();

    // predicate vector is 
    __vpred pred_vec_1  = __cmp_lt_pred(arr_3,arr_4); 
    pred_vec_1.print();  // for the 8 elements 8 *4 = 32 ele came so last 32 elements are occupied with the values we need 

    
    
}