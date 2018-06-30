#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Bonus.h"
#include "Monde.h"

void initialiser_monde(Monde* monde) {
	assert(NULL != monde);
	assert(BLOC_VAISSEAUX > NB_BOTS_DEBUT);

	/* Allocation du tableau de vaisseaux. */
	monde->vaisseaux = allouer_vaisseaux(BLOC_VAISSEAUX);
	monde->nb_vaisseaux_max = BLOC_VAISSEAUX;
	monde->nb_vaisseaux = 1 + NB_BOTS_DEBUT;

	/* Allocation du tableau de bonus. */
	monde->bonus = allouer_bonus(BLOC_BONUS);
	monde->nb_bonus_max = BLOC_BONUS;
	monde->nb_bonus = 0;

	/* Définition des dimensions de la fenêtre. */
	monde->largeur_fenetre = LARGEUR_FENETRE_INI;
	monde->hauteur_fenetre = HAUTEUR_FENETRE_INI;
}

void afficher_monde_details(Monde monde) {
	printf("Adresse du tableau de vaisseau : %p\n", monde.vaisseaux);
	printf("Nombre de vaisseaux : %d\n", monde.nb_vaisseaux);
	printf("Capacité max de vaisseaux : %d\n", monde.nb_vaisseaux_max);
	printf("----------------\n");
	printf("Adresse du tableau de bonus : %p\n", monde.bonus);
	printf("Nombre de bonus : %d\n", monde.nb_bonus);
	printf("Capacité max de bonus : %d\n", monde.nb_bonus_max);
}

void ajouter_vaisseau_monde(Monde* monde, Vaisseau vaisseau) {
	assert(NULL != monde);

	/* Si on a atteint la capacité maximum de vaisseau, on la double. */
	if ( monde->nb_vaisseaux >= monde->nb_vaisseaux_max ) {
		monde->nb_vaisseaux_max *= 2;
		monde->vaisseaux = (Vaisseau*)realloc(monde->vaisseaux, sizeof(Vaisseau) * monde->nb_vaisseaux_max);
		if ( NULL == monde->vaisseaux )
			exit(EXIT_FAILURE);
	}

	monde->vaisseaux[monde->nb_vaisseaux] = vaisseau;
	monde->nb_vaisseaux += 1;
}

void ajouter_bonus_monde(Monde* monde, Bonus bonus) {
	assert(NULL != monde);

	/* Si on a atteint la capacité maximum de bonus, on la double. */
	if ( monde->nb_bonus >= monde->nb_bonus_max ) {
		monde->nb_bonus_max *= 2;
		monde->bonus = (Bonus*)realloc(monde->bonus, sizeof(Bonus) * monde->nb_bonus_max);
		if ( NULL == monde->bonus )
			exit(EXIT_FAILURE);
	}

	monde->bonus[monde->nb_bonus] = bonus;
	monde->nb_bonus += 1;
}

int dans_la_carte(Monde* monde, int x, int y) {
    if ( !( 0 <= x && x <= monde->largeur_fenetre &&
            0 <= y && y <= monde->hauteur_fenetre ) )

        return 0;

    else

        return 1;
}

int collision(Monde* monde, int x, int y) {
    int i;

    for (i = 0; i < monde->nb_vaisseaux; i++) {
        if ( monde->vaisseaux[i].x == x && monde->vaisseaux[i].y == y )
            return i;
    }

    return -1;
}

void calculer_prochaine_case(Vaisseau* vaisseau, int* x, int* y) {
    switch ( vaisseau->dep ) {
        case NORD:
            *x = vaisseau->x;
            *y = vaisseau->y - vaisseau->vi;
            break;
        case EST:
            *x = vaisseau->x + vaisseau->vi;
            *y = vaisseau->y;
            break;
        case SUD:
            *x = vaisseau->x;
            *y = vaisseau->y + vaisseau->vi;
            break;
        case OUEST:
            *x = vaisseau->x - vaisseau->vi;
            *y = vaisseau->y;
            break;
        default:
            *x = -1;
            *y = -1;
            break;
    }
}

int peux_se_deplacer(Monde* monde, int indice_v) {
    int nouvelles_coords_x, nouvelles_coords_y;
    int vaisseau_touche;
    int x, y;

    assert(NULL != monde);
    assert(indice_v >= 0);

    calculer_prochaine_case( &(monde->vaisseaux[indice_v]), &nouvelles_coords_x, &nouvelles_coords_y );

    /* Si les nouvelles coordonnées sont hors de la carte, on renvoie 0. */
    if ( !dans_la_carte(monde, nouvelles_coords_x, nouvelles_coords_y) )
        return 0;

    x = monde->vaisseaux[indice_v].x;
    y = monde->vaisseaux[indice_v].y;

    /* On regarde si sur le chemin de mouvement du vaisseau, on ne rentre pas en collision avec un autre vaisseau. */
    if ( x < nouvelles_coords_x ) {
    	while ( x <= nouvelles_coords_x ) {
		    vaisseau_touche = collision(monde, x, y);
		    if ( vaisseau_touche != -1 && vaisseau_touche != indice_v )
		        return 0;
		    x += 1;
    	}
    } else if ( x > nouvelles_coords_x ) {
    	while ( x >= nouvelles_coords_x ) {
		    vaisseau_touche = collision(monde, x, y);
		    if ( vaisseau_touche != -1 && vaisseau_touche != indice_v )
		        return 0;
		    x -= 1;
    	}
    } else if ( y < nouvelles_coords_y ) {
    	while ( y <= nouvelles_coords_y ) {
		    vaisseau_touche = collision(monde, x, y);
		    if ( vaisseau_touche != -1 && vaisseau_touche != indice_v )
		        return 0;
		    y += 1;
    	}
    } else if ( y > nouvelles_coords_y ) {
    	while ( y >= nouvelles_coords_y ) {
		    vaisseau_touche = collision(monde, x, y);
		    if ( vaisseau_touche != -1 && vaisseau_touche != indice_v )
		        return 0;
		    y -= 1;
    	}
    }

    return 1;
}