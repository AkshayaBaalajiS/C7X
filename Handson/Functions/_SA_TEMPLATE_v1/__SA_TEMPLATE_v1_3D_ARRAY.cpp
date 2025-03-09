#include <iostream>
#include "c7x.h"

using namespace std;

#define COL 32
#define ROW 5 
#define CHANNEL 3

int main()
{
    cout<<"This is the program to understand the 3D array fetch using the SA \n";

    int32_t array[CHANNEL][ROW][COL];

    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            int counter =0 ;
            for(int k=0;k<COL;k++)
            {
                counter++;
                array[i][j][k] = counter ;
            }
        }
    }

    cout<<"|-------------------------------------------------------------|\n";

    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k++)
            {
                cout<<array[i][j][k] << "  " ;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    cout<<endl;

    cout<<"|-------------------------------------------------------------|\n";

    __SA_TEMPLATE_v1 satemplate = __gen_SA_TEMPLATE_v1();
    satemplate.VECLEN = __SA_VECLEN_16ELEMS;
    satemplate.DIMFMT  = __SA_DIMFMT_3D;
    satemplate.ICNT0 = COL;
    satemplate.ICNT1 = ROW ;
    satemplate.ICNT2 = CHANNEL ;
    satemplate.DIM1 = COL;
    satemplate.DIM2 = ROW * COL;

    __SA0_OPEN(satemplate);

    for(int i=0;i<CHANNEL ; i++)
    {
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k+=16)
            {
                int16 int_vec = *__SA0ADV(int16, array);
                cout<<"The vector " << i << " " << j << " " << k  <<endl;
                int_vec.print();

            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }


}