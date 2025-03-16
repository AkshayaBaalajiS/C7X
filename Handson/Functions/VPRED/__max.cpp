#include <iostream>
#include "c7x.h"

using namespace std;

int main()
{
    cout<<"This is the program to find the max \n";

    float16 a_fvec = (1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7);
    float16 b_fvec = (0,0,0,0,1,2,3,4,5,6,7,8,9,1,2,3);
    
    float16 output  = __max(a_fvec, b_fvec);
    output.print();

}