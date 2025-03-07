#include <iostream>
#include "c7x.h"

using namespace std;

#define ROW 10
#define COL 32


int32_t main()
{
    cout<<"This is the program to understand the SE for 2d array \n";

    int16_t array [ROW][COL];
    int16_t * ptr = new int16_t [ROW * COL]; 
    int32_t counter = 0;
    
    for(int32_t i=0;i<ROW;i++)
    {
        for(int32_t j=0;j<COL;j++)
        {
            array[i][j] = counter ;
            counter++;
        }
    }

    for(int i =0 ;i<ROW;i++)
    {
        for(int j=0;j<COL;j++)
        {
            ptr[i * COL+ j ] = array[i][j];
        }
    }
    cout<<"|--------------------------------------------------------------------------|\n";
    for(int32_t i=0;i<ROW;i++)
    {
        for(int32_t j=0;j<COL;j++)
        {
            cout<<array[i][j] << "  " ;
        }
        cout<<endl;
    }
    cout<<"|--------------------------------------------------------------------------|\n";
    cout<<"The ptr output ";
    for(int i=0;i<ROW * COL;i++)
    {
        cout<<ptr[i] << "  "  ;
    }

    cout<<"\n|--------------------------------------------------------------------------|\n";


    __SE_TEMPLATE_v1 setemplate = __gen_SE_TEMPLATE_v1();
    setemplate.DIMFMT           = __SE_DIMFMT_2D; // without this line the se will consider this as 1d array 
    setemplate.ELETYPE = __SE_ELETYPE_16BIT;
    setemplate.VECLEN  = __SE_VECLEN_16ELEMS;
    setemplate.ICNT0 = COL ; // length of the row (the number of columns in your 2D array).
    setemplate.ICNT1 = ROW; // number of rows in your 2D
    setemplate.ICNT2 = 1; // don’t have a third dimension
    setemplate.DIM1 = COL ; //    this would represent the number of elements in each row 
    setemplate.DIM2 = 0; //corresponds to the second dimension size.

    __SE0_OPEN(ptr, setemplate );

    for (int row = 0; row < ROW; row++) {
        for (int vec = 0; vec < COL / 16; vec++) {  
            short16 short_vec = __SE0ADV(short16);
            cout << "Vector at row " << row << ", chunk " << vec << ": ";
            short_vec.print();
        }
    }
    
    cout<<"endl\n";
}


