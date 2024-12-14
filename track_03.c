#include <stdio.h>
#include "mtrack_03.h"

int main(void) 
{
    char *a=_my_malloc(1);
    char *b=_my_malloc(1);
    _my_free(a);
    b++;
    _my_free(b);
    return 0;
}
