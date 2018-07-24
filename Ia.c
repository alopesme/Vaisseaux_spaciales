#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_random.h>
#include "Ia.h"
#include "Monde.h"

void ajouter_vaisseau_bot(Monde* monde, int larg) {
	int x, y;

	assert(NULL != monde);

	if ( PROBA_BOT < MLV_get_random_integer(0, 100) )
		return;

	do {
		if ( MLV_get_random_boolean() ) { /* Bords supérieur et inférieur. */
			x = MLV_get_random_integer(0, monde->taille_x - 1);
			if ( MLV_get_random_boolean() ) /* Bord supérieur. */
				y = 0;
			else /* Bord inférieur. */
				y = monde->taille_y - 1;
		} else { /* Bords gauche et droit. */
			y = MLV_get_random_integer(0, monde->taille_y - 1);
			if ( MLV_get_random_boolean() ) /* Bord gauche. */
				x = 0;
			else /* Bord droit. */
				x = monde->taille_x - 1;
		}
	} while ( monde->tab[y][x].etats != VIDE );

	ajouter_vaisseau_monde(monde, x, y, 50, larg, BOT);
}