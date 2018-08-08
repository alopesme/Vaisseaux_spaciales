#ifndef __JEU__
#define __JEU__
/*
Espace commentaire : pas fini la partie tir encore des bugs
*/

void action_element(Monde *mo, const int x, const int y, const int larg);


/* Phase de jeu. */
void jouer(int taille_x, int taille_y);

/* Le jeu avec le menu à ajouter etc.*/
void jeu(int taille_x, int taille_y);

#endif