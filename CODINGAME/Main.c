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
#include "interface_graphique.h"
#include <MLV/MLV_all.h>

int main(int argc, char const *argv[]) {
	Monde monde;

	initialiser_monde(&monde);

	MLV_create_window("Wesh zoulette", "Bien ou quoi", monde.largeur_fenetre, monde.hauteur_fenetre);

	afficher_background();

	MLV_actualise_window();
	MLV_wait_mouse(NULL, NULL);

	MLV_free_window();

	return 0;
}
