/* Auteurs: LOPES MENDES Ailton
            Lin Gerald
            Wadan Samy
*  Creation: 26/06/2018
*  Modification: 29/06/2018*/
#ifndef __TIRES__
#define __TIRES__

/* Le nombre de tirs coorespond au nom.
 * Sauf pour CANON et RIEN.*/
typedef enum {
    SIMPLE = 1,
    DOUBLE,
    TRIPLE,
    CANON = -1,
    RIEN = 0

}Tir;

typedef struct {
   	int d_x;
   	int d_y;
    float tir_x;
    float tir_y;
    
}Coord_Tir;

/* Affice le Tir.*/
void afficher_tir(Tir t);

/* Initialise les variables dans `coord_t`*/
void init_coord_tir(const int x, const int y, Coord_Tir *coord_t);

/* Calculer l'équation de la droite `ỳ=ax+b`.
 * Obtient `a` et `b` decale les tir_x et tir_y de 1.
 * Recalcule tir_x et tir_y.*/
int calculer_tir(Coord_Tir *coord_t, const int xf_t, const int yf_t);

#endif