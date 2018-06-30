#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Bonus.h"
#include "Monde2.h"

static Element **initialise_tab(const int t_x, const int t_y) {
    int i;
    Element **tab;    
    assert(t_x > 0);
    assert(t_y > 0);
    if (NULL == (tab = (Element**)malloc(sizeof(Element*) * t_x))) {
        printf("Malloc rate initialiser_monde2\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < t_x; ++i) {
        if(NULL == (tab[i] = (Element*)malloc(sizeof(Element) * t_y))) {
            printf("Malloc rate initialiser_monde2 %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    return tab;

}

void initialiser_monde2(Monde2* monde, const int t_x, const int t_y) {
    int i, j;   
    assert(t_x > 0);
    assert(t_y > 0);

    monde->tab = initialise_tab(t_x, t_y);
    for (i = 0; i < t_x; ++i) {
        for (j = 0; j < t_y; ++j) {
            monde->tab[i][j].etats = VIDE;
            monde->tab[i][j].indice = 0;
        }
    }

    monde->taille_x = t_x;
    monde->taille_y = t_y;
}

void configure_matiere_monde(Monde2* monde, const int x, const int y, const int indice,  Etats etats) {
    assert(NULL != monde);
    assert(x > 0);
    assert(y > 0);
    if (etats < TIR) {
        monde->tab[x][y].etats = etats;
        monde->tab[x][y].indice = indice;
    }

}

void configure_tir_monde(Monde2* monde, Coord_Tir coord_t, Etats etats, const int indice) {
    assert(NULL != monde);
    if (etats == TIR) {
        monde->tab[(int)(coord_t.tir_x)][(int)(coord_t.tir_y)].etats = etats;
        monde->tab[(int)(coord_t.tir_x)][(int)(coord_t.tir_y)].indice = indice;
    }
}

void configure_vaisseau_monde(Monde2* monde, Vaisseau vaisseau, Etats etats, const int indice) {
    assert(NULL != monde);
    if (etats < BONUS1 && etats > TIR) {
        monde->tab[vaisseau.x][vaisseau.y].etats = etats;
        monde->tab[vaisseau.x][vaisseau.y].indice = indice;
    }
}

void libere_monde(Monde2* monde) {
    int i;
    assert(NULL != monde);

    for (i = 0; i < monde->taille_x; ++i) {
        free(monde->tab[i]);
        monde->tab[i] = NULL;
    }

    free(monde->tab);
    monde->tab = NULL;

}