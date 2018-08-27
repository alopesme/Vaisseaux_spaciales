/* Auteurs: LOPES MENDES Ailton
            Lin Gerald
            Wadan Samy
*  Creation: 26/06/2018
*  Modification: 17/07/2018*/
#ifndef __TIRES__
#define __TIRES__


/*
Espace commentaire : Ajout de fonction `validation_tir`
*/

typedef struct {
   	int d_x;
   	int d_y;
    int x_f;
    int y_f;
    float tir_x;
    float tir_y;
    int larg;
}Coord_Tir;

typedef enum {
    LEGER = 1,
    INTERMEDIAIRE = 5,
    FORT = 10,
    FATALE = 50
}Degat;

typedef struct {
    Degat degat;
    Coord_Tir coord_t;
}Tir;


/*Affiche les Tirs,*/
void afficher_tir(Tir tir);

/*Affiche coord_tir.*/
void afficher_coord_tir(Coord_Tir coord_t);

/* Initialise les variables dans `coord_t`*/
void init_coord_tir(const int x, const int y, const int x_f, const int y_f, const int larg, Coord_Tir *coord_t);

/* Initialise tirs.*/
Tir init_tirs(const int x, const int y, const int x_f, const int y_f, const int larg);

/* Calculer l'équation de la droite `y=ax+b`.
 * Obtient `a` et `b` decale les tir_x et tir_y de 1.
 * Recalcule tir_x et tir_y.*/
int calculer_tir(Coord_Tir *coord_t, const int num);

/* Verifie si le tir n'est pas sorti du cadre.
 * Renvoie 1 si dans le cadre 0 sinon.*/
int validation_tir(Coord_Tir *coord_t, const int d_x, const int d_y, const int t_x, const int t_y);

/* Verifie si les coordonnees du `tir` est entre les coordonnees du parametre.
 * Si oui renvoie 1 sinon 0.*/
int coord_tir_touche(Tir tir, const int x1, const int y1, const int x2, const int y2);

#endif