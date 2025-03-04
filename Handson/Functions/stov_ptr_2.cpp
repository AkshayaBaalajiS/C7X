#include <iostream>
#include "c7x.h"

using namespace std;

#define ARRAY_SIZE (512)

int main()
{
    cout<<"This is the program to understand the addition of 2 array using the stov_ptr";

    int32_t arr_1[ARRAY_SIZE];
    int32_t arr_2[ARRAY_SIZE];

    for(int i=0;i<ARRAY_SIZE;i++)
    {
        arr_1[i]=i+1;
        arr_2[i]=i+2;
    }

    int32_t * ptr_1 = arr_1 ;
    int32_t * ptr_2 = arr_2 ;
    


    int32_t output_arr[ARRAY_SIZE];

    for(int i=0;i<ARRAY_SIZE;i+=16)
    {
        int16 vec_3 =int16(0);

        int16 vec_1 = *stov_ptr(int16, (int32_t *)ptr_1 + i);
        int16 vec_2 = *stov_ptr(int16, (int32_t *)ptr_1 + i);

        vec_3 = vec_1 + vec_2 ;

        *stov_ptr(int16, (int32_t *)(output_arr+i)) = vec_3;
    }

    for(int i=0;i<ARRAY_SIZE;i++)
    {
        cout<<output_arr[i] << "  " ;
    }
    cout<<endl;
}