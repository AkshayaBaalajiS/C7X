#include<iostream>
#include "c7x.h"
using namespace std;

#define ARRAY_SIZE (50)
#define COEFF_SIZE (5)
#define OUTPUT_SIZE (ARRAY_SIZE - COEFF_SIZE +1 )

#define VEC_ELE (32)

int main()
{
    cout<<"This is a program to calculate the FIR\n";

    int16_t ip_array[ARRAY_SIZE];
    int16_t coeff_array[COEFF_SIZE];

    int16_t output_array[OUTPUT_SIZE] ;

    // initialize input array, coefficient array, output array 
    for(int32_t i=0,j=0;i<ARRAY_SIZE;i++)
    {
        ip_array[i]=i;   
    }
    for(int32_t i=0,j=0;i<COEFF_SIZE;i++)
    {
        coeff_array[i]=i;
    }
    for(int32_t i=0,j=0;i<OUTPUT_SIZE;i++)
    {
        output_array[i]=j;
    }

    cout << " INPUT ARRAY NOW : \n";
    for(int32_t i=0,j=0;i<ARRAY_SIZE;i++)
    {
        cout<<ip_array[i] << " " ; 
    }
    cout<<"\nCOEFFICEINT ARRAY NOW : \n";
    for(int32_t i=0,j=0;i<COEFF_SIZE;i++)
    {
        cout<<coeff_array[i] << " " ;
    }
    cout<<"\nOUTPUT ARRAY NOW : \n";
    for(int32_t i=0,j=0;i<OUTPUT_SIZE;i++)
    {
        cout<<output_array[i] << " " ;
    }

    // int16_t * ptr_1 = ip_array;
    // int16_t * ptr_2 = coeff_array;
    // int16_t * ptr_output_array = output_array;


    int16_t * ptr_1 = ip_array;
    int16_t * ptr_2 = coeff_array;
    int16_t * ptr_output_array = output_array;

    cout<<"\nCALCULATING THE FINITE IMPULSE RESPONSE ..\n";

    for(int32_t i=0;i<OUTPUT_SIZE;i+=VEC_ELE)
    {
        // we are initializing the VECTOR 
        short32 vect = (short32)(0);
        for(int32_t j=0;j<COEFF_SIZE;j++)
        {
            short32 input = *stov_ptr(short32, (int16_t *)(ptr_1 +i+j));
            cout<<"The input is : " << "\n";
            input.print();

            short32 vcoeff = short32(ptr_2[j]);
            cout<<"The covariance is  : " << "\n";
            vcoeff.print();

            vect+=(input * vcoeff);
            cout<<"The output should be  : " << "\n";
            vect.print(); 

        }
        // for storing the result   
        *stov_ptr(short32, (int16_t *)(ptr_output_array+i))=vect;
    }

    cout<<"\nOUTPUT ARRAY NOW : \n";
    for(int i=0,j=0;i<OUTPUT_SIZE;i++)
    {
        cout<<output_array[i] << " " ;
    }
    cout<<endl;


}

/*
The input is : 
(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
The covariance is  : 
(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
The output should be  : 
(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
The input is : 
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32)
The covariance is  : 
(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1)
The output should be  : 
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32)
The input is : 
(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33)
The covariance is  : 
(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2)
The output should be  : 
(5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35, 38, 41, 44, 47, 50, 53, 56, 59, 62, 65, 68, 71, 74, 77, 80, 83, 86, 89, 92, 95, 98)


input * covaraience + output
*/