#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Tires.h"


void afficher_coord_tir(Coord_Tir coord_t) {
    printf("d_x : %d // d_y : %d\n", coord_t.d_x, coord_t.d_y);
    printf("tir_x : %f // tir_y : %f\n\n", coord_t.tir_x, coord_t.tir_y);
}

void afficher_tir(Tir tir) {
    printf("degat [%d] \n", tir.degat);  
    afficher_coord_tir(tir.coord_t);  
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


Tir init_tirs(const int x, const int y, const int x_f, const int y_f) {
    Tir tir;
    assert(x >= 0);
    assert(y >= 0);
    assert(x_f >= 0);
    assert(y_f >= 0);

    
    
    tir.degat = LEGER;
    init_coord_tir(x, y, x_f, y_f, &(tir.coord_t));    

    return tir;
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
