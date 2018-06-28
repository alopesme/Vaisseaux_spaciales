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