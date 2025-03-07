// #include"c7x_host_emulation.h"
#include "c7x.h"
#include <iostream>

using namespace std;

int main()
{
    cout<<"This is the program to undertsand the and ppp function \n";
    
    float16 a = float16(0);
    float16 b = float16(1);

    
    __vpred pred_vec_1 = __cmp_lt_pred(a,b);
    pred_vec_1.print();

    // __vpred pred_vec_2 = __cmp_gt_pred(b,a);
    __vpred pred_vec_2 = __cmp_gt_pred(a,b);
    pred_vec_2.print();

    __vpred pred_vec_3 = __and_ppp(pred_vec_1,pred_vec_2);
    pred_vec_3.print();
}
