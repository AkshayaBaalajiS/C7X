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

    __SE_TEMPLATE_v1 setemplate =  __gen_SE_TEMPLATE_v1();
    setemplate.DIMFMT = __SE_DIMFMT_4D;
    setemplate.VECLEN = __SE_VECLEN_16ELEMS;
    setemplate.ELETYPE = __SE_ELETYPE_16BIT;
    setemplate.PROMOTE = __SE_PROMOTE_2X_ZEROEXT; 
    // setemplate.ELETYPE = // there wont be eletype in sE 
    setemplate.ICNT0 = COL;
    setemplate.ICNT1 = ROW;
    setemplate.ICNT2 = CHANNEL;
    setemplate.ICNT3 = ITERA;
    setemplate.DIM1 = COL;
    setemplate.DIM2 = COL*ROW;
    setemplate.DIM3  = COL * ROW * CHANNEL;

    __SE0_OPEN(input_array,setemplate);

    int counttt = 0 ;

    int16_t * ptr = input_array[0][0][0];
    for(int i=0;i<ITERA*2;i++)
    {
        for(int j=0;j<CHANNEL;j++)
        {
            for(int k=0;k<ROW;k++)
            {
                for(int l=0;l<COL/32;l++)
                {
                    int16 input_vec = __SE0ADV(int16);
                    input_vec.print();

                }
                cout<<endl;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }



}