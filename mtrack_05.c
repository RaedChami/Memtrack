/**
 * @file mtrack_05.c
 * @author Raëd CHAMI
 * @brief Fichier source du traceur
 * @version 2.0
 * @date 2024-12-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * @brief Indique si le traceur est activé
 * 
 */
bool _tracker_flag = false;

/**
 * @brief Structure représantant une cellule 
 * 
 */
typedef struct {
    void* adresse;
    size_t taille_allouee;
    bool alloc;
} _tracker_cell;

/**
 * @brief Table d'enregistrement des cellules
 * 
 */
typedef struct {
    _tracker_cell *cellules;
    size_t taille;
    size_t capacite;
    int cmpt_malloc;
    int cmpt_calloc;
    int cmpt_realloc;
    int cmpt_free_reussi;
    int cmpt_free_echouee;
    int cmpt_memoire_allouee;
    int cmpt_memoire_liberee;
} Environnement;

Environnement table;

/**
 * @brief Initialise l'environnement
 * 
 */
void init_environnement() {
    table.capacite = 2;
    table.cellules = (_tracker_cell*)malloc(table.capacite * sizeof(_tracker_cell));
    table.taille = 0;
    table.cmpt_malloc = 0;
    table.cmpt_calloc = 0;
    table.cmpt_realloc = 0;
    table.cmpt_free_reussi = 0;
    table.cmpt_free_echouee = 0;
    table.cmpt_memoire_allouee = 0;
    table.cmpt_memoire_liberee = 0; 
}

/**
 * @brief Nettoie l'environnement
 * 
 */
void nettoyage_env() { 
    if (table.cellules) free(table.cellules);  // libère la mémoire allouée
    table.capacite = 0;
    table.taille = 0;
    table.cmpt_malloc = 0;
    table.cmpt_calloc = 0;
    table.cmpt_realloc = 0;
    table.cmpt_free_reussi = 0;
    table.cmpt_free_echouee = 0;
    table.cmpt_memoire_allouee = 0;
    table.cmpt_memoire_liberee = 0;     
}

/**
 * @brief Affiche le bilan d'analyse du traceur
 * 
 */
void bilan_table() {
    printf("\033[32m–––––––––––––––––––––––\n");
    printf("BILAN FINAL\n");
    (table.cmpt_memoire_allouee > 1) ? printf("total mémoire allouée : %d octets\n", table.cmpt_memoire_allouee) : printf("total mémoire allouée : %d octet\n", table.cmpt_memoire_allouee);
    (table.cmpt_memoire_liberee > 1) ? printf("total mémoire libérée : %d octets\n", table.cmpt_memoire_liberee) : printf("total mémoire libérée : %d octet\n", table.cmpt_memoire_liberee);
    double ratio = (table.cmpt_memoire_allouee > 0) ? ((double)table.cmpt_memoire_liberee / table.cmpt_memoire_allouee) * 100.0 : 0.0;
    printf("ratio                 : %.2f%%\n", ratio);
    (table.cmpt_malloc > 1) ? printf("<malloc>              : %d appels\n", table.cmpt_malloc) : printf("<malloc>              : %d appel\n", table.cmpt_malloc);
    (table.cmpt_calloc > 1) ? printf("<calloc>              : %d appels\n", table.cmpt_calloc) : printf("<calloc>              : %d appel\n", table.cmpt_calloc);
    (table.cmpt_realloc > 1) ? printf("<realloc>             : %d appels\n", table.cmpt_realloc) : printf("<realloc>             : %d appel\n", table.cmpt_realloc);
    (table.cmpt_free_reussi > 1) ? printf("<free>                : %d appels correct\033[0m\n", table.cmpt_free_reussi) : printf("<free>                : %d appel correct\033[0m\n", table.cmpt_free_reussi);
    (table.cmpt_free_echouee > 1) ? printf("                      \033[31m: %d appels incorrect\033[0m\n", table.cmpt_free_echouee) : printf("                      \033[31m: %d appel incorrect\033[0m\n", table.cmpt_free_echouee);
    printf("\033[32m–––––––––––––––––––––––\n");
}

/**
 * @brief Affiche des informations supplémentaires sur l'utilisation du traceur
 * 
 */
void affiche_infos_machine() {
    const char* user = getenv("USER");
    char host[1024];
    fprintf(stdout, "%s %s\n", __DATE__, __TIME__);
    if (user) fprintf(stdout, "USER : %s\n", user);
    if (!gethostname(host, sizeof(host))) fprintf(stdout, "HOST : %s\n", host);
    fprintf(stdout, "–––––––––––––––––––––––\n");

}

/**
 * @brief Fonction de prototype regroupant les appels de fin
 * 
 */
void f(void) { 
    bilan_table();
    _tracker_flag = false;
    nettoyage_env();    
}

/**
 * @brief Active le traceur au premier appel d'une fonction clône
 * 
 * @return
 */
void activation() {
    if (!_tracker_flag) {   
        init_environnement();
        _tracker_flag = true;  
        atexit(f);
        printf("\033[32m–activate tracker – [VERS.5]–\n");
        printf("––––––––––––––––-\n");  
        affiche_infos_machine();       
    }    
}

void* _my_malloc(char* fich, const char* fonc, int line, size_t taille) {
    activation();   // Activation à l'appel du clone de malloc()
    void* adresse = malloc(taille);
    if (!adresse) exit(1);
    for (int i = 0; i < table.taille; i++) {
        if (adresse == table.cellules[i].adresse) {
            table.cellules[i].taille_allouee = taille;
            table.cellules[i].alloc = true;
            return adresse;
        }
    }
    if (table.taille >= table.capacite) {      // Si la taille est plus grande que la capacité, on renvoie une erreur
        fprintf(stderr, "Capacité dépassée");
        exit(1);
    }

    table.cellules[table.taille].adresse = adresse;
    table.cellules[table.taille].taille_allouee = taille; 
    table.cellules[table.taille].alloc = true;
    table.taille++;
    table.cmpt_malloc++;
    table.cmpt_memoire_allouee += taille;   
    printf("in file <%s> function <%s> line <0%d> - (call#0%d) - malloc(%zu)->%p\n", fich, fonc, line, table.cmpt_malloc, taille, adresse);
    return adresse;
}

void _my_free(char* fich, const char* fonc, int line, void* adresse) {
    /**
     * @brief Fonction clône de free.
     * 
     */
    activation();   // Activation à l'appel du clone de free()
    if (!adresse) { 
        table.cmpt_free_echouee++; 
        return;
    }
    for (int i = 0; i < table.taille; i++) {
        if (adresse == table.cellules[i].adresse) {
            if (!table.cellules[i].alloc) {
                table.cmpt_free_echouee++;
                fprintf(stderr, "in file <%s> function <%s> line <0%d> - (call#0%d) - free(%p) \033[31m- ERROR : double free detected\033[0m\n", fich, fonc, line, table.cmpt_free_echouee, adresse);
                return;
            } else {
                free(adresse);
                table.cellules[i].alloc = false;
                table.cmpt_free_reussi++;
                table.cmpt_memoire_liberee += table.cellules[i].taille_allouee;
                fprintf(stdout, "in file <%s> function <%s> line <0%d> - (call#0%d) - free(%p)\n", fich, fonc, line, table.cmpt_free_reussi, adresse);
                return;
            }
        }
    }
    table.cmpt_free_echouee++;
    fprintf(stderr, "\033[32min file <%s> function <%s> line <0%d> - (call#0%d) - free(%p) \033[31m- ERROR : illegal address -> ignored\033[0m\n", fich, fonc, line, table.cmpt_free_echouee, adresse);
}


void* _my_calloc(char* fich, const char* fonc, int line, size_t taille, size_t n) {
    activation();    // Activation du traceur à l'appel de calloc
    size_t taille_totale = n * taille;
    void* adresse = calloc(n, taille);
    if (!adresse) exit(1);
    for (int i = 0; i < table.taille; i++) {
        if (adresse == table.cellules[i].adresse) {
            table.cellules[i].taille_allouee = taille_totale;
            table.cellules[i].alloc = true;
            return adresse;
        }
    }
    if (table.taille >= table.capacite) {      // Si la taille est plus grande que la capacité, on renvoie une erreur
        fprintf(stderr, "Capacité dépassée");
        exit(1);
    }

    table.cellules[table.taille].adresse = adresse;
    table.cellules[table.taille].taille_allouee = taille_totale; 
    table.cellules[table.taille].alloc = true;
    table.taille++;
    table.cmpt_calloc++;
    table.cmpt_memoire_allouee += n;   
    printf("in file <%s> function <%s> line <0%d> - (call#0%d) - calloc(%zu)->%p\n", fich, fonc, line, table.cmpt_calloc, taille, adresse);
    return adresse;

}

void* _my_realloc(char* fich, const char* fonc, int line, void* adresse, size_t taille) {
    activation();  // Activation du traceur à l'appel de realloc
    size_t ancienne_taille = 0;
    for (int i = 0; i < table.taille; i++) {
        if (table.cellules[i].adresse == adresse && table.cellules[i].alloc) {
            ancienne_taille = table.cellules[i].taille_allouee;
            table.cellules[i].alloc = false;  
            break;
        }
    }

    void* nouvelle_adresse = realloc(adresse, taille);
    if (!nouvelle_adresse) exit(1);

    if (table.taille >= table.capacite) {  // Si la taille est plus grande que la capacité, on renvoie une erreur
        fprintf(stderr, "Capacité de la table dépassée\n");
        exit(1);
    }

    table.cellules[table.taille].adresse = nouvelle_adresse;
    table.cellules[table.taille].taille_allouee = taille;
    table.cellules[table.taille].alloc = true;
    table.taille++;

    table.cmpt_realloc++;

    printf("in file <%s> function <%s> line <%d> - (call#%d) - realloc(%zu)->%p\n", fich, fonc, line, table.cmpt_realloc, taille, nouvelle_adresse);
    return nouvelle_adresse;
}
