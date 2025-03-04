#include<iostream>
#include "c7x_host_emulation.h"
using namespace std;

#define ROW (8)
#define COLUMN (28)
#define STRIDE (COLUMN)

#define VEC_LEN (16)

int main()
{
    cout<<"This is the program for the Vector Predication using SA \n ";
    
    int16_t array_input [ROW * COLUMN];
    int16_t copy_buffer [ROW * COLUMN];

    int16_t * ptr = array_input;

    int value =0;
    for(int i=0;i<ROW;i++)
    {
        for(int j=0;j<COLUMN;j++)
        {
            ptr[(COLUMN * i)  + j] = value;
            ++value;
        }
    }

    cout<<"The Array is : \n";
    for(int i=0;i<ROW * COLUMN ; i++)
    {
        cout<<array_input[i] << "   " ;  
    } 
    cout<<endl<<endl;

    // __SE_FLAGS seflags ;
    // seflags = __SE_FLAGS_default();
    // seflags.ELETYPE = __SE_ELETYPE_16BIT;
    // seflags.VECLEN = __SE_VECLEN_16ELEMS;
    // seflags.

    // __STRM_PARAM_3D saparam ;
    // saparam.ICNT0 = COLUMN ;
    // saparam.ICNT1 = ROW ;
    // saparam.ICNT2 = 1 ;
    // saparam.DIM1 = STRIDE ;
    // saparam.DIM2 = 0;

    // __STRM_TEMPLATE satemplate ;
    // satemplate = __SE_SET_PARAM_3D(&saparam , &seflags);

    // __SE0_OPEN((void *)array_input , satemplate);

    // for(int i=0;i<=(ROW * COLUMN)/16 +1;++i)
    // {
    //     short16 sVector = __SE0ADV(short16);

    //     cout<<"Vector [" << i << "]  = " << endl;
    //     sVector.print(); 
    // }

    // __SE0_CLOSE();


    __SE_FLAGS seflags ;
    seflags = __SE_FLAGS_default();
    seflags.ELETYPE = __SE_ELETYPE_16BIT;
    seflags.VECLEN = __SE_VECLEN_16ELEMS;

    __STRM_PARAM_3D separam ;
    separam.ICNT0 = COLUMN ;
    separam.ICNT1 = ROW ;
    separam.ICNT2 = 1 ;
    separam.DIM1 = STRIDE ;
    separam.DIM2 = 0;

    __STRM_TEMPLATE setemplate ;
    setemplate = __SE_SET_PARAM_3D(&separam , &seflags);

    __SA_FLAGS saflags;
    saflags = __SA_FLAGS_default();
    saflags.VECLEN = __SA_VECLEN_16ELEMS;

    __STRM_PARAM_3D saparam ;
    saparam.ICNT0 = COLUMN ;
    saparam.ICNT1 = ROW ;
    saparam.ICNT2 = 1 ;
    saparam.DIM1 = COLUMN ;
    saparam.DIM2 = 0 ;

    __STRM_TEMPLATE satemplate ;
    satemplate = __SA_SET_PARAM_3D(&saparam , & saflags);

    __SA0_OPEN(satemplate);
    __SE0_OPEN((void * )array_input,setemplate);

    for(int i=0;i<=(ROW * COLUMN )/16 +1;i++)
    {
        short16 sVector = __SE0ADV(short16);

        int arr[] = {1,2,3,4,5,6,7,8};
        vpred vpVector_1 = __create_vpred(0x000F);
        vpVector_1.print();

        int16 sample = __vload_pred(vpVector_1,reinterpret_cast<int16 *>(arr));
        cout<<"Sample : " ;
        sample.print();

        vpred vpVector = __SA0_VPRED(short16);


        vpred vpVector_2 = __create_vpred(0x0FFF);
        vpVector_2.print();

        cout<<"vpVector [" << i << "]  = " ;
        // cout<<hex;
        vpVector.print();
        // cout<<int;

        __vstore_pred(vpVector,__SA0ADV(short16,(void *)copy_buffer),sVector);
        // __vstore_pred(vpVector, __SA0ADV(short16, &copy_buffer[0]), sVector);


        // without the predicate at last half 
        cout<<"Vector [" << i << "]  = " << endl;
        sVector.print(); 

        cout<<endl;
    } 

    __SA0_CLOSE();
    __SE0_CLOSE();

    cout<<"OUTPUT ARRAY IS   : " <<endl ;
    for(int i=0;i<(ROW * COLUMN );i++)
    {
        cout<<copy_buffer[i] << "   ";
    }
    cout<<endl<<endl;
    
}