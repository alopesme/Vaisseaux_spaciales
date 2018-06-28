#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Monde.h"

void initialiser_monde(Monde* monde) {
	assert(NULL != monde);
	assert(BLOC_VAISSEAUX > NB_BOTS_DEBUT);

	monde->vaisseaux = allouer_vaisseaux(BLOC_VAISSEAUX);
	monde->nb_vaisseaux = 1 + NB_BOTS_DEBUT;

	monde->bonus = (Bonus*)malloc(sizeof(Bonus) * BLOC_BONUS);
	if (monde->bonus == NULL) {
		printf("Malloc rate \t\tinitialiser_monde -> bonus\n");
		exit(EXIT_FAILURE);
	}

	monde->nb_bonus = 0;
}