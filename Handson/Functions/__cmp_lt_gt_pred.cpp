// #include"c7x_host_emulation.h"
#include "c7x.h"
#include <iostream>

using namespace std;

int main()
{
    cout<<"This is the program to undertsand the and ppp function \n";
    
    // float16 a = float16(0);
    // float16 b = float16(1);

    // another way of manual assigning 

    cout<<"A = ";
    // int16 a (0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1);
    // int16 a (1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0);
    // int16 a = int16(1);
    int16 a (3,6,5,4,5,4,5,4,5,4,5,4,5,4,5,4); 
    a.print();

    cout<<"B = ";
    int16 b (4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5);
    // int16 b (1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0);
    b.print();

    
    __vpred pred_vec_1 = __cmp_lt_pred(a,b);  // from reverse 
    pred_vec_1.print();

    // __vpred pred_vec_2 = __cmp_gt_pred(b,a);
    __vpred pred_vec_2 = __cmp_gt_pred(a,b);
    pred_vec_2.print();

}
