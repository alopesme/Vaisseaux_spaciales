/* Auteurs: LOPES MENDES Ailton
*  Creation: 26/06/2018
*  Modification: 14/07/2018*/
#ifndef __BONUS__
#define __BONUS__

#define DUREE_BONUS 3 /* Durée d'apparition d'un bonus en seconde. */

#include "Monde.h"

/*
Espace commentaire : 
*/

/* Ajoute un bonus aléatoire dans le monde en fonction d'un taux de probabilité. */
void ajouter_bonus_aleatoire(Monde* monde);

int doit_detruire_bonus(Element bonus);

#endif