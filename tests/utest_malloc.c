#include <stdio.h>

int main() {
    char *ptr = malloc(100);
    free(NULL);
    return 0;
}