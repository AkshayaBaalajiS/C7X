#include <iostream>
#include "c7x.h"

using namespace std;

#define ROW 5
#define COL 20
#define CHANNEL 3

int main()
{
    cout<<"This is the program to understand the SE TEMPLATE to take from the array and do pred operation \n";

    int32_t array[CHANNEL][ROW][COL];

    int32_t output_array [CHANNEL * ROW * 16];

    for(int i=0;i<CHANNEL;i++)
    {
        int counter =0 ;
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k++)
            {
                counter++;
                array[i][j][k]=counter;
            }
        }
    }    

    cout<<"|-----------------------------------------------------------------|\n";
    
    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            for(int k=0;k<COL;k++)
            {
                cout<<array[i][j][k]<< "   " ;
            }
            cout<<endl;
        }
        cout<<endl<<"|-----------------------------------------------------------------|\n";
    }    
    
    __SE_TEMPLATE_v1 setemplate = __gen_SE_TEMPLATE_v1();
    setemplate.DIMFMT = __SE_DIMFMT_3D;
    setemplate.VECLEN = __SE_VECLEN_16ELEMS;
    setemplate.ELETYPE = __SE_ELETYPE_32BIT;
    setemplate.ICNT0 = COL;
    setemplate.ICNT1 = ROW ;
    setemplate.ICNT2 = CHANNEL ;
    setemplate.DIM1 = COL ;
    setemplate.DIM2 = ROW * COL;

    // proof that without openning the SE the SE0ADV will give garbage value 
    __SE0_OPEN(array,setemplate);
    int counter =0;

    for(int i=0;i<CHANNEL;i++)
    {
        for(int j=0;j<ROW;j++)
        {
            int16 int_vec;
            int16 int_vec_1;
            int16 output_vec;
            for(int k=0;k<COL;k+=16*2)
            {
                int_vec = __SE0ADV(int16);
                int_vec_1 = __SE0ADV(int16);

                vpred vpred_vec = __cmp_gt_pred(int_vec, int_vec_1);


                int_vec.print();
                int_vec_1.print();
                vpred_vec.print();

                output_vec = __select(vpred_vec, int_vec, int_vec_1);
                output_vec.print();
            }
            cout<<endl;
            *stov_ptr(int16 , (int32_t *)(output_array + (counter*16))) = output_vec;
            counter++;
        }
        cout<<endl<<endl;

    }

    cout<<"|-----------------------------------------------------------------|\n";

    for(int l=0;l<CHANNEL*ROW*16;l++)
    {
        cout<<output_array[l] << "   "; 
    }
    cout<<endl;
}
