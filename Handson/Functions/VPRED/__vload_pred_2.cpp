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

    int counttt = 0 ;

    int16_t * ptr = input_array[0][0][0];
    for(int i=0;i<ITERA;i++)
    {
        int countt=0;
        for(int j=0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL/32;l++)
                {
                    int16_t * ptrr = ptr+ countt;
                    // __vpred vvpred = __SA0_VPRED(short32); // for all values in the vector 
                    __vpred vvpred = __create_vpred(0x0FFF); // for only 3 values from a vector 
                    vvpred.print();
                    short32 svec = __vload_pred(vvpred, reinterpret_cast<short32 *>(ptrr));
                    svec.print();
                    countt=countt+32;

                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }



}