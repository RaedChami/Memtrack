#include <stdio.h> 
#include <stdlib.h> 

int main(void) 
{ 
    int *ptr = (int *)malloc(10 * sizeof(int));
    int *new_ptr = (int *)realloc(ptr, 20 * sizeof(int));
    free(ptr);
    return 0; 
} 