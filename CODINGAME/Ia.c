#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <MLV/MLV_random.h>
#include "Ia.h"
#include "Monde.h"
#include "Vaisseaux.h"

void ajouter_vaisseau_ennemi(Monde* monde, Type_vaisseau type) {
	Vaisseau vaisseau;

	assert(NULL != monde);
	assert(type != JOUEUR);

	switch ( type ) {
		case BOT:
			vaisseau.vi = LENT;
			vaisseau.tir = RIEN;
			vaisseau.vie = 25;
			break;
		case MIBOSS:
			vaisseau.vi = MOYEN;
			vaisseau.tir = DOUBLE;
			vaisseau.vie = 100;
			break;
		case BOSSFINALE:
			vaisseau.vi = RAPIDE;
			vaisseau.tir = TRIPLE;
			vaisseau.vie = 300;
			break;
		default:
			printf("ERREUR -- Ajout d'un vaisseau autre que BOT, MIBOSS, BOSSFINALE.\n");
			return;
	}

	vaisseau.type = type;
	vaisseau.dep = STOP;

	/* Ici on détermine le point d'apparition du bot (sur les bords). */

	if ( MLV_get_random_boolean() ) { /* Bords supérieur et inférieur. */
		vaisseau.x = MLV_get_random_integer(0, monde->largeur_fenetre);
		if ( MLV_get_random_boolean() ) /* Bord supérieur. */
			vaisseau.y = 0;
		else /* Bord inférieur. */
			vaisseau.y = monde->hauteur_fenetre;
	} else { /* Bords gauche et droit. */
		vaisseau.y = MLV_get_random_integer(0, monde->hauteur_fenetre);
		if ( MLV_get_random_boolean() ) /* Bord gauche. */
			vaisseau.x = 0;
		else /* Bord droit. */
			vaisseau.x = monde->largeur_fenetre;
	}

	ajouter_vaisseau_monde(monde, vaisseau);
}