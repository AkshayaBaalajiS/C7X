#include "c7x.h"
#include <iostream>
#include <stdint.h>

using namespace std;

#define ARRAY_SIZE (50)
#define COL_NUMBERS (32) //32 -16b elements in a 512b vector

// void add_function(int32_t * ptr1 ,int32_t * ptr2 ,intn * vector_ptr )
// {
//     cout<<"void add_function(int32_t * ptr1 ,int32_t * ptr2 ,intn * vector_ptr )  ..\n";

// } 

int main()
{
    int32_t array_1[ARRAY_SIZE];
    int32_t array_2[ARRAY_SIZE];
    


    for (int i=0;i<ARRAY_SIZE;i++)
    {
        array_1[i]=i;
        array_2[i]=i;
    }

    cout<<"This is the output for the array ..\n";

    for(int i=0;i<ARRAY_SIZE;i++)
    {
        cout<<"ARRAY_1["<<i<< "]" << "= " << array_1[i] << "  " ;
    }
    cout<<"\n\n";
    
    for(int i=0;i<ARRAY_SIZE;i++)
    {
        cout<<"ARRAY_2["<<i<< "]" << "= " << array_2[i] << "  " ;
    }



    int32_t output_array_1[ARRAY_SIZE] ;

    for(int i=0,j=0;i<ARRAY_SIZE;i++)
    {
        output_array_1[i]=j;
    }

    cout<<"\n\n";
    
    for(int i=0;i<ARRAY_SIZE;i++)
    {
        cout<<"OUTPUT_ARRAY["<<i<< "]" << "= " << output_array_1[i] << "  " ;
    }

    cout<<"\n\n";

    cout<<"The addition result is : " << "\n";
    cout<<"The output array is  :  " << "\n";

    // this takes nearly 50 iteration 
    // for(int i=0;i<ARRAY_SIZE;i++)
    // {
    //     output_array_1[i] = array_1[i] + array_2[i];
    // }

    // for(int i=0;i<ARRAY_SIZE;i++)
    // {
    //     cout<<"OUTPUT_ARRAY["<<i<< "]" << "= " << output_array_1[i] << "  " ;
    // }

    
    int32_t * ptr_1 = array_1;
    int32_t * ptr_2 = array_2;

    int32_t * output_ptr = output_array_1;

    
    for(int i=0;i<ARRAY_SIZE;i+=COL_NUMBERS)
    {
        // int32 vInt_1 = *stov_ptr(int32,(int32_t *)(ptr_1+i));
        
        // int32 vInt_2 = *stov_ptr(int32,(int32_t *)(ptr_2+i));
        
        // int32 vInt_3 = vInt_1 + vInt_2 ;

        // *stov_ptr(int32,(int32_t *)(ptr_2+i)) = vInt_3;

        short32 vInt_1 = *stov_ptr(short32,(int32_t *)(ptr_1+i));
        
        short32 vInt_2 = *stov_ptr(short32,(int32_t *)(ptr_2+i));
        
        short32 vInt_3 = vInt_1 + vInt_2 ;

        *stov_ptr(short32,(int32_t *)(output_ptr+i)) = vInt_3;

    }

    cout<<"The addition result is : " << "\n";
    cout<<"The output array is  :  " << "\n";


    for(int i=0;i<ARRAY_SIZE;i++)
    {
        cout<<"OUTPUT_ARRAY["<<i<< "]" << "= " << output_array_1[i] << "  " ;
    }




    
    
}
