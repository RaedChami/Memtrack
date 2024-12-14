#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    int i, * ptr, sum = 0;
    ptr = calloc(10, 20);
    free(ptr);
    return 0;
}
