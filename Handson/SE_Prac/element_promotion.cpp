#include<iostream>
#include "c7x_host_emulation.h"

using namespace std;

#define ARRAY_SIZE (20)

int main()
{
    cout<<"This is the program to understand the Element promotion from 8bit to 16bit\n";
 
    int8_t array_input[ARRAY_SIZE];

    for(int8_t i=0;i<ARRAY_SIZE;i++)
    {
        array_input[i]=i*-1;
    }

    // int8_t * array_ptr = (int8_t *)&array_input[0];
    int8_t * array_ptr = array_input;

    cout<<"Array is : ";
    for(int i=0;i<ARRAY_SIZE;i++)
    {
        cout<<(int)array_ptr[i] << "   " ;
    }
    cout<<"\n";

    __SE_FLAGS seflags ;
    seflags.ELETYPE = __SE_ELETYPE_8BIT;
    seflags.VECLEN = __SE_VECLEN_16ELEMS;
    seflags.PROMOTE = __SE_PROMOTE_4X_SIGNEXT;

    __STRM_PARAM_3D separam ;
    separam.ICNT0 = ARRAY_SIZE ;
    separam.ICNT1 = 1 ;
    separam.ICNT2 = 1 ;
    separam.DIM1 = 0 ;
    separam.DIM2 = 0 ;

    __STRM_TEMPLATE setemplate ;
    setemplate = __SE_SET_PARAM_3D(&separam,&seflags);

    __SE0_OPEN((void *)&array_input[0] ,setemplate);

    for(int i=0;i<=ARRAY_SIZE/16;i++)
    {
        int16 sVector = __SE0ADV(int16);  // this is the proof that the 8 bit is converted to 32 bit 
        
        cout<<" Vector[" << i << "]  = " ;
        sVector.print();

    } 
    __SE0_CLOSE();

}