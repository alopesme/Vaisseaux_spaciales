/* Auteurs: LOPES MENDES Ailton
*  Creation: 30/06/2018
*  Modification: 14/07/2018*/


#ifndef __INTERFACE_GRAPHIQUE__
#define __INTERFACE_GRAPHIQUE__

#include "Monde.h"

/*
Espace commentaire : Utilise les fontions d'Images directement
*/

#define FOND /*MLV_rgba(0, 4, 40, 255)*/ MLV_COLOR_BLACK

/* Affiche le background du jeu. */
void afficher_background();

/* Déssine l'élément dont le centre est situé aux coordonnées (x, y). */
void dessiner_element(Monde* monde, int x, int y, const int larg);

void effets_speciaux(const char* nom_im, const char* nom_son, int x, int y, const int larg);

#endif