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

void afficher_coord_tir(Coord_Tir coord_t) {
    printf("d_x : %d // d_y : %d\n", coord_t.d_x, coord_t.d_y);
    printf("tir_x : %f // tir_y : %f\n\n", coord_t.tir_x, coord_t.tir_y);
}

void afficher_tirs(Tirs *tirs) {
    int i;
    for (i = 0; i < NB_TIRES_DEF; ++i) {
        afficher_tir(tirs[i].tir);

        if (tirs[i].tir != 0) {
            afficher_coord_tir(tirs[i].coord_t);
        }

    }
}

void init_coord_tir(const int x, const int y, Coord_Tir *coord_t) {
    assert(x >= 0);
    assert(y >= 0);
    assert(NULL != coord_t);

    coord_t->tir_x = (float)x;
    coord_t->d_x = x;
    coord_t->tir_y = (float)y;
    coord_t->d_y = y;

}

Tirs* init_tirs(const Tir tir, const int x, const int y) {
    int j;
    Tirs *tirs = NULL;
    assert(x >= 0);
    assert(y >= 0);

    if (NULL == (tirs = (Tirs*)malloc(sizeof(Tirs) * NB_TIRES_DEF))) {
        printf("Malloc rate init_tirs\n");
        exit(EXIT_FAILURE);
    }
    for (j = 0; j < NB_TIRES_DEF; ++j) {
        tirs[j].tir = tir;
        init_coord_tir(x, y, &(tirs[j].coord_t));    
    }

    return tirs;
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