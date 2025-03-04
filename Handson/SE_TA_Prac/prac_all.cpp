#include<iostream>
#include "c7x_host_emulation.h"

#define WIDTH (16)
#define HEIGHT (4)
#define CHANNEL (3)
// typedef WIDTH WIDTH ;
// typedef HEIGHT HEIGHT ;
using namespace std ;

int main()
{
    cout<<"This is the program to understand the Multi dimension transpose \n";

    int16_t input_buffer [CHANNEL * HEIGHT * WIDTH ];
    int16_t copy_buffer [CHANNEL ][HEIGHT] [WIDTH ];
    
    for(int i=0;i<CHANNEL;i++)
    {   
        int value =0;
        int16_t * ptr = (int16_t *)&input_buffer[(WIDTH * HEIGHT) *i];
        for(int i=0;i<HEIGHT ; i++)
        {
            for(int j=0;j<WIDTH;j++)
            {
                ptr[j+(WIDTH * i)] = value;
                ++value; 
            }
        }
    }

    cout<<"The input Array is : \n";

    for(int i=0;i<CHANNEL;i++)
    {
        int16_t * ptr =  (int16_t *)&input_buffer[i*(HEIGHT * WIDTH)];
        for(int i=0;i<HEIGHT;i++)
        {
            for(int j=0;j<WIDTH;j++)
            {
                cout<<ptr[j+(i*WIDTH)] << "    " ;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }

    // for(int i=0;i<(WIDTH * HEIGHT * CHANNEL );i++)
    // {
    //     cout <<input_buffer[i] << "    " ;
    // } 

    __SE_FLAGS seflags ;
    seflags = __SE_FLAGS_default();
    seflags.ELETYPE = __SE_ELETYPE_16BIT;
    seflags.VECLEN = __SE_VECLEN_16ELEMS;

    __STRM_PARAM_3D separam;
    // 2D ARRAY 
    separam.ICNT0 = WIDTH ;
    separam.ICNT1 = HEIGHT ;
    separam.ICNT2 = 1 ;
    separam.DIM1 = WIDTH;
    separam.DIM2 = 0 ;

    // 1D Array 
    // separam.ICNT0 = WIDTH * HEIGHT * CHANNEL ;
    // separam.ICNT1 = 1 ;
    // separam.ICNT2 = 1 ;
    // separam.DIM1 = 0;
    // separam.DIM2 = 0 ;


    __STRM_TEMPLATE setemplate ;
    setemplate = __SE_SET_PARAM_3D(&separam , &seflags); 


    __SA_FLAGS saflags ;
    saflags = __SA_FLAGS_default();
    saflags.VECLEN = __SA_VECLEN_16ELEMS;

    __STRM_PARAM_3D saparam;
    // saparam.ICNT0 = WIDTH ;
    // saparam.ICNT1 = HEIGHT ;
    // saparam.ICNT2 = 1 ;
    // saparam.DIM1 = WIDTH;
    // saparam.DIM2 = 0 ;

    // multi dim load 
    saparam.ICNT0 = WIDTH ;
    saparam.ICNT1 = HEIGHT ;
    saparam.ICNT2 = CHANNEL ;
    saparam.DIM1 = WIDTH;
    saparam.DIM2 = WIDTH * HEIGHT ;

    __STRM_TEMPLATE satemplate ;
    satemplate = __SA_SET_PARAM_3D(&saparam, & saflags);

    __SA0_OPEN(satemplate);

    __SE0_OPEN((void *)input_buffer, setemplate);
    // for array to vector and printing 
    // for(int i=0;i<=( HEIGHT * (WIDTH/ 16)); i++) // ceil((WIDTH)/16));i++)
    // {
    //     short16 sVector = __SE0ADV(short16);

    //     sVector.print();    
    // }

    // for vector predication 
    // for(int i=0;i<=(HEIGHT * WIDTH)/ 16; i++) // ceil((WIDTH)/16));i++)
    // {
    //     short16 sVector = __SE0ADV(short16);
    //     vpred vpVector = __SA0_VPRED(short16);

    //     __vstore_pred(vpVector , __SA0ADV(short16,(void *)copy_buffer),sVector);
    // }

    // for array to vector to array 
    for(int i=0;i<(CHANNEL * HEIGHT * WIDTH );i+=16)
    {
        short16 sVector = *stov_ptr(short16,(int16_t *)&input_buffer[i]);
        *(__SA0ADV(short16,&copy_buffer[0][0][0])) = sVector ;
        sVector.print();


    }

     cout << "OUTPUT BUFFER : \n";
    // the wrong way of accessing the ouput buffer 3D 
    // for(int k=0;k<CHANNEL ; k++)
    // {
    //     int16_t * ptr = (int16_t * )&copy_buffer [k * (WIDTH * HEIGHT )];
    //     for(int i=0;i<HEIGHT ;i++)
    //     {
    //         for(int j=0;j<WIDTH;j++)
    //         {
    //             cout<< ptr[j+ (i*WIDTH)] << "    " ;
    //         }
    //         cout<<endl;
    //     }
    //     cout<<endl<<endl;
    // }   

     cout << "OUTPUT BUFFER : \n";
    for (int c = 0; c < CHANNEL; c++) {
        cout << "Channel " << c << ": \n";
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                cout << copy_buffer[c][i][j] << "    ";
            }
            cout << endl;
        }
        cout << endl;
    }
}