#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Bonus.h"
#include "Monde.h"

static Element **initialise_tab(const int t_x, const int t_y) {
    int i;
    Element **tab;    
    assert(t_x > 0);
    assert(t_y > 0);
    if (NULL == (tab = (Element**)malloc(sizeof(Element*) * t_x))) {
        printf("Malloc rate initialiser_monde\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < t_x; ++i) {
        if(NULL == (tab[i] = (Element*)malloc(sizeof(Element) * t_y))) {
            printf("Malloc rate initialiser_monde %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    return tab;

}

void initialiser_monde(Monde* monde, const int t_x, const int t_y) {
    int i, j;   
    assert(t_x > 0);
    assert(t_y > 0);
    
    monde->tab = initialise_tab(t_x, t_y);
    for (i = 0; i < t_x; ++i) {
        for (j = 0; j < t_y; ++j) {
            monde->tab[i][j].etats = VIDE;
            monde->tab[i][j].vie = 0;
            monde->tab[i][j].indice = -1;
        }
    }

    monde->vaisseaux = allouer_vaisseaux(BLOC_VAISSEAUX);
    monde->nb_vaisseaux_max = BLOC_VAISSEAUX;
    monde->nb_vaisseaux = 1;

    monde->taille_x = t_x;
    monde->taille_y = t_y;
}

void configure_matiere_monde(Monde* monde, Etats etats, const int x, const int y, const int vie) {
    assert(NULL != monde);
    assert(x > 0);
    assert(y > 0);
    assert(vie > 0);
    if (etats < TIR) {
        monde->tab[x][y].etats = etats;
        monde->tab[x][y].vie = vie;
        monde->tab[x][y].indice = -1;
    }

}

void configure_tir_monde(Monde* monde, Coord_Tir coord_t, Etats etats, Degat degat) {
    assert(NULL != monde);
    if (etats == TIR) {
        monde->tab[(int)(coord_t.tir_x)][(int)(coord_t.tir_y)].etats = etats;
        monde->tab[(int)(coord_t.tir_x)][(int)(coord_t.tir_y)].indice = -1;
        monde->tab[(int)(coord_t.tir_x)][(int)(coord_t.tir_y)].vie = degat;
    }
}

void ajouter_vaisseau_monde(Monde* monde, Vaisseau vaisseau, int x, int y, Etats type, int vie) {
    assert(NULL != monde);
    assert(x > 0);
    assert(y > 0);
    assert(JOUEUR <= type && type <= BOSSFINALE);
    assert(vie > 0);

    /* Si on a atteint la capacité maximum de vaisseau, on la double. */
    if ( monde->nb_vaisseaux >= monde->nb_vaisseaux_max ) {
        monde->nb_vaisseaux_max *= 2;
        monde->vaisseaux = (Vaisseau*)realloc(monde->vaisseaux, sizeof(Vaisseau) * monde->nb_vaisseaux_max);
        if ( NULL == monde->vaisseaux )
            exit(EXIT_FAILURE);
    }

    monde->tab[x][y].etats = type;
    monde->tab[x][y].vie = vie;
    monde->tab[x][y].indice = monde->nb_vaisseaux;

    monde->nb_vaisseaux += 1;
}

void libere_monde(Monde* monde) {
    int i;
    assert(NULL != monde);

    for (i = 0; i < monde->taille_x; ++i) {
        free(monde->tab[i]);
        monde->tab[i] = NULL;
    }

    free(monde->tab);
    monde->tab = NULL;

}