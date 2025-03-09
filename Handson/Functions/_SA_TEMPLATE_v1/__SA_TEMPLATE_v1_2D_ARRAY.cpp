#include <iostream>
#include "c7x.h"

using namespace std;

#define COL 20 
#define ROW 5

int main()
{
    cout<<"This is the program to understand the SA Template working like SE template for DIMFMT 2D   \n";

    int32_t array[ROW][COL];
    
    int counter =0;
    for(int j=0;j<ROW;j++)
    {
        for(int i=0;i<COL;i++)
        {
            array[j][i]=i+1;
        }
    }

    cout<<"|------------------------------------------------------------------------|\n";

    for(int j=0;j<ROW;j++)
    {
        for(int i=0;i<COL;i++)
        {
            cout<<array[j][i]<<   "   " ; 
        }
        cout<<endl;
    }

    cout<<"\n|------------------------------------------------------------------------|\n";

    __SA_TEMPLATE_v1 satemplate = __gen_SA_TEMPLATE_v1();
    satemplate.VECLEN = __SA_VECLEN_16ELEMS;
    satemplate.DIMFMT = __SA_DIMFMT_2D;
    satemplate.ICNT0 = COL;
    satemplate.ICNT1 = ROW;
    satemplate.ICNT2 = 1;
    satemplate.DIM1 = COL;
    satemplate.DIM2 = 0;

    __SA0_OPEN(satemplate);

    for(int j=0;j<ROW;j++)
    {
        for(int i=0;i<COL;i+=16)
        {
            int16 int_vec =int16(0);
            int_vec= *__SA0ADV(int16,(void *)array);
            cout<<"Vector at : "<< i << endl;
            int_vec.print();
        }
        cout<<endl;
    }
    cout<<"\n|------------------------------------------------------------------------|\n";
    cout<<"Array now is : \n";
    for(int j=0;j<ROW;j++)
    {
        for(int i=0;i<COL;i++)
        {
            cout<<array[j][i] << "   " ;
        }
        cout<<endl;
    }
    cout<<endl;

}