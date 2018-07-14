#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vitesse.h"

void afficher_vitesse(Vitesse vi) {
	switch(vi) {
		case TRES_LENT : printf("TRES_LENT "); break;

		case LENT : printf("LENT "); break;

		case MOYEN : printf("MOYEN "); break;

		case RAPIDE : printf("RAPIDE "); break;

		default : printf("Erreur "); break;

	}
}

int mutiple_vitesse(const Vitesse *vi, int *mut) {
	int var = 1;
	assert(NULL != vi);
	assert(NULL != mut);

	if (*vi == TRES_LENT)
		var = 2;
	else if (*vi > TRES_LENT && *vi <= RAPIDE)
		*mut = (*mut) * (*vi);

	return var;
}