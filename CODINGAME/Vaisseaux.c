#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"

void afficher_vaisseau(const Type_vaisseau vaisseau) {

    switch(vaisseau) {

        case JOUEUR : printf("JOUEUR "); break;

        case BOT : printf("BOT "); break;

        case MIBOSS : printf("MIBOSS "); break;

        case BOSSFINALE : printf("BOSSFINALE "); break;
        
        default : printf("Erreur "); break;
    }
}

void afficher_vaisseau_details(const Vaisseau vaisseau) {
    printf("[x : %d // y : %d] ", vaisseau.x, vaisseau.y);
    afficher_vaisseau(vaisseau.vaisseau);
    afficher_deplacement(vaisseau.dep);
    afficher_vitesse(vaisseau.vi);
    afficher_tir(vaisseau.tir);
    printf("\n");
    
}

void afficher_vaisseaux_details(const Vaisseau* vaisseaux, const int nb_vaisseaux) {
    int i;
    assert(NULL != vaisseaux);
    assert(nb_vaisseaux > 0);

    for (i = 0; i < nb_vaisseaux; ++i) 
        afficher_vaisseau_details(vaisseaux[i]);
    
}

void afficher_vaisseaux(const Vaisseau* vaisseaux, const int nb_vaisseaux) {
     int i;
     assert(nb_vaisseaux > 0);
     assert(NULL != vaisseaux);

     for (i = 0; i < nb_vaisseaux; ++i) {
        afficher_vaisseau(vaisseaux[i].vaisseau);
        printf("\n");
    }
}

Vaisseau* allouer_vaisseaux(const int nb_vaisseaux) {
    int i;
    Vaisseau vais_defaut = {0, 0, JOUEUR, STOP, LENT, SIMPLE};
    Vaisseau bot_defaut = {nb_vaisseaux, nb_vaisseaux, BOT, STOP, LENT, RIEN};
    Vaisseau* vaisseaux = NULL;

    assert(nb_vaisseaux > 0);

    if (NULL == (vaisseaux = (Vaisseau*)malloc(sizeof(Vaisseau) * nb_vaisseaux))) {
        printf("Malloc rate \t\tallouer_vaisseaux\n");
        exit(EXIT_FAILURE);
    }

    vaisseaux[0] = vais_defaut;

    for (i = 1; i < nb_vaisseaux; ++i) {
        vaisseaux[i] = bot_defaut;
        vaisseaux[i].x = nb_vaisseaux - i;

    }

    return vaisseaux;
}


void libere_vaisseaux(Vaisseau* vaisseaux, const int nb_vaisseaux) {
    assert(nb_vaisseaux > 0);
    assert(NULL != vaisseaux);

    free(vaisseaux);

    vaisseaux = NULL;

}

void deplacer_vaisseau(Vaisseau* vaisseau) {
    assert(NULL != vaisseau);

    switch ( vaisseau->dep ) {
        case NORD:
            vaisseau->y -= vaisseau->vi;
            break;
        case EST:
            vaisseau->x += vaisseau->vi;
            break;
        case SUD:
            vaisseau->y += vaisseau->vi;
            break;
        case OUEST:
            vaisseau->x -= vaisseau->vi;
            break;
        default:
            break;
    }
}