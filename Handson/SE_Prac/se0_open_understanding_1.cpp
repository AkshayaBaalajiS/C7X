// #include "c7x.h"
#include "c7x_host_emulation.h"

#include <iostream>

#define IMAGE_HEIGHT (8)
#define IMAGE_WIDTH (32)
#define NO_OF_CHANNEL (3)



using namespace std;

int main()
{
    cout<<"This is a simple program to understand the Streaming Engine and how it works ..\n";

    int16_t image_buffer[NO_OF_CHANNEL * IMAGE_HEIGHT * IMAGE_WIDTH];

    for(int k=0;k<NO_OF_CHANNEL;k++)
    {
        int16_t * pIn = (int16_t *)&image_buffer[(k * (IMAGE_HEIGHT * IMAGE_WIDTH))];
        int val=0;
        for(int i=0;i<IMAGE_HEIGHT;i++)
        {
            for(int j=0;j<IMAGE_WIDTH ; j++ )
            {
                pIn[(i*IMAGE_WIDTH) + j] =val++ ; 
            }
        }
    }

    for(int k=0;k<NO_OF_CHANNEL;k++)
    {
        int16_t * pout = (int16_t *)&image_buffer[(k * (IMAGE_HEIGHT * IMAGE_WIDTH))];
        for(int i=0;i<IMAGE_HEIGHT;i++)
        {
            for(int j=0;j<IMAGE_WIDTH;j++)
            {
                cout<< pout[(i*IMAGE_WIDTH)+j] << " " ;
            }
            cout<<"\n";
        }
    }

    // STREAMING ENGINE STARTS NOW 
    __SE_FLAGS seflag ;
    seflag = __SE_FLAGS_default();

    seflag.ELETYPE = __SE_ELETYPE_16BIT;
    seflag.VECLEN = __SE_VECLEN_32ELEMS;

    __STRM_PARAM_3D separam;
    separam.ICNT0 = IMAGE_WIDTH;
    separam.ICNT1 = IMAGE_HEIGHT;
    separam.ICNT2 = NO_OF_CHANNEL;
    separam.DIM1 = IMAGE_WIDTH ;
    separam.DIM2 = IMAGE_HEIGHT * IMAGE_WIDTH;
    
    __STRM_TEMPLATE setemplate ;

    setemplate = __SE_SET_PARAM_3D(&separam,&seflag);

    __SE0_OPEN((void *)&image_buffer[0] , setemplate);

    for(int i=0;i<(IMAGE_HEIGHT * NO_OF_CHANNEL * (IMAGE_WIDTH/32)); i++)
    {
        short32 vector = __SE0ADV(short32);
        
        cout<<" Vector[" << i << "]  = " ;
        vector.print(); 
    }
    
    __SE0_CLOSE();
} 