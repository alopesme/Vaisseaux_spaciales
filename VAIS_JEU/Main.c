#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Test.h"
#include "Interface_graphique.h"
#include <MLV/MLV_all.h>

int main(int argc, char const *argv[]) {
	/*int x, y, nbtirs = 0, i;
	Tirs *tirs, temp;
	Monde monde;

	initialiser_monde(&monde);

	tirs = init_tirs(SIMPLE, monde.largeur_fenetre / 2, monde.hauteur_fenetre * 0.8, 0, 0);
	MLV_create_window("Wesh zoulette", "Bien ou quoi", monde.largeur_fenetre, monde.hauteur_fenetre);

	while(1) {
		afficher_background();
		afficher_vaisseau(monde.vaisseaux[0], monde.largeur_fenetre, monde.hauteur_fenetre, monde.largeur_fenetre / 2, monde.hauteur_fenetre * 0.8);
		if(MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED) {
			MLV_get_mouse_position(&x, &y);
			tirs[nbtirs].coord_t.x_f = x;
			tirs[nbtirs].coord_t.y_f = y;
			++nbtirs;
			while(MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) != MLV_RELEASED);
			printf("%d\n", nbtirs);
		}

		for (i = 0; i < nbtirs; ++i) {
			calculer_tir(&(tirs[i].coord_t), tirs[i].coord_t.x_f, tirs[i].coord_t.y_f);
			MLV_draw_circle(tirs[i].coord_t.tir_x, tirs[i].coord_t.tir_y, 5,
				MLV_COLOR_RED);
			
		}
		MLV_actualise_window();
	}

	MLV_actualise_window();
	MLV_wait_mouse(NULL, NULL);

	MLV_free_window();
	*/
	test_monde(atoi(argv[1]), atoi(argv[2]));

	return 0;
}