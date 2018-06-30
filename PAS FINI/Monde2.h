/* Auteurs: LOPES MENDES Ailton
*  Creation: 30/06/2018
*  Modification: 30/06/2018*/
#ifndef __MONDE2__
#define __MONDE2__

#include "Tires.h"
#include "Vaisseaux.h"

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
	int indice;
}Element;

typedef struct {
	int taille_x;
	int taille_y;
	Element **tab;
}Monde2;


/* Initialise un Monde.*/
void initialiser_monde2(Monde2* monde, const int t_x, const int t_y);

void configure_matiere_monde(Monde2* monde, const int x, const int y, const int indice,  Etats etats);

void configure_tir_monde(Monde2* monde, Coord_Tir coord_t, Etats etats, const int indice);

void configure_vaisseau_monde(Monde2* monde, Vaisseau vaisseau, Etats etats, const int indice);



/* Libere monde.*/
void libere_monde(Monde2* monde);

#endif