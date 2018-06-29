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