#include <iostream>
#include "c7x.h"

using namespace std;

#define COL 20
#define ROW 5

int main()
{
    cout<<"This is the program to understand the SE Template working like SA template for DIMFMT 2D   \n";

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

    __SE_TEMPLATE_v1 setemplate = __gen_SE_TEMPLATE_v1();
    setemplate.VECLEN = __SE_VECLEN_16ELEMS;
    setemplate.DIMFMT = __SE_DIMFMT_2D;
    setemplate.ELETYPE = __SE_ELETYPE_32BIT;
    setemplate.ICNT0 = COL;
    setemplate.ICNT1 = ROW;
    setemplate.ICNT2 = 1;
    setemplate.DIM1 = COL;
    setemplate.DIM2 = 0;

    __SE0_OPEN(array,setemplate);

    for(int j=0;j<ROW;j++)
    {
        for(int i=0;i<COL;i+=16)
        {
            int16 int_vec = __SE0ADV(int16);
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