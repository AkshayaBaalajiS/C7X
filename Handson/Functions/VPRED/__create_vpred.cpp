#include <iostream>
#include "c7x.h"

using namespace std;

#define ROW 5
#define COL 16


int main()
{
    cout<<"This is the code to see how the vpred works and __create_vpred works \n";

    int32_t array[ROW][COL];

    int counter=0;
    for(int j=0;j<ROW;j++)
    {
        for(int k=0;k<COL;k++)
        {  
            counter++;
            array[j][k]=counter;
        }
    }
    cout<<"|----------------------------------------------------------------|\n";

    for(int j=0;j<ROW;j++)
    {
        for(int k=0;k<COL;k++)
        {  
            cout<<array[j][k] << "  " ;
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    
    int32_t * ptr = array[0] ;
    cout<<"|----------------------------------------------------------------|\n";

    int l =0 ;
    for(int j=0;j<ROW;j++)
    {
        for(int k=0;k<COL;k+=16)
        {
            int32_t * pptr = ptr + l;
            l=l+16;
            // vpred vvec = __create_vpred(0x0FFF);  //  0x0FFF denotes the first 3 values from the array  
            vpred vvec = __create_vpred(0x00FF);  //  0x00FF denotes the first 2 values from the array  
            // vpred vvec = __create_vpred(0x000F);  //  0x000F denotes the first 1 values from the array  
            vvec.print();

            int16 int_vec = __vload_pred(vvec, reinterpret_cast<const int16*>(pptr));  // the prob occurs when the cast is not proper  
            int_vec.print();
        }
        cout<<endl;
    }

}