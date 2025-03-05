#include<iostream>
#include "c7x_host_emulation.h"

using namespace std;

#define ARRAY_SIZE (32)
#define GRP_DUP_ELE (2)

int main()
{
    cout<<"This is the program to understand the group duplication in SE \n";
    int16_t array_input [ARRAY_SIZE];

    for(int i=0,value=10;i<ARRAY_SIZE ; i++,value+=10 )
    {
        array_input[i] = value ;
    }

    int16_t * array_ptr = array_input ;

    cout<<"Array is : " ;
    for(int i=0;i<ARRAY_SIZE ; i++)
    {
        cout<< array_ptr[i] << "  ";
    }
    cout<<endl;

    __SE_FLAGS seflags;
    seflags.ELETYPE = __SE_ELETYPE_16BIT;
    seflags.GRPDUP = __SE_GRPDUP_ON;
    seflags.VECLEN = __SE_VECLEN_2ELEMS;


    __STRM_PARAM_3D separam;
    separam.ICNT0 = ARRAY_SIZE ;
    separam.ICNT1 = 1;
    separam.ICNT2 = 1 ;
    separam.DIM1 = 0;
    separam.DIM2 = 0 ;

    __STRM_TEMPLATE setemplate ;
    setemplate = __SE_SET_PARAM_3D(&separam,&seflags);

    __SE0_OPEN((void *)&array_input[0] , setemplate );

    for(int i=0;i<ARRAY_SIZE/GRP_DUP_ELE;i++)
    {
        short32 sVector = __SE0ADV(short32);
        
        cout<<" Vector[" << i << "]  = " ;
        sVector.print();

    }

    __SE0_CLOSE();




}