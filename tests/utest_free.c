# include <stdio.h>
# include <stdlib.h>

int main(void)
{
    int* ptr1=malloc(1);
    int** ptr2=&ptr1;
    free(*ptr2);
    free(ptr1);
    *ptr2=NULL;
    free(ptr2);
    return 0;
}