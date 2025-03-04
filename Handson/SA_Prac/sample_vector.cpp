
// #include "c7x_host_emulation.h"
#include "c7x.h"
using namespace std;

int main()
{
    
    char16 cvec= char16(-1);

    for(int8_t i=1;i<=16;i++)
    {
        cvec.s[i-1]=-i;
    }
    cvec.print();

    float16 fvec = float16(cvec);
    fvec.print();
    

    short8 svec = __high_char_to_short(cvec); 
    short8 svec_1 = __low_char_to_short(cvec); 

    cout<<"++++++++++++++++++++++++++++++\n";

    svec.print();
    svec_1.print();

    cout<<"++++++++++++++++++++++++++++++\n";

    short8 ssvec = svec ;
    svec.print();
    svec_1.print();

    // fvec.print();

    
}