#ifndef MTRACK_04_H
#define MTRACK_04_H
#include <stdio.h>

#define malloc(taille) my_malloc(taille)
#define free(adresse) my_free(adresse)

void* my_malloc(size_t taille);
void my_free(void* adresse);

#endif