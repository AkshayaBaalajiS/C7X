#include<iostream>
#include "c7x_host_emulation.h"
using namespace std;
#define ROW (8)
#define COLUMN (32)
#define STRIDE (COLUMN)
#define CHANNEL (3)

int main()
{
    cout<<"This is the program to understand the Multi Dimension Load \n";

    int16_t array_input [(CHANNEL * ROW * COLUMN)];

    for(int i=0;i<CHANNEL;i++)
    {
        int16_t * ptr = (int16_t *)&array_input[(i*(ROW * COLUMN))];
        int value = 10;
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COLUMN;k++,value+=10)
            {
                ptr[k + ( j * COLUMN )]= value;
            }
        }
    }

    for(int i=0;i<CHANNEL;i++)
    {
        int16_t * ptr = (int16_t *)&array_input[(i*(ROW * COLUMN))];
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COLUMN;k++)
            {
                cout<<ptr[k+(j * COLUMN)] << "  " ;
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
    }

    cout<<endl;

    __SA_FLAGS saflags ;
    // saflags.ELETYPE = __SA_ELETYPE_ // there is no ele type in sa 
    saflags = __SA_FLAGS_default();
    saflags.VECLEN = __SA_VECLEN_32ELEMS;

    __STRM_PARAM_3D saparam;
    saparam.ICNT0 = COLUMN;
    saparam.ICNT1 = ROW; 
    saparam.ICNT2 = CHANNEL; // nmo of channel 
    saparam.DIM1 = STRIDE ; 
    saparam.DIM2 = STRIDE * ROW; // each channel at dis of COL * ROW 

    __STRM_TEMPLATE satemplate ;
    satemplate = __SA_SET_PARAM_3D(&saparam,&saflags);

    __SA0_OPEN(satemplate);

    for(int i=0;i<(CHANNEL * ROW * (COLUMN / 32));i++)
    {
       short32 sVector = __SA0ADV(short32,(void *)array_input);

        cout<<"Vector [" << i << "] " << endl ;
        sVector.print();
    }
    
    __SA0_CLOSE();



}