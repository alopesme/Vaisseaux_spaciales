#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "Jeu.h"
#include "Vaisseaux.h"
#include "Monde.h"

void deplacement_joueur(Monde* monde) {
	int deplacer;

	assert(NULL != monde);

	deplacer = 0;

	/* Si le joueur appuis sur Z-Q-S-D on modifie la direction et on indique qu'on fera bouger le vaisseau s'il reste dans les limites. */
	if ( MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED ) {
		monde->vaisseaux[0].dep = NORD;
		deplacer = peux_se_deplacer(&(monde->vaisseaux[0]), monde->largeur_fenetre, monde->hauteur_fenetre);
	} else if ( MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED ) {
		monde->vaisseaux[0].dep = EST;
		deplacer = peux_se_deplacer(&(monde->vaisseaux[0]), monde->largeur_fenetre, monde->hauteur_fenetre);
	} else if ( MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED ) {
		monde->vaisseaux[0].dep = SUD;
		deplacer = peux_se_deplacer(&(monde->vaisseaux[0]), monde->largeur_fenetre, monde->hauteur_fenetre);
	} else if ( MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED ) {
		monde->vaisseaux[0].dep = OUEST;
		deplacer = peux_se_deplacer(&(monde->vaisseaux[0]), monde->largeur_fenetre, monde->hauteur_fenetre);
	}

	/* On déplace le vaisseau si c'est indiqué. */
	if ( deplacer )
		deplacer_vaisseau(&(monde->vaisseaux[0]));
}