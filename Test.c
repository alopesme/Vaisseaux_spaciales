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