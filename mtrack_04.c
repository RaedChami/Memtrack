#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool flag = false;

typedef struct {
    void* adresse;
    size_t taille_allouee;
    bool alloc;
} Cellule;

typedef struct {
    Cellule *cellules;
    size_t taille;
    size_t capacite;
    int cmpt_malloc;
    int cmpt_free_reussi;
    int cmpt_free_echouee;
    int cmpt_memoire_allouee;
    int cmpt_memoire_liberee;
} Environnement;

Environnement table;


void init_environnement() {
    table.capacite = 2;
    table.cellules = (Cellule*)malloc(table.capacite * sizeof(Cellule));
    table.taille = 0;
    table.cmpt_malloc = 0;
    table.cmpt_free_reussi = 0;
    table.cmpt_free_echouee = 0;
    table.cmpt_memoire_allouee = 0;
    table.cmpt_memoire_liberee = 0; 
}

void nettoyage_env() {  // Nettoyage de l'environnement
    if (table.cellules) free(table.cellules);  // On libère la mémoire allouée   
    table.capacite = 0;
    table.taille = 0;
    table.cmpt_malloc = 0;
    table.cmpt_free_reussi = 0;
    table.cmpt_free_echouee = 0;
    table.cmpt_memoire_allouee = 0;
    table.cmpt_memoire_liberee = 0;     
}

void bilan_table() {    // Affichage du bilan
    printf("–––––––––––––––––––––––\n");
    printf("BILAN FINAL\n");
    (table.cmpt_memoire_allouee > 1) ? printf("total mémoire allouée : %d octets\n", table.cmpt_memoire_allouee) : printf("total mémoire allouée : %d octet\n", table.cmpt_memoire_allouee);
    (table.cmpt_memoire_liberee > 1) ? printf("total mémoire libérée : %d octets\n", table.cmpt_memoire_liberee) : printf("total mémoire libérée : %d octet\n", table.cmpt_memoire_liberee);
    double ratio = (table.cmpt_memoire_allouee > 0) ? ((double)table.cmpt_memoire_liberee / table.cmpt_memoire_allouee) * 100.0 : 0.0;
    printf("ratio                 : %.2f%%\n", ratio);
    (table.cmpt_malloc > 1) ? printf("<malloc>              : %d appels\n", table.cmpt_malloc) : printf("<malloc>              : %d appel\n", table.cmpt_malloc);
    (table.cmpt_free_reussi > 1) ? printf("<free>                : %d appels correct\n", table.cmpt_free_reussi) : printf("<free>                : %d appel correct\n", table.cmpt_free_reussi);
    (table.cmpt_free_echouee > 1) ? printf("                      : %d appels incorrect\n", table.cmpt_free_echouee) : printf("                      : %d appel incorrect\n", table.cmpt_free_echouee);
    printf("–––––––––––––––––––––––\n");
}

void f(void) {  // Fonction Sortie
    bilan_table();
    flag = false;
    nettoyage_env();    
}
 
void activation() {  // Fonction Activation
    if (!flag) {   
        init_environnement();
        flag = true;
        atexit(f);
    }
}

void* my_malloc(size_t taille) {
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
    table.cmpt_memoire_allouee++;
    printf("(0%d) malloc(%zu)->%p\n", table.cmpt_malloc, taille, adresse);
    return adresse;
}

void my_free(void* adresse) {
    activation();   // Activation à l'appel du clone de free()
    if (!adresse) { 
        table.cmpt_free_echouee++; 
        return;
    }
    for (int i = 0; i < table.taille; i++) {
        if (adresse == table.cellules[i].adresse) {
            if (!table.cellules[i].alloc) {
                table.cmpt_free_echouee++;
                fprintf(stderr, "(0%d) free(%p) - ERROR : double free detected\n", table.cmpt_free_echouee, adresse);
                return;
            } else {
                free(adresse);
                table.cellules[i].alloc = false;
                table.cmpt_free_reussi++;
                table.cmpt_memoire_liberee += table.cellules[i].taille_allouee;
                fprintf(stderr, "(0%d) free(%p)\n", table.cmpt_free_reussi, adresse);
                return;
            }
        }
    }
    table.cmpt_free_echouee++;
    fprintf(stdout, "(0%d) free(%p) - ERROR : illegal address -> ignored\n", table.cmpt_free_echouee, adresse);
}