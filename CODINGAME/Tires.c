#include <stdio.h>
#include <stdlib.h>
#include "Tires.h"

void afficher_tires(Tires t) {
	switch(t) {
		case SIMPLE : printf("SIMPLE "); break;

		case DOUBLE : printf("DOUBLE "); break;

		case TRIPLE : printf("TRIPLE "); break;

		case CANON : printf("CANON "); break;

		case RIEN : printf("RIEN "); break;
		
		default : printf("Erreur "); break;
	}
}