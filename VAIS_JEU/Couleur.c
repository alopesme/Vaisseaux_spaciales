#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "Couleur.h"

void tester_couleur(MLV_Color tab[], int taille) {
    int i;
    for (i = 0; i < taille; ++i) {
        MLV_clear_window(tab[i]);
        MLV_wait_seconds(2);
        MLV_actualise_window();
    }
}