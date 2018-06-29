#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Bonus.h"
#include "Monde.h"

void initialiser_monde(Monde* monde) {
	assert(NULL != monde);
	assert(BLOC_VAISSEAUX > NB_BOTS_DEBUT);

	/* Allocation du tableau de vaisseaux. */
	monde->vaisseaux = allouer_vaisseaux(BLOC_VAISSEAUX);
	monde->nb_vaisseaux_max = BLOC_VAISSEAUX;
	monde->nb_vaisseaux = 1 + NB_BOTS_DEBUT;

	/* Allocation du tableau de bonus. */
	monde->bonus = allouer_bonus(BLOC_BONUS);
	monde->nb_bonus_max = BLOC_BONUS;
	monde->nb_bonus = 0;

	/* Définition des dimensions de la fenêtre. */
	monde->largeur_fenetre = LARGEUR_FENETRE_INI;
	monde->hauteur_fenetre = HAUTEUR_FENETRE_INI;
}

void afficher_monde_details(Monde monde) {
	printf("Adresse du tableau de vaisseau : %p\n", monde.vaisseaux);
	printf("Nombre de vaisseaux : %d\n", monde.nb_vaisseaux);
	printf("Capacité max de vaisseaux : %d\n", monde.nb_vaisseaux_max);
	printf("----------------\n");
	printf("Adresse du tableau de bonus : %p\n", monde.bonus);
	printf("Nombre de bonus : %d\n", monde.nb_bonus);
	printf("Capacité max de bonus : %d\n", monde.nb_bonus_max);
}

void ajouter_vaisseau_monde(Monde* monde, Vaisseau vaisseau) {
	assert(NULL != monde);

	/* Si on a atteint la capacité maximum de vaisseau, on la double. */
	if ( monde->nb_vaisseaux >= monde->nb_vaisseaux_max ) {
		monde->nb_vaisseaux_max *= 2;
		monde->vaisseaux = (Vaisseau*)realloc(monde->vaisseaux, sizeof(Vaisseau) * monde->nb_vaisseaux_max);
		if ( NULL == monde->vaisseaux )
			exit(EXIT_FAILURE);
	}

	monde->vaisseaux[monde->nb_vaisseaux] = vaisseau;
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