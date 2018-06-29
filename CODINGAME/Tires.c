#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

    coord_t->tir_x = x;
    coord_t->tir_y = y;

}

int calculer_tir(Coord_Tir *coord_t, const int xf_t, const int yf_t, const int limite_x, const int limite_y) {
    int cond1, cond2, d_x, d_y;
    assert(NULL != coord_t);
    assert(xf_t >= 0);
    assert(yf_t >= 0);

    d_x = coord_t->tir_x;
    d_y = coord_t->tir_y;
    cond1 = coord_t->tir_x > 0 && coord_t->tir_x < limite_x;
    cond2 = coord_t->tir_y > 0 && coord_t->tir_y < limite_y;

    while (cond1 && cond2) {
        (d_x < xf_t ? --coord_t->tir_x : ++coord_t->tir_x);
        (d_y < yf_t ? --coord_t->tir_y : ++coord_t->tir_y);
   }

   return 1;

}
