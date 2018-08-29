#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "Menu_Option.h"
#include "Clic_Menu_Option.h"
#include "Couleur.h"
#include "Page_Accueil.h"
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Images.h"
#include "Interface_graphique.h"
#include "Jeu.h"
#include "Bonus.h"
#include "Music_Sons.h"
#include "Ia.h"

static void matiere_monde(Monde *mo, const int x, const int y) {
	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);

	switch (mo->tab[x][y].etats) {
		case VIDE:
			mo->tab[x][y].vie = 0;
			break;
		/* Si c'est une planete ou un obstacle, on vérifie sa vie, et si elle est négative on le détruit. */
		case PLANETE:
			configure_matiere_monde(mo, mo->tab[x][y].etats, x, y, mo->tab[x][y].vie, 5);
			break;
					/* Si c'est un tir, ... */
		default:
			break;
	}
}

static void tir_monde(Monde *mo, const int x, const int y) {
	int x1, x2, y1, y2, l;
	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);
	l = mo->tab[x][y].tir.coord_t.larg;
	tir_touche_element(mo, x, y);
			
	x1 = mo->larg / 2; x2 = mo->taille_x * mo->larg - (l / 2);
	y1 = mo->haut / 2; y2 = mo->taille_y * mo->haut - (l / 2);
			
	if(validation_tir(&(mo->tab[x][y].tir.coord_t), x1, y1, x2, y2)) {
		if (configure_tir_obstacle_monde(mo, mo->tab[x][y].tir, mo->tab[x][y].etats)) {
			mo->tab[x][y].etats = VIDE;
			mo->tab[x][y].vie = VIDE;
		}
	}
	else {
		mo->tab[x][y].etats = VIDE;
		mo->tab[x][y].vie = VIDE;
	}
			
}

static void vaisseaux_monde(Monde *mo, const int x, const int y) {
	int i_vaisseau;

	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);

	i_vaisseau = mo->tab[x][y].indice;

	switch (mo->tab[x][y].etats) {
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
		if (peut_se_deplacer(mo, x, y, i_vaisseau)) {
			deplacer_vaisseau(mo, x, y);
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
	switch(mo->tab[x][y].etats) {
		/* Si c'est un bonus. */
		case BONUS1:
		case BONUS2:
		case BONUS3:
			if ( doit_detruire_bonus(mo->tab[x][y]) )
				mo->tab[x][y].etats = VIDE;
			break;

		default: break;
	}
}

void action_element(Monde *mo, const int x, const int y) {
	assert(NULL != mo);
	assert(x >= 0);
	assert(x < mo->taille_x);
	assert(y >= 0);
	assert(y < mo->taille_y);

	if (mo->tab[x][y].etats <= PLANETE_CASSE)
		matiere_monde(mo, x, y);

	if (mo->tab[x][y].etats >= OBSTACLE && mo->tab[x][y].etats <= TIR) 
		tir_monde(mo, x, y);
				
	if (mo->tab[x][y].etats >= JOUEUR && mo->tab[x][y].etats <= BOSSFINALE) 
		vaisseaux_monde(mo, x, y);

	if (mo->tab[x][y].etats > BOSSFINALE)
		bonus_monde(mo, x, y);
}

void jouer(int taille_x, int taille_y) {
	Monde monde;
	MLV_Sound* son = NULL;
	MLV_Image* images[BONUS3 + 1] = {NULL}, *fond = NULL;
	int x, y, tir_x, tir_y, larg = 30, nb = 0;
	int debut, temps1, temps2;

	assert(taille_x > 0);
	assert(taille_y > 0);

	initialiser_monde(&monde, taille_x / larg, taille_y / larg, larg, larg);

	debut = MLV_get_time() / 1000;
	temps1 = debut;

	while(MLV_get_mouse_button_state( MLV_BUTTON_RIGHT ) != MLV_PRESSED)  {
		
		afficher_background(&monde, &fond);

		if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED) {
			MLV_get_mouse_position(&tir_x, &tir_y);
			ajouter_tir_monde(&monde, tir_x, tir_y, monde.larg, 0);
		}

		/* On tente d'ajouter un bonus et un bot toutes les secondes. */
		temps2 = MLV_get_time() / 1000;
		if ( temps2 != temps1 && nb < 10) {
			temps1 = temps2;
			ajouter_bonus_aleatoire(&monde);
			nb += ajouter_vaisseau_ennemi(&monde, 1, BOT);
		}

		for (y = 0; y < monde.taille_y; ++y) {
			for (x = 0; x < monde.taille_x; ++x) {
				dessiner_element(&monde, &son, &(images[monde.tab[x][y].etats]), x, y);
				action_element(&monde, x, y);
				MLV_draw_rectangle(x * larg, y * larg, larg, larg, MLV_COLOR_RED);

			}
			
		}

		MLV_actualise_window();
	}
	MLV_free_sound(son);

	for (x = 0; x < BONUS3 + 1; ++x) {
		if (NULL != images[x])
			liberer_image(&(images[x]));
	}
	libere_monde(&monde);
}

void jeu(int taille_x, int taille_y) {
	int veri;
	MLV_Music* musique;
	MLV_init_audio( );
	init_music(&musique, "../SONS_MUSIC/overlord-iii-official-opening.ogg");
	veri = cliquer_sur_menu_depart(taille_x, taille_y);
	if (veri == 1)
		jouer(taille_x, taille_y);
	libere_musique(&musique);
}