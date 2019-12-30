#include "dll.h"
#include <Windows.h>


int main(int argc, char **argv)
{
    // always same seed to ensure same sequence
    srand(1);

    while(true)
    {
        // each second we call to the dll
        dllFunc( rand()%10 );
        Sleep(1000);
    }
}