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

void init_coord_tir(const int x, const int y, const int x_f, const int y_f, Coord_Tir *coord_t) {
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

int calculer_tir(Coord_Tir *coord_t) {
    /*float a, b, num = 1;
    assert(NULL != coord_t);
    printf("[[[[[[[[[[[[[[[[[[[[[[[[%d %f]]]]]]]]]]]]]]]]]]]]\n\n\n", coord_t->x_f, coord_t->tir_x);
    a = (float)((coord_t->y_f - coord_t->tir_y) / (coord_t->x_f - coord_t->tir_x));
    printf("[[[[[[[[[[[[[[[[[[[[[[[[%d %f]]]]]]]]]]]]]]]]]]]]\n\n\n", coord_t->y_f, coord_t->tir_x);
    b = (coord_t->tir_y - a * coord_t->tir_x);

    coord_t->tir_x = (coord_t->d_x < coord_t->x_f ? coord_t->tir_x + num : coord_t->tir_x - num);

    coord_t->tir_y = (coord_t->d_y < coord_t->y_f ? coord_t->tir_y + num : coord_t->tir_y - num);
    coord_t->tir_y = a * coord_t->tir_x + b;
    if (a != 0)
        coord_t->tir_x = (coord_t->tir_y - b) / a;
    afficher_coord_tir(*coord_t);*/

    float sum_x, sum_y;
    assert(NULL != coord_t);

    sum_x = coord_t->x_f - coord_t->d_x; sum_y = coord_t->y_f - coord_t->d_y;
    if (pow(sum_x, 2) < pow(sum_y, 2)) {
        sum_x = 1 / sum_x;
        sum_y = 1;
    }

    else {
        sum_y = 1 / sum_y;
        sum_x = 1;
    }

    sum_x = (coord_t->d_x > coord_t->x_f && sum_x > 0 ? -sum_x : sum_x);
    sum_y = (coord_t->d_y > coord_t->y_f && sum_y > 0 ? -sum_y : sum_y);

    coord_t->tir_x += sum_x;
    coord_t->tir_y += sum_y;

    return 1;
}


int validation_tir(Coord_Tir *coord_t, const int t_x, const int t_y) {
    Coord_Tir tmp;
    int x, y;
    assert(NULL != coord_t);
    tmp = *coord_t;

    calculer_tir(&tmp);
    x = (int)tmp.tir_x; y = (int)tmp.tir_y;
    if ((x < 0 || x > t_x) || (y < 0 || y > t_y))
        return 0;
    *coord_t = tmp;
    return 1;
}