#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Deplacement.h"

void afficher_deplacement(Deplacement dep) {
    switch(dep) {
        case ROTATION : printf("ROTATION "); break;

        case NORD : printf("NORD "); break;

        case SUD : printf("SUD "); break;

        case EST : printf("EST "); break;

        case OUEST : printf("OUEST "); break;

        case STOP : printf("STOP "); break;
        
        default: printf("Erreur "); break;
    }
}


int action_deplacement(const Deplacement *dep, int *dep_x, int *dep_y) {
	int var = 1;
	assert(NULL != dep_x);
	assert(NULL != dep_y);
	assert(NULL != dep);

	switch(*dep) {
		case ROTATION : var = 2; break;

        case NORD : *dep_y = 1; break;

        case SUD : *dep_y = -1; break;

        case EST : *dep_x = 1; break;

        case OUEST : *dep_x = -1; break;

        case STOP : var = 3; break;
        
        default: var = 0; break;
	}
	return var;
}