/* Auteurs: LOPES MENDES Ailton
*  Creation: 30/06/2018
*  Modification: 14/07/2018*/
#ifndef __MONDE2__
#define __MONDE2__

#include "Tires.h"
#include "Vaisseaux.h"
#include "Bonus.h"

/*
Espace commentaire : Tout objet aura une vie, si des objets avec une vie se rencontre ils perdent la vie de l'autre.
					 L'unique tableau qu'on gere sera celui des vaisseaux donc on garde l'indice sinon indice sert à rien.
*/

#define BLOC_VAISSEAUX 16 /* Bloc de mémoire alloué au début pour les vaisseaux. */
#define BLOC_BONUS 8 /* Bloc de mémoire alloué au début pour les bonus. */

typedef enum {
	VIDE,
	MUR,
	OBSTACLE,
	TIR,
	JOUEUR,
    BOT,
    MIBOSS,
    BOSSFINALE,
    BONUS1,
	BONUS2,
	BONUS3
}Etats;

typedef struct {
	Etats etats;
	int vie;
	int indice;
}Element;

typedef struct {
	int taille_x;
	int taille_y;
	Element **tab;
	Vaisseau *vaisseaux;
	int nb_vaisseaux;
	int nb_vaisseaux_max;
}Monde;


/* Initialise un Monde.*/
void initialiser_monde(Monde* monde, const int t_x, const int t_y);

void configure_matiere_monde(Monde* monde, Etats etats, const int x, const int y, const int vie);

void configure_tir_monde(Monde* monde, Coord_Tir coord_t, Etats etats, Degat degat);

/* Ajoute un vaisseau aux coordonnées (x, y) dont le type et sa vie est donné. */
void ajouter_vaisseau_monde(Monde* monde, Vaisseau vaisseau, int x, int y, Etats type, int vie);

/* Libere monde.*/
void libere_monde(Monde* monde);

#endif