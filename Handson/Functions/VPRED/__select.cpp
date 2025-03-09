// #include"c7x_host_emulation.h"
#include "c7x.h"
#include <iostream>

using namespace std;

int main()
{
    cout<<"This is the program to undertsand the and ppp function \n";
    
    // float16 a = float16(0);
    // float16 b = float16(1);
    cout<<"A = ";
    // float16 a (0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1);
    float16 a (1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0);
    a.print();

    cout<<"B = ";
    float16 b (2,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1);
    b.print();

    __vpred pred_vec_1 = __cmp_lt_pred(a,b);  // this will have 64 ele and with only the req bit selected 
    pred_vec_1.print();

    float16 sample = float16(5);

    // now is 1 replace the 0 with 5 or else skip 
    float16 result = float16(0);
    cout<<"The result before select is : " ;
    result.print();

    result = __select(pred_vec_1, sample, result); 
    cout<<"The result after select is : " ;
    result.print();



}
