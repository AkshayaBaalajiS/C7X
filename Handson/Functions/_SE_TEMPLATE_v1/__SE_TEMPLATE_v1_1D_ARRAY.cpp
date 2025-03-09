#include <iostream>
// #include "c7x_host_emulation.h"
#include "c7x.h"

#define ARRAY_SIZE 544
using namespace std;

int main()
{
    cout<<"This is the program to understand the SE Template open and SEADV\n";

    int32_t arr[ARRAY_SIZE];

    for(int i=0;i<ARRAY_SIZE;i++)
    {
        arr[i]=i+1;
    }

    cout<<"Array is : ";
    for (int i = 0; i < ARRAY_SIZE; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    int32_t * ptr = arr ;
    __SE_TEMPLATE_v1 setemplate = __gen_SE_TEMPLATE_v1();
    setemplate.ICNT0 = ARRAY_SIZE;
    setemplate.ICNT1 = 1;
    setemplate.ICNT2 = 1;
    setemplate.DIM1 = 0;
    setemplate.DIM2 = 0;
    setemplate.ELETYPE = __SE_ELETYPE_32BIT ;
    setemplate.VECLEN = __SE_VECLEN_16ELEMS ;

    __SE0_OPEN((void *)arr,setemplate);

    for(int i=0;i<ARRAY_SIZE;i+=16)
    {
        int16 int_vec= __SE0ADV(int16);
        int_vec.print();            
    }  

}