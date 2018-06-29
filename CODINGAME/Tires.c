#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Tires.h"

void afficher_tir(Tir t) {
    switch(t) {
        case SIMPLE : printf("SIMPLE [%d] ", SIMPLE); break;

        case DOUBLE : printf("DOUBLE [%d] ", DOUBLE); break;

        case TRIPLE : printf("TRIPLE [%d] ", TRIPLE); break;

        case CANON : printf("CANON [%d] ", CANON); break;

        case RIEN : printf("RIEN [%d] ", RIEN); break;
        
        default : printf("Erreur "); break;
    }
}

void init_coord_tir(const int x, const int y, Coord_Tir *coord_t) {
    assert(x >= 0);
    assert(y >= 0);
    assert(NULL != coord_t);

    coord_t->d_x = coord_t->tir_x = (float)x;
    coord_t->d_y = coord_t->tir_y = (float)y;

}

int init_tirs(Tirs *tirs, const int nb_tires) {
    assert(NULL != nb_tires);

    if (NULL == (tirs = (Tirs*)malloc(sizeof(Tirs) * nb_tires))) {
        printf("Malloc rate init_tirs\n");
        exit(EXIT_FAILURE);
    }
    return 1;
}

int calculer_tir(Coord_Tir *coord_t, const int xf_t, const int yf_t) {
    float a, b;
    assert(NULL != coord_t);
    assert(xf_t >= 0);
    assert(yf_t >= 0);

    a = (float)((yf_t - coord_t->tir_y) / (xf_t - coord_t->tir_x));
    b = (coord_t->tir_y - a * coord_t->tir_x);

    coord_t->tir_x = (coord_t->d_x < xf_t ? coord_t->tir_x + 1 : coord_t->tir_x - 1);
    coord_t->tir_y = (coord_t->d_y < yf_t ? coord_t->tir_y + 1 : coord_t->tir_y - 1);

    coord_t->tir_y = a * coord_t->tir_x + b;

    coord_t->tir_x = (coord_t->tir_y - b) / a;
    return 1;
}

void libere_tirs(Tirs *tirs) {
    assert(NULL != tirs);
    free(tirs);
    tirs = NULL;
}