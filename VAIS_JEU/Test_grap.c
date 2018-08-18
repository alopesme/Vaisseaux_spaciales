#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include "Bonus.h"
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
#include "Music_Sons.h"
#include "Test_grap.h"
#include "Ia.h"
#include "Jeu.h"


void test_affichage_image(const int l_fen, const int h_fen, const char* nom_im) {
	MLV_Image* image = 	NULL;
	assert(l_fen > 0);
	assert(h_fen > 0);

	MLV_create_window("affichage_image", "affichage_image", l_fen, h_fen);
	dessiner_image(&image, nom_im, l_fen / 2, h_fen / 2, 0, 0);
	MLV_actualise_window();

	MLV_wait_mouse(NULL, NULL);

	MLV_free_window();
}

void test_rotation_image(const int l_fen, const int h_fen, const char* nom_im) {
	MLV_Image* image = 	NULL;
	assert(l_fen > 0);
	assert(h_fen > 0);
	
	MLV_create_window("rotation_image", "rotation_image", l_fen, h_fen);
	while (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) != MLV_PRESSED) {
		afficher_background();
		dessiner_vaisseau(&image, nom_im, l_fen / 2, h_fen / 2, l_fen / 15, h_fen / 15);
		MLV_actualise_window();
	}

	MLV_wait_mouse(NULL, NULL);
	liberer_image(&image);
	MLV_free_window();	
}

void test_un_tir_image(const int l_fen, const int h_fen, const int larg, const char* nom_im) {
	int x, y;
	Tir tir;
	MLV_Image* im;
	assert(l_fen > 0);
	assert(h_fen > 0);
	assert(NULL != nom_im);

	MLV_create_window("tir_image", "tir_image", l_fen, h_fen);


	MLV_wait_mouse(&x, &y);
	tir = init_tirs(l_fen / 2, h_fen / 2, x, y);
	while (MLV_get_mouse_button_state( MLV_BUTTON_RIGHT ) != MLV_PRESSED) {
		if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED) {
			MLV_get_mouse_position(&x, &y);
			tir = init_tirs(l_fen / 2, h_fen / 2, x, y);
		}

		if ((tir.coord_t.tir_x < l_fen && tir.coord_t.tir_x >= larg / 2) && (tir.coord_t.tir_y < l_fen && tir.coord_t.tir_y >= larg / 2)) {
			afficher_background();
			dessiner_image(&im, nom_im ,(int)(tir.coord_t.tir_x), (int)(tir.coord_t.tir_y), larg, larg);
			calculer_tir(&(tir.coord_t), 1);
			MLV_actualise_window();
		}
	}

	MLV_wait_mouse(NULL, NULL);
	MLV_free_window();
}

void test_deplacement_vaisseau(const int l_fen, const int h_fen) {
	MLV_Image* im;
	Monde monde;
	int x, y;

	assert(l_fen > 0);
	assert(h_fen > 0);

	initialiser_monde(&monde, l_fen, h_fen, 20, 20);

	MLV_create_window("Déplacement vaisseau", "Déplacement vaisseau", l_fen, h_fen);

	while ( 1 ) {
		afficher_background();

		if ( MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED )
			monde.vaisseaux[0].dep = NORD;
		if ( MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED )
			monde.vaisseaux[0].dep = OUEST;
		if ( MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED )
			monde.vaisseaux[0].dep = SUD;
		if ( MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED )
			monde.vaisseaux[0].dep = EST;

		for (y = 0; y < monde.taille_y; y++) {
			for (x = 0; x < monde.taille_x; x++) {
				if ( monde.tab[y][x].etats == JOUEUR ) {
					dessiner_image(&im, "../Images/v_joueur.png", x, y, 0, 0);
					if ( monde.vaisseaux[0].dep != STOP ) {
						if (peut_se_deplacer(&monde, x, y, monde.tab[y][x].indice) ) {
							deplacer_vaisseau(&monde, x, y);
							monde.vaisseaux[0].dep = STOP;
						}
					}
				}
			}
		}

		MLV_actualise_window();
	}
	libere_monde(&monde);
	liberer_image(&im);
	MLV_free_window();
}


void test_monde(const int l_fen, const int h_fen, const int larg, const int nb_vaisseaux) {
	Monde monde;
	MLV_Sound* son = NULL;
	MLV_Image* images[BONUS3 + 1] = {NULL};
	int x, y, tir_x, tir_y, debut, temps1, temps2, nb = 0;
	assert(l_fen > 0);
	assert(h_fen > 0);
	initialiser_monde(&monde, l_fen / larg, h_fen / larg, larg, larg);
	ajouter_mur_monde(&monde, 1, 1, 1, MUR);
	debut = MLV_get_time() / 1000;
	temps1 = debut;

	while(MLV_get_mouse_button_state( MLV_BUTTON_RIGHT ) != MLV_PRESSED)  {
		afficher_background();
		if( MLV_get_keyboard_state( MLV_KEYBOARD_k ) == MLV_PRESSED ) {
			afficher_monde(monde);
			while(MLV_get_keyboard_state( MLV_KEYBOARD_k ) != MLV_RELEASED );
		}
		
		if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED) {
			MLV_get_mouse_position(&tir_x, &tir_y);
			ajouter_tir_monde(&monde, tir_x, tir_y, 0);
		}

		temps2 = MLV_get_time() / 1000;
		if ( temps2 != temps1 && nb < nb_vaisseaux) {
			temps1 = temps2;
			ajouter_bonus_aleatoire(&monde);
			ajouter_obstacle(&monde, 1, OBSTACLE);
			nb += ajouter_vaisseau_ennemi(&monde, 1, BOT);
		}

		for (y = 0; y < monde.taille_y; ++y) {
			for (x = 0; x < monde.taille_x; ++x) {
				dessiner_element(&monde, &son, &(images[monde.tab[y][x].etats]), x, y);

				action_element(&monde, x, y);
				MLV_draw_rectangle(x * larg, y * larg, larg, larg, MLV_COLOR_RED);
			}
			
		}
		MLV_actualise_window();
	}
	for (x = 0; x < BONUS3 + 1; ++x) {
		if (NULL != images[x])
			liberer_image(&(images[x]));
	}
	MLV_free_sound(son);

	libere_monde(&monde);

}

void test_jeu(const int l_fen, const int h_fen, const int larg, const int n_v) {
	int veri;
	MLV_Music* musique;
	MLV_create_window("Vaisseaux spatiales", "Vaisseaux spatiales", l_fen, h_fen);
	MLV_init_audio( );
	init_music(&musique, "../SONS_MUSIC/you-say-run-the-real-orchestral-my-hero-academia-deku.ogg");
	veri = cliquer_sur_menu_depart(l_fen, h_fen);
	if (veri == 1)
		test_monde(l_fen, h_fen, larg, n_v);
	libere_musique(&musique);
	MLV_free_window();
}