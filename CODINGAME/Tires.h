/* Auteurs: LOPES MENDES Ailton
            Lin Gerald
            Wadan Samy
*  Creation: 26/06/2018
*  Modification: 29/06/2018*/
#ifndef __TIRES__
#define __TIRES__

#define MAX_T 4
#define NB_TIRES_DEF 100

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

typedef struct {
    Tir tir;
    Coord_Tir coord_t;
}Tirs;

/* Affice le Tir.*/
void afficher_tir(Tir t);

/*Affiche les Tirs,*/
void afficher_tirs(Tirs *tirs);

void afficher_coord_tir(Coord_Tir coord_t);

/* Initialise les variables dans `coord_t`*/
void init_coord_tir(const int x, const int y, Coord_Tir *coord_t);

/* Initialise tirs.*/
Tirs* init_tirs(const Tir tir, const int x, const int y);

/* Calculer l'équation de la droite `y=ax+b`.
 * Obtient `a` et `b` decale les tir_x et tir_y de 1.
 * Recalcule tir_x et tir_y.*/
int calculer_tir(Coord_Tir *coord_t, const int xf_t, const int yf_t);

void libere_tirs(Tirs *tirs);


#endif