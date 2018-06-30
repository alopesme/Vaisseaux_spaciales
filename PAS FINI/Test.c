#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Monde2.h"
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

	tirs = init_tirs(x, y, x + 10, y + 10);
	afficher_tirs(tirs);
	libere_tirs(tirs);
	return 1;
}

int test_monde2(const int t_x, const int t_y) {
	Monde2 mo;
	int i, j;
	initialiser_monde2(&mo, t_x, t_y);

	printf("%d et %d\n", mo.taille_x, mo.taille_y);
	for (i = 0; i < t_x; ++i) {
		for (j = 0; j < t_y; ++j) {
			if (mo.tab[i][j].etats == VIDE)
				printf("%d ", mo.tab[i][j].etats);
		}
		printf("\n");
	}

	libere_monde(&mo);

	return 1;

}