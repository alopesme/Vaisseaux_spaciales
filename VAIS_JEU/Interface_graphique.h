/* Auteurs: LOPES MENDES Ailton
*  Creation: 30/06/2018
*  Modification: 14/07/2018*/


#ifndef __INTERFACE_GRAPHIQUE__
#define __INTERFACE_GRAPHIQUE__

#include "Monde.h"
#include <MLV/MLV_all.h>

/*
Espace commentaire : Utilise les fontions d'Images directement
*/

/* Affiche le background du jeu. */
void afficher_background();

/* Déssine l'élément dont le centre est situé aux coordonnées (x, y). */
void dessiner_element(Monde* monde, MLV_Image** image, int x, int y, const int larg);

void effets_speciaux(MLV_Sound** son, const char* nom_son);

#endif