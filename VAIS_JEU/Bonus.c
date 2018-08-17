#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_time.h>
#include <MLV/MLV_random.h>
#include "Bonus.h"
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"


void ajouter_bonus_aleatoire(Monde* monde) {
    Element elem;
    int proba, x, y;

    assert(NULL != monde);

    proba = PROBA_BONUS; /* Pourcentage de chance qu'un bonus apparaisse. */

    if ( proba > MLV_get_random_integer(0, 100) ) {
        elem.etats = MLV_get_random_integer(BONUS1, BONUS3);
        elem.vie = MLV_get_time();

        do {
            x = MLV_get_random_integer(0, monde->taille_x);
            y = MLV_get_random_integer(0, monde->taille_y);
        } while ( monde->tab[y][x].etats != VIDE );

        monde->tab[y][x] = elem;
    }
}

int doit_detruire_bonus(Element bonus) {
	return (MLV_get_time() - bonus.vie) / 1000 > DUREE_BONUS;
}