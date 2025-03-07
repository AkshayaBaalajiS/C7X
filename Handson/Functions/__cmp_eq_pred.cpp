#include <iostream>
#include "c7x.h"
using namespace std;

int main()
{
    cout<<"This the program to understand the cmp_eq_pred \n";

    int16 vec_1 (1,2,3,4,5,6,7,8,9,10,0,1,2,3,4,5);
    cout<<"Vec_1 = ";
    vec_1.print();

    int16 vec_2 (1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8);
    cout<<"Vec_2 = " ;
    vec_2.print();

    __vpred pred_vec = __cmp_eq_pred(vec_1,vec_2);
    pred_vec.print();
     
}