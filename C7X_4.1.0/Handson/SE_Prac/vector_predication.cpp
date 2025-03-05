#include<iostream>
#include "c7x_host_emulation.h"
using namespace std;

#define ROW (8)
#define COLUMN (28)

#define STRIDE (COLUMN)
#define VECTOR (16)

int main()
{
    cout<<"This is the code to understand the vector predication \n";

    int32_t array_size[ROW * COLUMN];

    int32_t * array_ptr = array_size;

    int value =0 ;
    for(int i=0;i<ROW;i++)
    {

        for(int j=0;j<COLUMN;j++)
        {
            array_ptr[(i * COLUMN) + j]=value++; 
        }
    }

    // cout<<"Array is  : ";
    // for(int i=0;i<(ROW*COLUMN);i++)
    // {
    //     cout<< array_size[i]<< "  ";
    // }
    // cout<<endl;

    cout<<"Array is  : \n";
    for(int i=0;i<(ROW);i++)
    {
        for(int j=0;j<COLUMN;j++)
        {
            cout<< array_ptr[(i * COLUMN) + j]<< "  ";
        }
        cout<<"\n";
    }
    cout<<endl;

    __SE_FLAGS seflags ;
    seflags = __SE_FLAGS_default() ;
    
    // for non predicate 
    // seflags.ELETYPE = __SE_ELETYPE_32BIT ;
    // seflags.VECLEN = __SE_VECLEN_16ELEMS ;
    
    // for predicate 
    seflags.ELETYPE = __SE_ELETYPE_32BIT ;
    seflags.VECLEN = __SE_VECLEN_16ELEMS ;
    seflags.DECDIM1 = __SE_DECDIM_DIM2 ; // decrement DECDIM1_WIDTH everytime ICNT2 updated 
    

    __STRM_PARAM_3D separam;
    // for non predicate 
    // separam.ICNT0 = COLUMN;
    // separam.ICNT1 = ROW ;
    // separam.ICNT2 = 1 ;
    // separam.DIM1 = STRIDE ;
    // separam.DIM2 = 0 ;

    // for predicate 
    separam.ICNT0 = 16;
    separam.ICNT1 = ROW ;
    separam.ICNT2 = 2 ;
    separam.DIM1 = STRIDE ;
    separam.DIM2 = 16 ;
    separam.DECDIM1_WIDTH = COLUMN;

    __STRM_TEMPLATE setemplate;
    setemplate=__SE_SET_PARAM_3D(&separam,&seflags);

    __SE0_OPEN((void *)&array_size[0] , setemplate);

    for(int i=0;i<(ROW *ceil(COLUMN / 16.0));i++)
    {
        int16 sVector = __SE0ADV(int16);

        cout<<"Vector ["<< i <<"]  = " ;
        sVector.print();
    }
    __SE0_CLOSE();

}

/*
predicated / zero out

ICNT -> 18 
VECLEN -> 16

18 - 16   ----  2 
2 - 16 ----- 2 valied remaining 14 invalid (predicated) 
*/