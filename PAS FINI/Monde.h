/* Auteurs: LOPES MENDES Ailton
*  Creation: 26/06/2018
*  Modification: 26/06/2018*/
#ifndef __MONDE__
#define __MONDE__

#include "Vaisseaux.h"
#include "Bonus.h"

#define NB_BOTS_DEBUT 0
#define BLOC_VAISSEAUX 16 /* Bloc de mémoire alloué au début pour les vaisseaux. */
#define BLOC_BONUS 8 /* Bloc de mémoire alloué au début pour les bonus. */
#define LARGEUR_FENETRE_INI 800
#define HAUTEUR_FENETRE_INI 600

typedef struct {
	Vaisseau* vaisseaux;
	int nb_vaisseaux;
	int nb_vaisseaux_max;

	Bonus* bonus;
	int nb_bonus;
	int nb_bonus_max;

	int largeur_fenetre;
	int hauteur_fenetre;
} Monde;

/* Initialise un monde par adresse, avec le vaisseau du joueur + NB_BOTS_DEBUT bots ainsi que 0 bonus. */
void initialiser_monde(Monde* monde);

/* Affiche les détails d'un monde. */
void afficher_monde_details(Monde monde);

/* Ajoute un vaisseau au monde `monde`. */
void ajouter_vaisseau_monde(Monde* monde, Vaisseau vaisseau);

/* Ajoute un bonus au monde `monde`. */
void ajouter_bonus_monde(Monde* monde, Bonus bonus);

/* Renvoie 1 si les coordonnées (x, y) se situe dans les limites de la carte. */
int dans_la_carte(Monde* monde, int x, int y);

/* Si les coordonnées (x, y) correspondent aux coordonnées d'un vaisseau, renvoie l'indice du vaisseau.
 * Sinon renvoie -1. */
int collision(Monde* monde, int x, int y);

/* Renvoie par adresse les nouvelles coordonnées du vaisseau après un déplacement. */
void calculer_prochaine_case(Vaisseau* vaisseau, int* x, int* y);

/* Renvoie 1 si le vaisseau situé à l'indice `indice_v` peut se déplacer dans sa direction. */
int peux_se_deplacer(Monde* monde, int indice_v);

#endif