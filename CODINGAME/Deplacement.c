#include <stdio.h>
#include <stdlib.h>
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
