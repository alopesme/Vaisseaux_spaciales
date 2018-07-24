#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vitesse.h"
#include "Deplacement.h"
#include "Vaisseaux.h"

void afficher_vaisseau_details(const Vaisseau vaisseau) {
    afficher_deplacement(vaisseau.dep);
    afficher_vitesse(vaisseau.vi);
    printf("\n");
    
}

void afficher_vaisseaux_details(const Vaisseau* vaisseaux, const int nb_vaisseaux) {
    int i;
    assert(NULL != vaisseaux);
    assert(nb_vaisseaux > 0);

    for (i = 0; i < nb_vaisseaux; ++i) 
        afficher_vaisseau_details(vaisseaux[i]);
    
}

Vaisseau* allouer_vaisseaux(const int nb_vaisseaux, const int x, const int y, const int larg) {
    int i;
    Vaisseau vais_defaut = {x, y, STOP, LENT};
    Vaisseau* vaisseaux = NULL;
    assert(larg > 0);
    assert(x >= larg / 2);
    assert(y >= larg / 2);

    assert(nb_vaisseaux > 0);

    if (NULL == (vaisseaux = (Vaisseau*)malloc(sizeof(Vaisseau) * nb_vaisseaux))) {
        printf("Malloc rate \t\tallouer_vaisseaux\n");
        exit(EXIT_FAILURE);
    }

    vaisseaux[0] = vais_defaut;

    for (i = 1; i < nb_vaisseaux; ++i) {
        vaisseaux[i] = vais_defaut;
        vaisseaux[i].x = i * larg;
        vaisseaux[i].y = larg;
    }

    return vaisseaux;
}

void calculer_prochaine_case_vaisseau(Vaisseau *v) {
    assert(NULL != v);
    switch ( v->dep ) {
        case NORD:
            v->y -= v->vi;
            if ( v->y < 0 )
                v->y = 0;
            break;
        case OUEST:
            v->x += v->vi;
            break;
        case SUD:
            v->y += v->vi;
            break;
        case EST:
            v->x -= v->vi;
            if ( v->x < 0)
               v->x = 0;
            break;
        default:
            break;
    }
}


void libere_vaisseaux(Vaisseau* vaisseaux, const int nb_vaisseaux) {
    assert(nb_vaisseaux > 0);
    assert(NULL != vaisseaux);

    free(vaisseaux);

    vaisseaux = NULL;

}
