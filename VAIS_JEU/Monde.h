/* Auteurs: LOPES MENDES Ailton
*  Creation: 30/06/2018
*  Modification: 14/07/2018*/
#ifndef __MONDE2__
#define __MONDE2__

#include "Tires.h"
#include "Vaisseaux.h"
#include "Bonus.h"

/*
Espace commentaire : Modifie `configure_tir_monde`.
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
	Tir tir;
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

void afficher_monde(Monde mo);

void afficher_monde_details(Monde monde);

void configure_matiere_monde(Monde* monde, Etats etats, const int x, const int y, const int vie);

void configure_tir_monde(Monde* monde, Tir tir, Etats etats);

/* Ajoute un vaisseau aux coordonnées (x, y) dont le type et sa vie est donné. */
void ajouter_vaisseau_monde(Monde* monde, Vaisseau vaisseau, int x, int y, Etats type, int vie);

/* Libere monde.*/
void libere_monde(Monde* monde);

/* Renvoie par adresse les coordonnées du vaisseau après un déplacement. */
void calculer_prochaine_case_vaisseau(int x, int y, Vaisseau v, int* out_x, int* out_y);

/* Renvoie 1 si le vaisseau à l'indice `indice_vaisseau` et aux coordonnées (x, y) peut se déplacer dans sa direction et 0 sinon. */
int peut_se_deplacer(Monde* monde, int x, int y, int indice_vaisseau);

/* Déplace d'un cran le vaisseau situé aux coordonnées (x, y). */
void deplacer_vaisseau(Monde* monde, int x, int y);

#endif
