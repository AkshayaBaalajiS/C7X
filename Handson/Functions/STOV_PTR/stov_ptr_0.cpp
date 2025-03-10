#include <iostream>
#include "c7x.h"

using namespace std;

int main()
{
    cout<<"This is the program to understand the stov_ptr function of C7x\n";
    int size ;
    cout<<"Enter the size of the array : ";
    cin>>size;
    int16_t arr[size];
    for(int i=0;i<size;i++)
    {
        arr[i]= i * 2 ;
    }
    cout<<"Array is  :  ";
    for(int i=0;i<size;i++)
    {
        cout<<arr[i] << "  " ;
    }

    cout<<endl;

    cout<<"\nTHe vector is : ";
    short32 svector = short32(0);
    svector.print();

    svector = *stov_ptr(short32 , (int16_t *)arr );

    cout<<"The vector after stov is :  " ;
    svector.print();

    int16_t result_array[size];
    *stov_ptr(short32, (int16_t *)result_array)=svector;
    
    cout<<"\nThe output from vector to array is : ";
    for(int i=0;i<size;i++)
    {
        cout<<result_array[i] << "   " ;
    }
    cout<<endl;
}