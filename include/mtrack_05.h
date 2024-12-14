/**
 * @file mtrack_05.h
 * @author Raëd CHAMI
 * @brief Définit les fonctions clônes du traceur.
 * @version 2.0
 * @date 2024-12-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef MTRACK_05_H
#define MTRACK_05_H
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Fonction clône de malloc 
 * Trace l'allocation mémoire d'un programme et fournit un affichage dans le rapport d'analyse final.
 * 
 * @param fich Nom de fichier
 * @param fonc Nom de la fonction contenant une allocation mémoire
 * @param line Ligne contenant une allocation mémoire
 * @param taille Taille de la mémoire allouée
 * @return 
 */
void* _my_malloc(char* fich, const char* fonc, int line, size_t taille);

/**
 * @brief Fonction clône de free
 * Trace la libération de mémoire d'un programme et fournit un affichage dans le rapport d'analyse final.
 * 
 * @param fich Nom de fichier 
 * @param fonc Nom de la fonction contenant une libération de mémoire
 * @param line Ligne contenant une libération de mémoire
 * @param adresse Pointeur vers mémoire à libérer
 */
void _my_free(char* fich, const char* fonc, int line, void* adresse);

/**
 * @brief Fonction clône de calloc
 * Trace l'allocation de mémoire pour des tableaux.
 * 
 * @param fich Nom de fichier
 * @param fonc Nom de la fonction contenant une allocation de mémoire
 * @param line Ligne contenant une allocation mémoire
 * @param taille Taille de la mémoire allouée
 * @param n Nombre d'éléments à allouer
 * @return  
 */
void* _my_calloc(char* fich, const char* fonc, int line, size_t taille, size_t n);

/**
 * @brief Fonction clône de realloc
 * Trace la réallocation de mémoire
 * 
 * @param fich Nom de fichier
 * @param fonc Nom de la fonction contenant une réallocation de mémoire
 * @param line Ligne contenant une réallocation mémoire
 * @param adresse Pointeur vers la mémoire à réallouer
 * @param taille Taille de la mémoire réallouée
 * @return
 */
void* _my_realloc(char* fich, const char* fonc, int line, void* adresse, size_t taille);

#define malloc(taille) _my_malloc(__FILE__, __func__, __LINE__, taille)
#define free(adresse) _my_free(__FILE__, __func__, __LINE__, adresse)
#define calloc(n, taille) _my_calloc(__FILE__, __func__, __LINE__, taille, n)
#define realloc(adresse, taille) _my_realloc(__FILE__, __func__, __LINE__, adresse, taille)

#endif
