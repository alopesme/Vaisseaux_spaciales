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
    
    int tir_x;
    int tir_y;
    
}Coord_Tir;

/* Affice le Tir.*/
void afficher_tir(Tir t);

/* Initialise les variables dans `coord_t`*/
void init_coord_tir(const int x, const int y, Coord_Tir *coord_t);

/* Sert à calculer les coordonnees du tir.
 * Elles vont dependre de `xf_t` et `ỳf_t`.
 * Tout d'abord elle calcule jusqu'aux `limite_x` et `limite_y` par rapport à `xf_t` et `yf_t`.*/
int calculer_tir(Coord_Tir *coord_t, const int xf_t, const int yf_t, const int limite_x, const int limite_y);

#endif