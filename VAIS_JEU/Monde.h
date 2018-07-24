/* Auteurs: LOPES MENDES Ailton
*  Creation: 30/06/2018
*  Modification: 14/07/2018*/
#ifndef __MONDE__
#define __MONDE__

#include "Tires.h"
#include "Vaisseaux.h"

/*
Espace commentaire : Modifie `configure_tir_monde`.
*/

#define BLOC_VAISSEAUX 16 /* Bloc de mémoire alloué au début pour les vaisseaux. */
#define BLOC_BONUS 8 /* Bloc de mémoire alloué au début pour les bonus. */
#define PROBA_BONUS 10 /* Pourcentage de chance de faire apparaître un bonus à chaque seconde. */

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
void initialiser_monde(Monde* monde, const int t_x, const int t_y, const int larg);

void afficher_monde(Monde mo);

void afficher_monde_details(Monde monde);

void configure_matiere_monde(Monde* monde, Etats etats, const int x, const int y, const int vie);

int configure_tir_monde(Monde* monde, Tir tir, Etats etats, const int larg);

/* Ajoute un vaisseau aux coordonnées (x, y) dont le type et sa vie est donné. */
void ajouter_vaisseau_monde(Monde* monde, const int x, const int y, const int vie, const int larg, const Etats type);

/* Permet d'ajouter un tir dans monde. Ajoute d'abord dans le tableau.
 * Puis converti les coordonnees aux coordonnees de la fenetre graĥique.*/
int ajouter_tir_monde(Monde* monde, const int x, const int y, const int larg, const int indice_v);

/* Libere monde.*/
void libere_monde(Monde* monde);

/* Renvoie 1 si le vaisseau à l'indice `indice_vaisseau` et aux coordonnées (x, y) peut se déplacer dans sa direction et 0 sinon. */
int peut_se_deplacer(Monde* monde, const int x, const int y, const int indice_vaisseau, const int larg);

/* Déplace d'un cran le vaisseau situé aux coordonnées (x, y). */
void deplacer_vaisseau(Monde* monde, const int x, const int y, const int larg);

/* Ajoute un bonus aléatoire dans le monde en fonction d'un taux de probabilité. */
void ajouter_bonus_aleatoire(Monde* monde);

#endif
