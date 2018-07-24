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
#include "Bonus.h"
#include "Ia.h"

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
		
			if(validation_tir(&(mo->tab[y][x].tir.coord_t), larg / 2, larg / 2, mo->taille_x * larg - larg / 2, mo->taille_y * larg - larg / 2)) {
				if (configure_tir_monde(mo, mo->tab[y][x].tir, TIR, larg)) {
					mo->tab[y][x].etats = VIDE;
					mo->tab[y][x].vie = VIDE;
				}
			}
			else {
				mo->tab[y][x].etats = VIDE;
				mo->tab[y][x].vie = VIDE;
			}
			break;
			
		default: break;
	}
}

static void vaisseaux_monde(Monde *mo, const int x, const int y, const int larg) {
	int i_vaisseau;

	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);

	i_vaisseau = mo->tab[y][x].indice;

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
			break;
		case BOT:
		case MIBOSS:
		case BOSSFINALE:
			changer_direction_aleatoirement(mo, i_vaisseau);
			break;
		default: return;
	}

	if ( mo->vaisseaux[i_vaisseau].dep != STOP ) {
		if (peut_se_deplacer(mo, x, y, i_vaisseau, larg)) {
			deplacer_vaisseau(mo, x, y, larg);
		}
	}

	mo->vaisseaux[0].dep = STOP;
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
		case BONUS2:
		case BONUS3:
			if ( doit_detruire_bonus(mo->tab[y][x]) )
				mo->tab[y][x].etats = VIDE;
			break;

		default: break;
	}
}

void action_element(Monde *mo, const int x, const int y, const int larg) {
	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);

	if (mo->tab[y][x].etats <= OBSTACLE)
		matiere_monde(mo, x, y);

	if (mo->tab[y][x].etats > OBSTACLE && mo->tab[y][x].etats <= TIR) 
		tir_monde(mo, x, y, larg);
				
	if (mo->tab[y][x].etats > TIR && mo->tab[y][x].etats <= BOSSFINALE) 
		vaisseaux_monde(mo, x, y, larg);

	if (mo->tab[y][x].etats > BOSSFINALE)
		bonus_monde(mo, x, y);
}

void jouer(int taille_x, int taille_y) {
	Monde monde;
	int x, y, tir_x, tir_y, larg = 30;
	int debut, temps1, temps2;

	assert(taille_x > 0);
	assert(taille_y > 0);

	initialiser_monde(&monde, taille_x / larg, taille_y / larg, larg);

	debut = MLV_get_time() / 1000;
	temps1 = debut;

	while(MLV_get_mouse_button_state( MLV_BUTTON_RIGHT ) != MLV_PRESSED)  {
		afficher_background();

		if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED) {
			MLV_get_mouse_position(&tir_x, &tir_y);
			ajouter_tir_monde(&monde, tir_x, tir_y, larg, 0);
		}

		/* On tente d'ajouter un bonus et un bot toutes les secondes. */
		temps2 = MLV_get_time() / 1000;
		if ( temps2 != temps1 ) {
			temps1 = temps2;
			ajouter_bonus_aleatoire(&monde);
			ajouter_vaisseau_bot(&monde, larg);
		}

		for (y = 0; y < monde.taille_y; ++y) {
			for (x = 0; x < monde.taille_x; ++x) {
				dessiner_element(&monde, x, y, larg);
				action_element(&monde, x, y, larg);
			}
			
		}

		MLV_actualise_window();
	}

	libere_monde(&monde);
}