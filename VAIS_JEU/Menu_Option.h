/* Auteurs: LOPES MENDES Ailton
			LAMBERT--DELAVAQUERIE Fabien
* Creation: 10/04/2018
* Modification: 10/04/2018*/

#ifndef __MENU_OPTION__
#define __MENU_OPTION__



typedef struct MENU_OPTION
{
    int x[10];
    int largeur_x;
    int largeur_y;
    int y[10];
    char message[10][100];

}Menu_option;
/*Alloue tableau `char**` et alloue aussi tableau de int `x` et `y`*/
int alluoe_texte(int nb_x, int nb_y, Menu_option *menu);

/* Initialise les coordonnes des cases avec texte du menu de depart*/
Menu_option initialisation_Menu_option(int taille_x, int taille_y, int nb_x, int nb_y, char *texte[]);

#endif