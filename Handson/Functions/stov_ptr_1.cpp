#include <iostream>
#include "c7x.h"

using namespace std;

#define ARRAY_SIZE (50)
#define COEFF_SIZE (5) 
#define OUTPUT_SIZE (ARRAY_SIZE - COEFF_SIZE + 1)
int main()
{
    cout<<"This is the program to undertsand the FIR calculation using the stov_ptr \n";
    int16_t arr_1[ARRAY_SIZE];
    int16_t arr_2[COEFF_SIZE];
    int16_t arr_3[OUTPUT_SIZE];

    for(int32_t i=0;i<ARRAY_SIZE;i++)
    {
        arr_1[i]=i;   
    }
    for(int32_t i=0;i<COEFF_SIZE;i++)
    {
        arr_2[i]=i;
    }
    for(int32_t i=0;i<OUTPUT_SIZE;i++)
    {
        arr_3[i]=0;
    }

    cout << " INPUT ARRAY NOW : \n";
    for(int32_t i=0;i<ARRAY_SIZE;i++)
    {
        cout<<arr_1[i] << " " ; 
    }
    cout<<"\nCOEFFICEINT ARRAY NOW : \n";
    for(int32_t i=0;i<COEFF_SIZE;i++)
    {
        cout<<arr_2[i] << " " ;
    }
    cout<<"\nOUTPUT ARRAY NOW : \n";
    for(int32_t i=0;i<OUTPUT_SIZE;i++)
    {
        cout<<arr_3[i] << " " ;
    }
    cout<<endl;

    int16_t * ptr_1 = arr_1;
    int16_t * ptr_2 = arr_2;
    int16_t * ptr_output_array = arr_3;


    for(int j=0;j<OUTPUT_SIZE;j+=32)
    {
        short32 result_vec = short32(0);
    
        for(int i=0;i<COEFF_SIZE;i++)
        {
            short32 input_vec = *stov_ptr(short32, (int16_t *)ptr_1+i+j);
            short32 coeff_vec = short32 (ptr_2[i]);

            result_vec += (input_vec * coeff_vec);
            // result_vec.print();

        }
        *stov_ptr(short32 , (int16_t *) (arr_3+j)) = result_vec;   
    }

    cout<<"\nOUTPUT ARRAY NOW : \n";
    for(int32_t i=0;i<OUTPUT_SIZE;i++)
    {
        cout<<arr_3[i] << " " ;
    }

}