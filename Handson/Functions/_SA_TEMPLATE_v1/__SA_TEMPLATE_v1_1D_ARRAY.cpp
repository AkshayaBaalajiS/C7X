#include <iostream>
#include "c7x.h"

using namespace std;

#define COL 510 

int main()
{
    cout<<"This is the program to understand the SA Template working like the SE template  \n";

    int32_t array[COL];

    for(int i=0;i<COL;i++)
    {
        array[i]=i+1;
    }

    cout<<"|------------------------------------------------------------------------|\n";

    for(int i=0;i<COL;i++)
    {
        cout<<array[i] << "   " ;
    }

    cout<<"\n|------------------------------------------------------------------------|\n";

    __SA_TEMPLATE_v1 satemplate = __gen_SA_TEMPLATE_v1();
    satemplate.VECLEN = __SA_VECLEN_16ELEMS;
    satemplate.DIMFMT = __SA_DIMFMT_1D;
    satemplate.ICNT0 = COL;
    satemplate.ICNT1 = 1;
    satemplate.ICNT2 = 1;
    satemplate.DIM1 = COL;
    satemplate.DIM2 = 0;

    __SA0_OPEN(satemplate);

    for(int i=0;i<COL;i+=16)
    {
        int16 int_vec = *__SA0ADV(int16,(void *)array);
        cout<<"Vector at : "<< i << endl;
        int_vec.print();
    }
    cout<<"\n|------------------------------------------------------------------------|\n";
    cout<<"Array now is : ";
    for(int i=0;i<COL;i++)
    {
        cout<<array[i] << "   " ;
    }
    cout<<endl;


}
