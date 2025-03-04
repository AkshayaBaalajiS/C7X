#include<iostream>
#include "c7x_host_emulation.h"
// #include "c7x.h"

#define ROW (8)
#define COLUMN (32)
#define STRIDE (COLUMN)
#define CHANNEL (3)

using namespace std;

int main()
{
    cout<<"This is the second level of program to understand the multi dimension load using SA \n";
    int32_t array_input[(ROW*COLUMN*CHANNEL)];        

    int32_t image_buffer [CHANNEL][ROW][COLUMN] ;
    // for(int k=0;k<CHANNEL;k++)
    // {
    //     int value = 10 ;
    //     int16_t * ptr = (int16_t *)&array_input[(k *(COLUMN * ROW))];
    //     for(int i=0;i<ROW;i++)
    //     {
    //         for(int j=0;j<COLUMN;j++,value+=10)
    //         {
    //             ptr[j +(i * COLUMN )] = value ;  
    //         }
    //     }
    // }

    // for(int k=0;k<CHANNEL;k++)
    // {
    //     int16_t * ptr = (int16_t *)&array_input[(k *(COLUMN * ROW))];
    //     for(int i=0;i<ROW;i++)
    //     {
    //         for(int j=0;j<COLUMN;j++)
    //         {
    //             cout<< ptr[j+(i * COLUMN)] << "   ";
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;

    for(int i=0,value=10;i<(CHANNEL * ROW * COLUMN) ; i++ , value++)
    {
        array_input[i]=value;
    }

    for(int i=0,value=10;i<(CHANNEL * ROW * COLUMN) ; i++ , value++)
    {
        cout<<array_input[i] << "  ";
    }
    cout<<endl;

    __SA_FLAGS saflags;
    saflags = __SA_FLAGS_default();
    saflags.VECLEN = __SA_VECLEN_16ELEMS;

    __STRM_PARAM_3D saparam;
    saparam.ICNT0 = COLUMN ;
    saparam.ICNT1 = ROW;
    saparam.ICNT2 = CHANNEL ;
    saparam.DIM1 = STRIDE ;
    saparam.DIM2 = STRIDE * ROW ;

    __STRM_TEMPLATE satemplate ;
    satemplate = __SA_SET_PARAM_3D(&saparam , &saflags);

    __SA0_OPEN(satemplate); 

    // for(int i=0;i<(CHANNEL * ROW * (COLUMN/16) ); i++)
    // {
    //     int16 iVector = __SA0ADV(int16,(void *)array_input);

    //     cout<<"Vector [" << i << "] " << endl ;
    //     iVector.print();
    // }
    // cout<<endl;

    for(int i=0;i<(CHANNEL * ROW * (COLUMN) ); i+=16)
    {
        int16 iVector = *stov_ptr(int16 , (int32_t *)&array_input[i]);
        // since the col already is 32 and here we get with 16 ele as col so we are adding with 16 in i 

        // __SA0ADV(int16, &image_buffer[0][0][0]) = &iVector ;
        // *((int16*)__SA0ADV(int16, &image_buffer[0][0][0])) = iVector;
        *(__SA0ADV(int16, &image_buffer[0][0][0])) = iVector;

        // int16 * ptr ;
        // ptr = &iVector ;
        // __SA0ADV(int16, (int32_t *)&image_buffer[0][0][0]) = iVector;


        cout<<"Vector ["<< i <<"]  = " ;
        iVector.print();
    }

    for(int i=0;i<CHANNEL ; i++)
    {
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COLUMN;k++)
            {
                cout<<image_buffer[i][j][k] << "   " ;
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
    }

    cout<<endl;
    __SA0_CLOSE();
    
}


