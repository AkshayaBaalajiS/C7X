#include<iostream>
#include "c7x_host_emulation.h"

#define ARRAY_SIZE (256)

#define ROW (5)
#define COLUMN (64)
#define CHANNEL (2)

using namespace std;

int main()
{
    cout<<"This is the program to understand the array to Streaming Engine to Reduce CPU Load\n";
    int16_t array[CHANNEL * ROW * COLUMN];

    int value=1;
    for(int k=0;k<CHANNEL;k++)
    {
        int value=1;
        int16_t * ptr = (int16_t *)&array[(k * (ROW * COLUMN))]; 
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COLUMN;j++,value++)
            {
                ptr[(i * COLUMN ) + j ]=value;
            }
        }
    }
    cout<<"The array is : \n";
    for(int k=0;k<CHANNEL;k++)
    {
        int16_t * ptr = (int16_t *)&array[( k* (ROW * COLUMN))]; 
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COLUMN;j++)
            {
                cout<< ptr[(i * COLUMN ) + j ] << "  " ;
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
    // int16_t array[ROW][COLUMN];
    
    // for(int i=0;i<ROW;i++)
    // {
    //     int value=1;
    //     for(int j=0;j<COLUMN;j++,value++)
    //     {
    //         array[i][j]=value;
    //     }
    // }

    cout<<"The array is  : \n";
    for(int i=0;i<ROW* COLUMN * CHANNEL;i++)
    {
        cout<<array[i] << " ";
    }

    __SE_FLAGS seflag ;
    seflag = __SE_FLAGS_default();

    seflag.ELETYPE = __SE_ELETYPE_16BIT;
    seflag.VECLEN = __SE_VECLEN_16ELEMS;

    __STRM_PARAM_3D separam ;
    separam.ICNT0 = COLUMN;
    separam.ICNT1 = ROW ;
    separam.ICNT2 = CHANNEL ;
    separam.DIM1 = COLUMN ;
    separam.DIM2 = ROW * COLUMN ;

    __STRM_TEMPLATE setemplate ;
    setemplate = __SE_SET_PARAM_3D(&separam , &seflag);

    __SE0_OPEN((void *)&array[0] , setemplate);
    cout<<endl;

    for(int i=0 ; i<(ROW * CHANNEL * (COLUMN/16));i++)
    {
        short16 vector = __SE0ADV(short16);

        cout<<" Vector[" << i << "]  = " ;
        vector.print();
    }
    __SE0_CLOSE();

}