#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Tires.h"


void afficher_coord_tir(Coord_Tir coord_t) {
    printf("d_x : %d // d_y : %d\n", coord_t.d_x, coord_t.d_y);
    printf("tir_x : %f // tir_y : %f\n\n", coord_t.tir_x, coord_t.tir_y);
}

void afficher_tirs(Tirs *tirs) {
    int i;
    for (i = 0; i < NB_TIRES_DEF; ++i) { 
        printf("degat [%d] \n", tirs[i].degat);  
        afficher_coord_tir(tirs[i].coord_t);  
    }
}

void init_coord_tir(const int x, const int y, const int x_f, const int y_f, Coord_Tir *coord_t) {
    assert(x >= 0);
    assert(y >= 0);
    assert(NULL != coord_t);

    coord_t->tir_x = (float)x;
    coord_t->d_x = x;
    coord_t->tir_y = (float)y;
    coord_t->d_y = y;
}


Tirs* init_tirs(const int x, const int y, const int x_f, const int y_f) {
    int j;
    Tirs *tirs = NULL;
    assert(x >= 0);
    assert(y >= 0);

    if (NULL == (tirs = (Tirs*)malloc(sizeof(Tirs) * NB_TIRES_DEF))) {
        printf("Malloc rate init_tirs\n");
        exit(EXIT_FAILURE);
    }
    for (j = 0; j < NB_TIRES_DEF; ++j) {
        tirs[j].degat = 1;
        init_coord_tir(x, y, x_f, y_f, &(tirs[j].coord_t));    
    }

    return tirs;
}

int calculer_tir(Coord_Tir *coord_t, const int xf_t, const int yf_t) {
    float a, b, num = 1;
    assert(NULL != coord_t);
    assert(xf_t >= 0);
    assert(yf_t >= 0);

    a = (float)((yf_t - coord_t->tir_y) / (xf_t - coord_t->tir_x));
    b = (coord_t->tir_y - a * coord_t->tir_x);

    coord_t->tir_x = (coord_t->d_x < xf_t ? coord_t->tir_x + num : coord_t->tir_x - num);

    coord_t->tir_y = (coord_t->d_y < yf_t ? coord_t->tir_y + num : coord_t->tir_y - num);
    coord_t->tir_y = a * coord_t->tir_x + b;
    coord_t->tir_x = (coord_t->tir_y - b) / a;
    return 1;
}

void libere_tirs(Tirs *tirs) {
    assert(NULL != tirs);
    free(tirs);
    tirs = NULL;
}