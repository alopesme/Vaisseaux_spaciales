#include "Jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "Interface_graphique.h"
#include "Monde.h"

static void action_element(Monde* monde, int x, int y, int* a_bouge) {
	int i_vaisseau;

	assert(NULL != monde);
	assert(NULL != a_bouge);
	assert(x >= 0);
	assert(y >= 0);

	switch ( monde->tab[y][x].etats ) {
		case VIDE:
			break;
		/* Si c'est un mur ou un obstacle, on vérifie sa vie, et si elle est négative on le détruit. */
		case MUR:
		case OBSTACLE:
			if ( monde->tab[y][x].vie <= 0 )
				monde->tab[y][x].etats = VIDE;
			break;
		/* Si c'est un tir, ... */
		case TIR:
			break;
		/* Si c'est un vaisseau, on le déplace si nécessaire. */
		case JOUEUR:
			if ( MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED )
				monde->vaisseaux[0].dep = NORD;
			if ( MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED )
				monde->vaisseaux[0].dep = OUEST;
			if ( MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED )
				monde->vaisseaux[0].dep = SUD;
			if ( MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED )
				monde->vaisseaux[0].dep = EST;
		case BOT:
		case MIBOSS:
		case BOSSFINALE:
			i_vaisseau = monde->tab[y][x].indice;
			if ( monde->vaisseaux[i_vaisseau].dep != STOP ) {
				if ( peut_se_deplacer(monde, x, y, i_vaisseau) && !(*a_bouge) ) {
					deplacer_vaisseau(monde, x, y);
					monde->vaisseaux[i_vaisseau].dep = STOP;
					*a_bouge = 1;
				}
			}
			break;
		/* Si c'est un bonus. */
		case BONUS1:
			break;
		case BONUS2:
			break;
		case BONUS3:
			break;
	}
}

void jouer(int taille_x, int taille_y) {
	int x, y;
	int a_bouge;
	Monde monde;

	initialiser_monde(&monde, taille_x, taille_y);

	while ( 1 ) {

		afficher_background();
		a_bouge = 0;

		/* On parcours tous le tableau, et selon l'élément de la case, on effectue une action. */
		for (y = 0; y < monde.taille_y; y++) {
			for (x = 0; x < monde.taille_x; x++) {
				dessiner_element(&monde, x, y);
				action_element(&monde, x, y, &a_bouge);
			}
		}

		MLV_actualise_window();
	}
}