#include <iostream>
#include "c7x.h"
// #include "c7x_he_strm.h"

using namespace std;

#define ROW 5
#define COL 16
#define CHANNEL 3

int main()
{
    cout<<"This is the program to understadn the SE for 3d array \n";

    int32_t array [CHANNEL] [ROW] [COL] ;

    for(int i=0;i<CHANNEL;i++)
    {
        int temp = 0 ;
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k++)
            {   
                array[i][j][k]=temp;
                temp++;
            }
        }
    }
    cout<<"|-------------------------------------------------------------------|\n";
    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k++)
            {   
                cout<<array[i][j][k] << "   " ;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    cout<<"|-------------------------------------------------------------------|\n";

    __SE_TEMPLATE_v1 setemplate  = __gen_SE_TEMPLATE_v1();
    setemplate.DIMFMT = __SE_DIMFMT_3D;
    setemplate.ELETYPE = __SE_ELETYPE_32BIT;
    setemplate.VECLEN = __SE_VECLEN_16ELEMS;
    // setemplate.DECDIM1 = __SE_DECDIM_DIM0;
    setemplate.ICNT0 = COL;
    setemplate.ICNT1 = ROW;
    setemplate.ICNT2 = CHANNEL;
    setemplate.DIM1 = COL ;
    setemplate.DIM2 = COL*ROW;  //product of columns and rows. So it is the total number of elements per channel.
    
/*
setemplate.DIM2 = CHANNEL*ROW;
You can observe that:

The second channel’s data starts at 15, 16, and so on.
The vector data is now split into 15 total rows, where the data is being "rolled over" from the first channel to the second.
This behavior occurs because DIM2 is now flattened across channels: rather than keeping each channel's data in its own separate rows, the elements are essentially mixed across all channels, creating a continuous stream of values. Hence, the data for Channel 1 starts at 15, 16, 17, ..., 30, and for Channel 2 it starts at 30, 31, 32, ..., 45.
*/
    __SE0_OPEN(array, setemplate);

    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<(ROW*COL)/16;j++)
        {
            // for(int k=0;k<=COL/16;k++)
            // {
                int16 int_vec = __SE0ADV(int16);
                cout<<"Vector at " << i <<" Channel " << " : ";
                int_vec.print();
            // }
            // cout<<endl;
        }
        cout<<endl<<endl;
    }

}   