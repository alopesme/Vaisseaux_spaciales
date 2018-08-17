#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Test.h"

int test_allouer_vaisseaux(const int nb_vaisseaux) {
	Vaisseau* vaisseaux = NULL;

	assert(nb_vaisseaux > 0);

	vaisseaux = allouer_vaisseaux(nb_vaisseaux, 0, 0, 0, 0);
	afficher_vaisseaux_details(vaisseaux, nb_vaisseaux);
	libere_vaisseaux(vaisseaux);

	return 1;
}

int test_tirs(const int x, const int y) {
	Tir tir;
	assert(x >= 0);
	assert(y >= 0);

	tir = init_tirs(x, y, x + 10, y + 10);
	afficher_tir(tir);
	return 1;
}

int test_monde_vide(const int t_x, const int t_y) {
	Monde mo;
	int i, j;
	initialiser_monde(&mo, t_x, t_y, 0, 0);

	printf("%d et %d\n", mo.taille_x, mo.taille_y);
	for (i = 0; i < t_x; ++i) {
		for (j = 0; j < t_y; ++j) {
			if (mo.tab[i][j].etats == VIDE) 
				printf("[etat : %d vie : %d] ", mo.tab[i][j].etats, mo.tab[i][j].vie);
		}
		printf("\n");
	}

	libere_monde(&mo);
	return 1;
}

int test_monde_tir(const int t_x, const int t_y, const int x_f, const int y_f) {
	Monde mo;
	Tir tir;
	int i, j, var = 1;
	initialiser_monde(&mo, t_x + 1, t_y + 1, 20, 20);

	tir = init_tirs(t_x / 2, t_y, x_f, y_f);
	configure_tir_monde(&mo, tir, TIR);
	printf("\n\n\n\n\n\n\n");
	afficher_monde(mo);

	while (var) {
		for(i = 0; i < mo.taille_x; ++i) {
			for (j = 0; j < mo.taille_y; ++j) {
				if(mo.tab[i][j].etats == TIR) {
					var = validation_tir(&(mo.tab[i][j].tir.coord_t), 0, 0, mo.taille_x, mo.taille_y);
					configure_tir_monde(&mo, mo.tab[i][j].tir, TIR);
					afficher_tir(mo.tab[i][j].tir);
					mo.tab[i][j].etats = VIDE;
					mo.tab[i][j].vie = VIDE;
					afficher_monde(mo);
				}
			}
		}
	}
	
	return 1;
}