#include<iostream>
#include "c7x.h"

using namespace std;

#define COL 32
#define ROW 5
#define CHANNEL 3
#define FD 2 

int main()
{
    cout<<"This is the program to understand the SE TEMPLATE 4D \n";
    
    int16_t input_array [FD][CHANNEL][ROW][COL];

    for(int i=0;i<FD;i++)
    {
        int counter = 0 ;
        for(int j=0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL;l++)
                {
                    input_array[i][j][k][l] = counter ;
                    counter++;
                }
            }
        }
    }

    cout<<"|------------------------------------------------------------|\n";

    for(int i=0;i<FD;i++)
    {
        int counter = 0 ;
        for(int j=0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL;l++)
                {
                    cout<<input_array[i][j][k][l] << "  " ;
                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }

    cout<<"|------------------------------------------------------------|\n";

    __SE_TEMPLATE_v1 setemplate0 = __gen_SE_TEMPLATE_v1();
    setemplate0.DIMFMT = __SE_DIMFMT_4D;
    setemplate0.ELETYPE = __SE_ELETYPE_16BIT;
    setemplate0.VECLEN = __SE_VECLEN_32ELEMS;
    setemplate0.ICNT0 = COL;
    setemplate0.ICNT1 = ROW;
    setemplate0.ICNT2 = CHANNEL;
    setemplate0.ICNT3 = FD;
    setemplate0.DIM1 = COL;
    setemplate0.DIM2 = COL * ROW;
    setemplate0.DIM3 = COL * ROW * CHANNEL;
    setemplate0.DIM4 = FD * COL * ROW * CHANNEL;

    __SE0_OPEN(input_array, setemplate0 );

    for(int i=0;i<FD;i++)
    {
        for(int j=0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL/32;l++)
                {
                    short32 int_vector = __SE0ADV(short32);
                    int_vector.print();
                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    

}