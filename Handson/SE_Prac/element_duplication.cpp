/*
Good program to understand 
The __SE_FLAG data member ELETYPE , ELEDUP , VECLEN
The __STRM_PARAM_3D data member like ICNT , DIM 
*/
#include<iostream>
#include "c7x_host_emulation.h"

using namespace std ;

#define ARRAY_LENGTH (32)
#define VECTOR_LENGTH (16)

using namespace std;

int main()
{
    cout<<"This is a program to understand the moving of array to SE and element duplication to form a Vector \n";

    int16_t array_input[ARRAY_LENGTH];

    for(int i=0, value =10;i<ARRAY_LENGTH;i++,value+=10)
    {
        array_input[i] = value ; 
    }

    int16_t * array_ptr = array_input;

    cout<<"Array is : " ;
    for(int i=0;i<ARRAY_LENGTH ; i++ )
    {
        cout<< array_ptr[i] << "  " ; 
    }
    cout<<endl ;

    __SE_FLAGS seflag;
    seflag = __SE_FLAGS_default();

    seflag.ELETYPE = __SE_ELETYPE_16BIT;
    seflag.VECLEN = __SE_VECLEN_32ELEMS;
    seflag.ELEDUP = __SE_ELEDUP_32X;  

    __STRM_PARAM_3D separam ;
    separam.ICNT0 = ARRAY_LENGTH ;
    separam.ICNT1 = 1 ;
    separam.ICNT2 = 1 ;
    separam.DIM1 = 0 ;
    separam.DIM2 = 0 ;

    __STRM_TEMPLATE setemplate ;
    setemplate = __SE_SET_PARAM_3D(&separam , &seflag);

    __SE0_OPEN((void *)&array_input[0] , setemplate);

    for(int i=0;i<ARRAY_LENGTH;i++)
    {
        short32 sVector = __SE0ADV(short32);
        
        cout<<" Vector[" << i << "]  = " ;
        sVector.print();
    }

    __SE0_CLOSE();
}