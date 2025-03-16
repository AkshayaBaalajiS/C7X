#include <C7100/c7x.h>
#include <C7100/ti_he_impl/vector.h>
#include <iostream>
#include "c7x.h"

using namespace std;

#define ROW 5
#define COL 32 
#define CHANNEL 3 
#define ITERA 2

int main()
{
    cout<<"This is the program to understand the vstore pred and vload pred in C7X\n";

    int16_t input_array [ITERA][CHANNEL][ROW][COL];
    int16_t output_array [ITERA][CHANNEL][ROW][COL];

    for(int i=0;i<ITERA;i++)
    {
        int counter = 0;
        for(int j =0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL;l++)
                {
                    input_array[i][j][k][l] = counter ;
                    counter++;
                }
            }
        }
    }

    cout<<"|-----------------------------------------------------------------------------------|\n";
    
    for(int i=0;i<ITERA;i++)
    {
        int counter = 0;
        for(int j =0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL;l++)
                {
                    cout<<input_array[i][j][k][l] << "  " ;
                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }


    cout<<"|-----------------------------------------------------------------------------------|\n";

    __SA_TEMPLATE_v1 satemplate =  __gen_SA_TEMPLATE_v1();
    satemplate.DIMFMT = __SA_DIMFMT_4D;
    satemplate.VECLEN = __SA_VECLEN_32ELEMS;
    // satemplate.ELETYPE = // there wont be eletype in sa 
    satemplate.ICNT0 = COL;
    satemplate.ICNT1 = ROW;
    satemplate.ICNT2 = CHANNEL;
    satemplate.ICNT3 = ITERA;
    satemplate.DIM1 = COL;
    satemplate.DIM2 = COL*ROW;
    satemplate.DIM3  = COL * ROW * CHANNEL;

    __SA0_OPEN(satemplate);


    __SA_TEMPLATE_v1 satemplate_1 =  __gen_SA_TEMPLATE_v1();
    satemplate_1.DIMFMT = __SA_DIMFMT_4D;
    satemplate_1.VECLEN = __SA_VECLEN_32ELEMS;
    // satemplate_1.ELETYPE = // there wont be eletype in sa 
    satemplate_1.ICNT0 = COL;
    satemplate_1.ICNT1 = ROW;
    satemplate_1.ICNT2 = CHANNEL;
    satemplate_1.ICNT3 = ITERA;
    satemplate_1.DIM1 = COL;
    satemplate_1.DIM2 = COL*ROW;
    satemplate_1.DIM3  = COL * ROW * CHANNEL;

    __SA1_OPEN(satemplate_1);

    int16_t * ptr = input_array[0][0][0];
    for(int i=0;i<ITERA;i++)
    {
        int count=0;
        for(int j=0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL/32;l++)
                {
                    __vpred vvpred = __SA0_VPRED(short32);
                    int16_t * ptrr = ptr+count; 
                    // short32 input_vec  = *__SA0ADV(short32, (void * )ptrr);
                    short32 input_vec = __vload_pred(vvpred, reinterpret_cast<short32 *>(ptrr));
                    input_vec.print();
                    count=count+32;
                    __vpred vvpred_1 = __SA1_VPRED(short32);
                    // vvpred_1.print();
                    __vstore_pred(vvpred_1, __SA1ADV(short32,(void *)output_array),input_vec); 
                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }

    cout<<"|***************************************************************************************************************************************|\n";
    
    for(int i=0;i<ITERA;i++)
    {
        int counter = 0;
        for(int j =0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL;l++)
                {
                    cout<<output_array[i][j][k][l] << "  " ;
                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }


    cout<<"|***************************************************************************************************************************************|\n";



}