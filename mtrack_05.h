#ifndef MTRACK_05_H
#define MTRACK_05_H
#include <stddef.h>
#include <stdlib.h>

void* my_malloc(char* fich, const char* fonc, int line, size_t taille);
void my_free(char* fich, const char* fonc, int line, void* adresse);

#define malloc(taille) my_malloc(__FILE__, __func__, __LINE__, taille)
#define free(adresse) my_free(__FILE__, __func__, __LINE__, adresse)

#endif