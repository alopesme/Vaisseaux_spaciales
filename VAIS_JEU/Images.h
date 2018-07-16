/* Auteurs: LOPES MENDES Ailton
*  Creation: 15/07/2018
*  Modification: 15/07/2018*/

#ifndef __IMAGES__
#define __IMAGES__

#include <MLV/MLV_all.h>

#define PI 3.14159265

/*
Espace commentaire : Ficher sere a gere images fonction `rotation_vaisseau` pas fini.
*/




/* Cette fois permet de charger l'image et la redimisionner.*/
void charger_image(MLV_Image** image, const char* nom_image, const int l_fen, const int h_fen, const int largeur);

/* Cette fonction dessine l'image.*/
void dessiner_image(MLV_Image* image, const int x, const int y, const int largeur);

/* Fonction qui va dessiner un vaisseau avec la rotation aussi.*/
void dessiner_vaisseau(MLV_Image** image, const char* nom_image, const int l_fen, const int h_fen, const int x, const int y, const int largeur);

/* Tourne l'image par rapport à la position de la souris.*/
void rotation_vaisseau(MLV_Image** image, const int x, const int y, const int largeur);

/*Libere image.*/
void liberer_image(MLV_Image** image);

#endif