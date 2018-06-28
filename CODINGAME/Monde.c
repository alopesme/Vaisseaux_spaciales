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

void ajouter_vaisseau_monde(Monde* monde) {
	Vaisseau bot_defaut = {nb_vaisseaux, nb_vaisseaux, BOT, STOP, LENT, RIEN};

	assert(NULL != monde);

	/* Si on a atteint la capacité maximum de vaisseau, on la double. */
	if ( monde->nb_vaisseaux >= monde->nb_vaisseaux_max ) {
		monde->nb_vaisseaux_max *= 2;
		monde->vaisseaux = (Vaisseau*)realloc(monde->vaisseaux, sizeof(Vaisseau) * monde->nb_vaisseaux_max);
		if ( NULL == monde->vaisseaux )
			exit(EXIT_FAILURE);
	}

	monde->vaisseaux[monde->nb_vaisseaux] = bot_defaut;
	monde->nb_vaisseaux += 1;
}

void ajouter_bonus_monde(Monde* monde, Bonus bonus) {
	assert(NULL != monde);

	/* Si on a atteint la capacité maximum de bonus, on la double. */
	if ( monde->nb_bonus >= monde->nb_bonus_max ) {
		monde->nb_bonus_max *= 2;
		monde->bonus = (Bonus*)realloc(monde->bonus, sizeof(Bonus) * monde->nb_bonus_max);
		if ( NULL == monde->bonus )
			exit(EXIT_FAILURE);
	}

	monde->bonus[monde->nb_bonus] = bonus;
	monde->nb_bonus += 1;
}