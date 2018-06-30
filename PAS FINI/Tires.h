/* Auteurs: LOPES MENDES Ailton
            Lin Gerald
            Wadan Samy
*  Creation: 26/06/2018
*  Modification: 29/06/2018*/
#ifndef __TIRES__
#define __TIRES__

#define MAX_T 4
#define NB_TIRES_DEF 100

typedef struct {
   	int d_x;
   	int d_y;
    int x_f;
    int y_f;
    float tir_x;
    float tir_y;
}Coord_Tir;

typedef struct {
    int degat;
    Coord_Tir coord_t;
}Tirs;


/*Affiche les Tirs,*/
void afficher_tirs(Tirs *tirs);

void afficher_coord_tir(Coord_Tir coord_t);

/* Initialise les variables dans `coord_t`*/
void init_coord_tir(const int x, const int y, const int x_f, const int y_f, Coord_Tir *coord_t);

/* Initialise tirs.*/
Tirs* init_tirs(const int x, const int y, const int x_f, const int y_f);

/* Calculer l'équation de la droite `y=ax+b`.
 * Obtient `a` et `b` decale les tir_x et tir_y de 1.
 * Recalcule tir_x et tir_y.*/
int calculer_tir(Coord_Tir *coord_t, const int xf_t, const int yf_t);

void libere_tirs(Tirs *tirs);


#endif