#include <stdio.h>
#include <stdlib.h>
#include "Vitesse.h"

void afficher_vitesse(Vitesse vi) {
	switch(vi) {
		case RALENTI_TEMPS : printf("RALENTI_TEMPS "); break;

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

	switch (*vi) {
		case RALENTI_TEMPS : var = 2; break;

		case LENT : *mut *= LENT; break;

		case MOYEN : *mut *= MOYEN; break;

		case RAPIDE : *mut *= RAPIDE; break;

		default : var = 0; break;
	}

	return var;
}