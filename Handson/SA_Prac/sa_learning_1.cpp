#include <iostream>
#include "c7x_host_emulation.h"
//#include "c7x.h"
using namespace std;

#define COLUMN (128)
#define ROW (16)

#define STRIDE (COLUMN)

int main()
{
    cout<<"This is the program to understand the SA (How to create a flag , param and Template and how to Open) \n";

    uint8_t array_input[ROW][COLUMN ];

    for(uint8_t i=0;i<(ROW);i++)
    {
        int value=1;
        for(int j=0;j<COLUMN;j++,value++)
        {
            array_input[i][j]=value;
        }
    }

    uint8_t * array_ptr = (uint8_t *)array_input ;

    cout<<endl;
    for(uint8_t i=0;i<(ROW);i++)
    {
        for(int j=0;j<COLUMN;j++)
        {
            cout<<(int)array_ptr[j + (COLUMN *i )] << "   " ; 
        }
        cout<<endl;
    }

    __SA_FLAGS saflags ;
    saflags=__SA_FLAGS_default();
    // saflags.ELETYPE=__SA_ELETYPE_16BIT;
    saflags.VECLEN=__SA_VECLEN_64ELEMS;
    

    __STRM_PARAM_3D saparam;
    saparam.ICNT0 = COLUMN;
    saparam.ICNT1=ROW;
    saparam.ICNT2 = 1;
    saparam.DIM1=STRIDE;
    saparam.DIM2=0 ;

    __STRM_TEMPLATE satemplate;
    satemplate = __SA_SET_PARAM_3D(&saparam , &saflags);

    __SA0_OPEN(satemplate);

    // for(int i=0;i<(ROW * COLUMN)/64.0)
    uchar64 clear_vec = uchar64(0);
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COLUMN;j+=64)
        {
            uchar64 ucVector = __SA0ADV(uchar64 , (void *)array_input);
            cout<<"Vector [" << i << "] [" <<j<<"]" << endl ;

            ucVector.print();
            ucVector=clear_vec;
	    ucVector.print();
 	}
    }

 
    __SA0_CLOSE();
    
}
