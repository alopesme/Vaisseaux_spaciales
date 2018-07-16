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


void test_affichage_image(const int l_fen, const int h_fen, const char* nom_im) {
	MLV_Image* image = 	NULL;
	assert(l_fen > 0);
	assert(h_fen > 0);

	MLV_create_window("affichage_image", "affichage_image", l_fen, h_fen);
	charger_image(&image, nom_im, l_fen, h_fen, l_fen / 20);
	dessiner_image(image, l_fen / 2, h_fen / 2, 0);
	MLV_actualise_window();

	MLV_wait_mouse(NULL, NULL);
	liberer_image(&image);

	MLV_free_window();
}

void test_rotation_image(const int l_fen, const int h_fen, const char* nom_im) {
	MLV_Image* image = 	NULL;
	assert(l_fen > 0);
	assert(h_fen > 0);
	
	MLV_create_window("rotation_image", "rotation_image", l_fen, h_fen);
	while (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) != MLV_PRESSED) {
		afficher_background();
		dessiner_vaisseau(&image, nom_im, l_fen, h_fen, l_fen / 2, h_fen / 2, h_fen / 15);
		MLV_actualise_window();
	}

	MLV_wait_mouse(NULL, NULL);
	liberer_image(&image);
	MLV_free_window();	
}

void test_un_tir_image(const int l_fen, const int h_fen, const char* nom_im) {
	int x, y;
	Tir tir;
	MLV_Image* im;
	assert(l_fen > 0);
	assert(h_fen > 0);
	assert(NULL != nom_im);

	tir = init_tirs(l_fen / 2, h_fen / 2, l_fen / 2, h_fen / 2);
	MLV_create_window("tir_image", "tir_image", l_fen, h_fen);


	MLV_wait_mouse(&x, &y);
	charger_image(&im, nom_im, l_fen, h_fen, h_fen / 8);
	while ((tir.coord_t.tir_x < l_fen && tir.coord_t.tir_x >= 0) && (tir.coord_t.tir_y < l_fen && tir.coord_t.tir_y >= 0)) {
		afficher_background();
		dessiner_image(im, (int)(tir.coord_t.tir_x), (int)(tir.coord_t.tir_y), h_fen / 8);
		calculer_tir(&(tir.coord_t), x, y);
		MLV_actualise_window();
	}

	MLV_wait_mouse(NULL, NULL);
	liberer_image(&im);
	MLV_free_window();
}

