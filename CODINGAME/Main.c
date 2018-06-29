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
#include "Jeu.h"
#include <MLV/MLV_all.h>

#define TICK 10

int main(int argc, char const *argv[]) {
	Monde monde;

	initialiser_monde(&monde);

	MLV_create_window("Wesh zoulette", "Bien ou quoi", monde.largeur_fenetre, monde.hauteur_fenetre);

	do {
		afficher_background();
		afficher_vaisseaux(&monde);
		MLV_actualise_window();

		deplacement_joueur(&monde);

		MLV_wait_milliseconds(TICK);

	} while ( 1 );

	MLV_free_window();

	return 0;
}