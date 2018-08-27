#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Tires.h"


void afficher_coord_tir(Coord_Tir coord_t) {
    printf("d_x : %d // d_y : %d\n", coord_t.d_x, coord_t.d_y);
    printf("x_f : %d // y_f : %d\n", coord_t.x_f, coord_t.y_f);
    printf("tir_x : %f // tir_y : %f\n\n", coord_t.tir_x, coord_t.tir_y);
}

void afficher_tir(Tir tir) {
    printf("degat [%d] \n", tir.degat);  
    afficher_coord_tir(tir.coord_t);  
}

void init_coord_tir(const int x, const int y, const int x_f, const int y_f, const int larg, Coord_Tir *coord_t) {
    assert(x >= 0);
    assert(y >= 0);
    assert(NULL != coord_t);

    coord_t->tir_x = (float)x;
    coord_t->d_x = x;
    coord_t->x_f = x_f;
    coord_t->tir_y = (float)y;
    coord_t->d_y = y;
    coord_t->y_f = y_f;
}


Tir init_tirs(const int x, const int y, const int x_f, const int y_f, const int larg) {
    Tir tir;
    assert(x >= 0);
    assert(y >= 0);
    assert(x_f >= 0);
    assert(y_f >= 0);
    
    tir.degat = LEGER;
    init_coord_tir(x, y, x_f, y_f, larg, &(tir.coord_t));    

    return tir;
}

int calculer_tir(Coord_Tir *coord_t, const int num) {

    float sum_x, sum_y;
    assert(NULL != coord_t);

    sum_x = coord_t->x_f - coord_t->d_x; sum_y = coord_t->y_f - coord_t->d_y;
    if (pow(sum_x, 2) < pow(sum_y, 2)) {
        sum_x = num / (sum_y / sum_x);
        sum_y = num;
    }

    else {
        sum_y = num / (sum_x / sum_y);
        sum_x = num;
    }

    if (coord_t->d_x > coord_t->x_f)
        sum_x = sum_x > 0 ? -sum_x : sum_x;

    else
        sum_x = sum_x < 0 ? -sum_x : sum_x;

    if (coord_t->d_y > coord_t->y_f)
        sum_y = sum_y > 0 ? -sum_y : sum_y;

    else
        sum_y = sum_y < 0 ? -sum_y : sum_y;


    coord_t->tir_x += sum_x;
    coord_t->tir_y += sum_y;

    return 1;
}


int validation_tir(Coord_Tir *coord_t, const int d_x, const int d_y, const int t_x, const int t_y) {
    Coord_Tir tmp;
    int x, y;
    assert(NULL != coord_t);
    tmp = *coord_t;

    calculer_tir(&tmp, 1);
    x = (int)tmp.tir_x; y = (int)tmp.tir_y;
    if ((x < d_x || x > t_x) || (y < d_y || y > t_y))
        return 0;
    *coord_t = tmp;
    return 1;
}

int coord_tir_touche(Tir tir, const int x1, const int y1, const int x2, const int y2) {
    int t_x, t_y;
    assert(x1 >= 0);
    assert(y1 >= 0);
    assert(x2 >= 0);
    assert(y2 >= 0);

    t_x = (int)tir.coord_t.tir_x; t_y = (int)tir.coord_t.tir_y;

    if ((x1 <= t_x && t_x <= x2) && (y1 <= t_y && t_y <= y2))
        return 1;

    return 0;

}