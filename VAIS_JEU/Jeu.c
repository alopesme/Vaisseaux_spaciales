#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Interface_graphique.h"
#include "Jeu.h"

static void matiere_monde(Monde *mo, const int x, const int y) {
	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);

	switch (mo->tab[y][x].etats) {
		case VIDE:
			break;
		/* Si c'est un mur ou un obstacle, on vérifie sa vie, et si elle est négative on le détruit. */
		case MUR:
		case OBSTACLE:
			if (mo->tab[y][x].vie <= 0)
				mo->tab[y][x].etats = VIDE;
				break;
					/* Si c'est un tir, ... */
		default:
			break;
	}
}

static void tir_monde(Monde *mo, const int x, const int y, const int larg) {
	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);

	switch (mo->tab[y][x].etats) {
		case TIR: 
			mo->tab[y][x].etats = VIDE;
			mo->tab[y][x].vie = VIDE;
			if(validation_tir(&(mo->tab[y][x].tir.coord_t), larg / 2, larg / 2, mo->taille_x * larg - larg / 2, mo->taille_y * larg - larg / 2))
				configure_tir_monde(mo, mo->tab[y][x].tir, TIR, larg);
			break;
		default: break;
	}
}

static void vaisseaux_monde(Monde *mo, const int x, const int y, const int larg, int *a_bouge) {
	int i_vaisseau;
	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);
	switch (mo->tab[y][x].etats) {
		case JOUEUR:
			if ( MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED )
				mo->vaisseaux[0].dep = NORD;
			if ( MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED )
				mo->vaisseaux[0].dep = OUEST;
			if ( MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED )
				mo->vaisseaux[0].dep = SUD;
			if ( MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED )
				mo->vaisseaux[0].dep = EST;
		case BOT:
		case MIBOSS:
		case BOSSFINALE:
			i_vaisseau = mo->tab[y][x].indice;
			if ( mo->vaisseaux[i_vaisseau].dep != STOP ) {
				if (peut_se_deplacer(mo, x, y, i_vaisseau, larg) && !(*a_bouge) ) {
					deplacer_vaisseau(mo, x, y, larg);
					mo->vaisseaux[i_vaisseau].dep = STOP;
					*a_bouge = 1;
				}
			}
			break;
		default: break;
	}
}

static void bonus_monde(Monde *mo, const int x, const int y) {
	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);
	switch(mo->tab[y][x].etats) {
		/* Si c'est un bonus. */
		case BONUS1:
			break;
		case BONUS2:
			break;
		case BONUS3:
			break;

		default: break;
	}
}

void action_element(Monde *mo, const int x, const int y, const int larg, int *a_bouge) {
	assert(NULL != mo);
	assert(NULL != a_bouge);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);

	if (mo->tab[y][x].etats <= OBSTACLE)
		matiere_monde(mo, x, y);

	if (mo->tab[y][x].etats > OBSTACLE && mo->tab[y][x].etats <= TIR) 
		tir_monde(mo, x, y, larg);
				
	if (mo->tab[y][x].etats > TIR && mo->tab[y][x].etats <= BOSSFINALE) 
		vaisseaux_monde(mo, x, y, larg, a_bouge);

	if (mo->tab[y][x].etats > BOSSFINALE)
		bonus_monde(mo, x, y);
}

void jouer(int taille_x, int taille_y) {
	int x, y, larg = 20;
	Monde monde;
	int a_bouge;
	initialiser_monde(&monde, taille_x, taille_y, larg);
	while ( 1 ) {
		a_bouge = 0;
		afficher_background();
		/* On parcours tous le tableau, et selon l'élément de la case, on effectue une action. */
		for (y = 0; y < monde.taille_y; y++) {
			for (x = 0; x < monde.taille_x; x++) {
				dessiner_element(&monde, x, y, larg);
				action_element(&monde, x, y, larg, &a_bouge);
			}
		}
		MLV_actualise_window();
	}

}