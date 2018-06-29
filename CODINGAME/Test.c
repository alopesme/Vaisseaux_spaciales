#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Vaisseaux.h"
#include "Test.h"

int test_allouer_vaisseaux(const int nb_vaisseaux) {
	Vaisseau* vaisseaux = NULL;

	assert(nb_vaisseaux > 0);

	vaisseaux = allouer_vaisseaux(nb_vaisseaux);
	afficher_vaisseaux_details(vaisseaux, nb_vaisseaux);
	libere_vaisseaux(vaisseaux, nb_vaisseaux);

	return 1;
}

int test_tirs(const int x, const int y) {
	Tirs *tirs;
	assert(x >= 0);
	assert(y >= 0);

	tirs = init_tirs(SIMPLE, x, y);
	afficher_tirs(tirs);
	libere_tirs(tirs);
	return 1;
}