#ifndef __IA__
#define __IA__

#include "Monde.h"

#define PROBA_BOT 25 /* Probabilité de faire apparaitre un bot à chaque seconde. */
#define PROBA_DEPLACEMENT_BOT 2 /* Probabilité qu'un bot change de direction chaque seconde. */

/* Ajoute aléatoirement un vaisseau dans le monde. */
int ajouter_vaisseau_ennemi(Monde* monde, const int larg, const int vie, const Etats type);

/* Change aléatoirement la direction d'un vaisseau. */
void changer_direction_aleatoirement(Monde* monde, int i_vaisseau);

#endif