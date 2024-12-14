#ifndef MTRACK_04_H
#define MTRACK_04_H
#include <stdio.h>

#define malloc(taille) _my_malloc(taille)
#define free(adresse) _my_free(adresse)

void* _my_malloc(size_t taille);
void _my_free(void* adresse);

#endif
