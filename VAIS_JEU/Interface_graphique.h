#ifndef __INTERFACE_GRAPHIQUE__
#define __INTERFACE_GRAPHIQUE__

#include "Vaisseaux.h"

/*
Espace commentaire : Rien
*/

#define LARGEUR_VAISSEAU 0.07
#define HAUTEUR_VAISSEAU 0.15

#define FOND MLV_rgba(0, 4, 40, 255)

/* Affiche le background du jeu. */
void afficher_background();

/* Affiche le vaisseau à l'écran dont le point (x, y) correspond au centre du vaisseau. */
void afficher_vaisseau(int largeur_fenetre, int hauteur_fenetre, int x, int y);

#endif