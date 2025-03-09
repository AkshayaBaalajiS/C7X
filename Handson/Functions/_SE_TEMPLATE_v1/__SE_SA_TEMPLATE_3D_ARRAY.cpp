#include <iostream>
#include "c7x.h"
using namespace std;

#define ROW 5
#define COL 32
#define CHANNEL 3

int main()
{
    cout<<"This is the program to understand the SE fetch + SA load\n";

    int32_t array[CHANNEL][ROW][COL];
    int32_t output_array [CHANNEL][ROW][COL];

    for(int i=0;i<CHANNEL;i++)
    {
        int counter =0;
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k++)
            {
                counter++;
                array[i][j][k] =  counter;
            }
        }
    }

    cout<<"|-----------------------------------------------------------------------------|\n";
    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k++)
            {
                cout<<array[i][j][k]<<"  "; 
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    cout<<endl;
    cout<<"|-----------------------------------------------------------------------------|\n";
    
    __SE_TEMPLATE_v1 setemplate = __gen_SE_TEMPLATE_v1();
    setemplate.ELETYPE = __SE_ELETYPE_32BIT;
    setemplate.VECLEN = __SE_VECLEN_16ELEMS;
    setemplate.DIMFMT = __SE_DIMFMT_3D;
    setemplate.ICNT0 = COL;
    setemplate.ICNT1 = ROW;
    setemplate.ICNT2 = CHANNEL;
    setemplate.DIM1 = COL;
    setemplate.DIM2 = ROW * COL;

    __SE0_OPEN(array,setemplate);

    __SA_TEMPLATE_v1 satemplate = __gen_SA_TEMPLATE_v1();
    satemplate.VECLEN = __SA_VECLEN_16ELEMS;
    satemplate.DIMFMT = __SA_DIMFMT_3D;
    satemplate.ICNT0 = COL;
    satemplate.ICNT1 = ROW;
    satemplate.ICNT2 = CHANNEL;
    satemplate.DIM1 = COL;
    satemplate.DIM2 = ROW * COL;

    __SA0_OPEN(satemplate);

    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k+=16)
            {
                int16 int_vec = __SE0ADV(int16);
                cout<<"The vector at " << i << "  " << j << "  " << k << endl; 
                int_vec.print();

                __vpred vpredVec = __SA0_VPRED(int16);
                vpredVec.print();
                __vstore_pred(vpredVec, __SA0ADV(int16,output_array),int_vec) ;
                
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }

    cout<<"|-----------------------------------------------------------------------------|\n";
    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k++)
            {
                cout<<output_array[i][j][k]<<"  "; 
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    cout<<endl;
    cout<<"|-----------------------------------------------------------------------------|\n";
}