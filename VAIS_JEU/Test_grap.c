#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Images.h"
#include "Interface_graphique.h"
#include "Test_grap.h"
#include "Jeu.h"


void test_affichage_image(const int l_fen, const int h_fen, const char* nom_im) {
	MLV_Image* image = 	NULL;
	assert(l_fen > 0);
	assert(h_fen > 0);

	MLV_create_window("affichage_image", "affichage_image", l_fen, h_fen);
	dessiner_image(&image, nom_im, l_fen / 2, h_fen / 2, 0);
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
		dessiner_vaisseau(&image, nom_im, l_fen / 2, h_fen / 2, h_fen / 15);
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
			dessiner_image(&im, nom_im ,(int)(tir.coord_t.tir_x), (int)(tir.coord_t.tir_y), larg);
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

	initialiser_monde(&monde, l_fen, h_fen, 20);

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
					dessiner_image(&im, "../Images/v_joueur.png", x, y, 0);
					if ( monde.vaisseaux[0].dep != STOP ) {
						if (peut_se_deplacer(&monde, x, y, monde.tab[y][x].indice, 20) ) {
							deplacer_vaisseau(&monde, x, y, 20);
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


void test_monde(const int l_fen, const int h_fen, const int larg) {
	Monde monde;
	int a_bouge, x, y, tir_x, tir_y;
	assert(l_fen > 0);
	assert(h_fen > 0);
	initialiser_monde(&monde, l_fen / larg, h_fen / larg, larg);
	MLV_create_window("Vaisseaux spatiales", "Vaisseaux spatiales", l_fen, h_fen);
	while(MLV_get_mouse_button_state( MLV_BUTTON_RIGHT ) != MLV_PRESSED)  {
		a_bouge = 0;
		afficher_background();
		if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED) {
			MLV_get_mouse_position(&tir_x, &tir_y);
			ajouter_tir_monde(&monde, tir_x, tir_y, larg, 0);
		}

		for (y = 0; y < monde.taille_y; ++y) {
			for (x = 0; x < monde.taille_x; ++x) {
				dessiner_element(&monde, x, y, larg);
				action_element(&monde, x, y, larg, &a_bouge);
			}
			
		}
		MLV_actualise_window();
	}
	libere_monde(&monde);
	MLV_free_window();


}