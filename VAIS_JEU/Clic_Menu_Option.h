/* Auteurs: LOPES MENDES Ailton
			LAMBERT--DELAVAQUERIE Fabien
* Creation: 10/04/2018
* Modification: 10/04/2018*/

#ifndef __CLIC_MENU_OPTION___
#define __CLIC_MENU_OPTION__

#include "Menu_Option.h"
#include <MLV/MLV_all.h>

/* Dessine menu de depart*/
void menu_depart(Menu_option menu, int nb_x, int nb_y);

/* Parcours tous les cases et les redessinant. Si la souris survole une des cases.
 * On dessine cette case d'une autre couleur de fond et on affecte à `veri` le numero de cases.
 * Les cases sont dans l'ordre croissant du haut vers bas commence à 1, de plus on retourne 1.
 * Sinon on retourne 0.*/
int verification_position_souris(Menu_option menu, MLV_Color couleur, int x, int y, int nb_x, int nb_y, int *veri);


#endif