#include <iostream>
#include "c7x.h"

using namespace std;

#define COL 16
#define ROW 5
#define CHANNEL 3
#define FOURD 2

int main()
{
    cout<<"This is the program to understand the SE template using 4d array \n";

    int32_t array[FOURD][CHANNEL][ROW][COL];

    for(int i=0;i<FOURD;i++)
    {
        for(int j=0;j<CHANNEL;j++)
        {
            int counter =0;
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL;l++)
                {
                    array[i][j][k][l]=counter;
                    counter++;
                }
            }
        }
    }
    
    cout<<"|----------------------------------------------------------------------|\n";
    for(int i=0;i<FOURD;i++)
    {
        for(int j=0;j<CHANNEL;j++)
        {
            int counter =0;
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL;l++)
                {
                    cout<<array[i][j][k][l]<<"  ";
                }
                cout<<endl;
            }
            cout<<endl<<endl;
        }
        cout<<"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+"<<endl;
    }
    cout<<"|----------------------------------------------------------------------|\n";
    
    __SE_TEMPLATE_v1 setemplate = __gen_SE_TEMPLATE_v1();
    setemplate.DIMFMT = __SE_DIMFMT_4D;
    setemplate.ELETYPE = __SE_ELETYPE_32BIT;
    setemplate.VECLEN = __SE_VECLEN_16ELEMS;
    setemplate.ICNT0 = COL;
    setemplate.ICNT1 = ROW;
    setemplate.ICNT2 = CHANNEL;
    setemplate.ICNT3 = FOURD;
    setemplate.DIM1 = COL;
    setemplate.DIM2 = COL * ROW;
    setemplate.DIM3 = CHANNEL* COL * ROW ;
    
    __SE0_OPEN(array,setemplate);

    for(int i=0;i<FOURD ; i++)
    {
        for(int j=0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL;l+=16)
                {
                    int16 int_vec = __SE0ADV(int16);
                    int_vec.print();
                }
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }

}