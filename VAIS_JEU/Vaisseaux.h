/* Auteurs: LOPES MENDES Ailton
			Lin Gerald
			Wadan Samy
*  Creation: 26/06/2018
*  Modification: 14/07/2018*/
#ifndef __VAISSEAU__
#define __VAISSEAU__

#include "Deplacement.h"
#include "Vitesse.h"

/*
Espace commentaire : Rien modifie
*/

typedef struct {
	int x;
	int y;
	Deplacement dep;
	Vitesse vi;
}Vaisseau;

/* Cette fonction affiche tous les details d'un vaisseau.*/
void afficher_vaisseau_details(const Vaisseau vaisseau);
 
/* Cette fonction affiche tous les details de tous les vaisseaux.*/
void afficher_vaisseaux_details(const Vaisseau* vaisseaux, const int nb_vaisseaux);

/*Cette fonction alloue les vaisseaux.*/
Vaisseau* allouer_vaisseaux(const int nb_vaisseaux, const int x, const int y, const int larg, const int haut);

/* Calcule les coordonnées de la case du vaisseau après un déplacement (elle peut rester la même).*/
void calculer_prochaine_case_vaisseau(Vaisseau *v, int* out_x, int* out_y, int larg, int haut);

/* Libere les vaisseaux.*/
void libere_vaisseaux(Vaisseau* vaisseaux);

#endif
