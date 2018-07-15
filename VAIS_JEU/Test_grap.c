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
	charger_image(&image, nom_im, l_fen, h_fen);
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
	charger_image(&image, nom_im, l_fen, h_fen);
	afficher_background();
	MLV_wait_mouse(NULL, NULL);
	rotation_vaisseau(image, l_fen / 2, h_fen / 2);
	dessiner_image(image, l_fen / 2, h_fen / 2, 0);
	MLV_actualise_window();
	

	MLV_wait_mouse(NULL, NULL);
	liberer_image(&image);

	MLV_free_window();	

}
