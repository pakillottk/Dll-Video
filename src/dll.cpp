#include "dll.h"
#include <stdio.h>

void dllFunc(int value)
{
    printf("The value is: %d\n", value);
    printf("The double of value is: %d\n", value*2);
}