#include<iostream>
#include "c7x_host_emulation.h"

using namespace std;

#define ARRAY_SIZE (200)
#define VECTOR_SIZE (32)

int main()
{
    cout<<"This is the program to understand the element decimation\n ";
    
    int8_t array_input[ARRAY_SIZE];
    for(int i=0;i<ARRAY_SIZE;i++)   
    {
        array_input[i]=i;
    }

    int8_t * array_ptr = array_input;
    cout<<"Array is  : " ;
    for(int i=0;i<ARRAY_SIZE;i++)
    {
        cout<<(int)array_ptr[i] << "  " ;
    }
    cout<<endl;

    __SE_FLAGS seflags ;
    seflags = __SE_FLAGS_default();
    seflags.ELETYPE = __SE_ELETYPE_8BIT;
    seflags.VECLEN = __SE_VECLEN_16ELEMS;  // if this is 16 bits we will get only the 16 ele on the 32 ele vector first 16 will only have value 
    seflags.DECIM = __SE_DECIM_2 ;
    seflags.PROMOTE = __SE_PROMOTE_2X_SIGNEXT ;

    __STRM_PARAM_3D separam ;
    separam.ICNT0 = ARRAY_SIZE ;
    separam.ICNT1 = 1;
    separam.ICNT2 = 1 ;
    separam.DIM1 = 0 ;
    separam.DIM2 = 0 ;

    __STRM_TEMPLATE setemplate;
    setemplate = __SE_SET_PARAM_3D(&separam,&seflags );

    __SE0_OPEN((void *)&array_input[0] , setemplate);

    for(int i=0;i<=ARRAY_SIZE/VECTOR_SIZE ; i++)
    {
        short16 sVector = __SE0ADV(short16);

        cout<<" Vector[" << i << "]  = " ;
        sVector.print();
    } 
    __SE0_CLOSE();
    
}