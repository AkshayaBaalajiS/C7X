#include <iostream>
#include "c7x.h"
using namespace std;

#define ARRAY_SIZE (32)
// #define ARRAY_SIZE (128)
#define VEC_SIZE (32)

int main()
{
    cout<<"This is the program to understand how the int16_t array is converted to vector ..\n";

    int16_t input_array[ARRAY_SIZE] ;

    for(int i=0;i<ARRAY_SIZE ; i++ )
    {
        input_array[i] = i ;
    }

    cout<<"The input array is : " << endl;
    for(int i=0;i<ARRAY_SIZE ; i++ )
    {
        cout<<input_array[i] << "  "  ;
    }
    cout<<endl;
    
    // this will only hold 32 ele 
    // short32 result_vector ;

    // for making it hold 128 element 
    short32 result_vector;

    cout<<"\nThe integer array to vector cast is going on ..\n";
    // for(int i=0;i<ARRAY_SIZE;i+=VEC_SIZE)
    // {
    //     result_vector = *stov_ptr(short32 , (int16_t *) (input_array));
    //     result_vector.print();
    // }

    result_vector = *stov_ptr(short32 , (int16_t *) (input_array));


    // from the vector to array again 
    int16_t * output_array = new int16_t[ARRAY_SIZE];

    *stov_ptr(short32 , (int16_t *) (output_array))=result_vector; 

    cout<<"\nThe final vector is : " <<endl; 
    result_vector.print();

    cout<<"\nThe final array is : " << endl;
    for(int i=0;i<ARRAY_SIZE ; i++ )
    {
        cout<<output_array[i] << "  "  ;
    }
    cout<<endl;

    
}


// the understanding is : 
/*
short is of 2 byte and int16_t is same of 
*/ 

