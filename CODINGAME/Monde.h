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

typedef struct {
	Vaisseau* vaisseaux;
	int nb_vaisseaux;
	int nb_vaisseaux_max;
	Bonus* bonus;
	int nb_bonus;
	int nb_bonus_max;
} Monde;

/* Initialise un monde par adresse, avec le vaisseau du joueur + NB_BOTS_DEBUT bots ainsi que 0 bonus. */
void initialiser_monde(Monde* monde);
/* Ajoute un vaisseau au monde `monde`. */
void ajouter_vaisseau_monde(Monde* monde, Vaisseau vaisseau);
/* Ajoute un bonus au monde `monde`. */
void ajouter_bonus_monde(Monde* monde, Bonus bonus);

#endif