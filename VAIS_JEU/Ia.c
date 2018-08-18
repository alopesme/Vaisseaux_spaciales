#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_random.h>
#include "Ia.h"
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"

static int position_element(Monde* monde, int *x, int *y, int proba) {
	assert(NULL != monde);

	if ( proba < MLV_get_random_integer(0, 100) )
		return 0;

	do {
		if ( MLV_get_random_boolean() ) { /* Bords supérieur et inférieur. */
			*x = MLV_get_random_integer(0, monde->taille_x);
			if ( MLV_get_random_boolean() ) /* Bord supérieur. */
				*y = 0;
			else /* Bord inférieur. */
				*y = monde->taille_y - 1;
		} else { /* Bords gauche et droit. */
			*y = MLV_get_random_integer(0, monde->taille_y);
			if ( MLV_get_random_boolean() ) /* Bord gauche. */
				*x = 0;
			else /* Bord droit. */
				*x = monde->taille_x - 1;
		}
	} while ( monde->tab[*y][*x].etats != VIDE );
	return 1;
}

int ajouter_obstacle(Monde* monde, const int vie, const Etats type) {
	int x1, y1, x2, y2;
	Tir tir;
	assert(NULL != monde);
	if (!position_element(monde, &x1, &y1, PROBA_OBSTACLE))
		return 0;

	if (!position_element(monde, &x2, &y2, 100))
		return 0;
	x1 = x1 * monde->larg + monde->larg / 2; y1 = y1 * monde->haut + monde->haut / 2;
	x2 = x2 * monde->larg + monde->larg / 2; y2 = y2 * monde->haut + monde->haut / 2;
    tir = init_tirs(x1, y1, x2, y2);
    configure_tir_obstacle_monde(monde, tir, type);
    return 1;
}

int ajouter_vaisseau_ennemi(Monde* monde, const int vie, const Etats type) {
	int x, y;
	assert(vie > 0);
	assert(NULL != monde);

	if (!position_element(monde, &x, &y, PROBA_BOT))
		return 0;

	ajouter_vaisseau_monde(monde, x, y, vie * type, type);
	return 1;
}

void changer_direction_aleatoirement(Monde* monde, int i_vaisseau) {
	assert(NULL != monde);
	assert(i_vaisseau >= 0);

	if ( PROBA_DEPLACEMENT_BOT < MLV_get_random_integer(0, 100) )
		return;

	monde->vaisseaux[i_vaisseau].dep = MLV_get_random_integer(NORD, OUEST + 1);
}