/* Auteurs: LOPES MENDES Ailton
			Lin Gerald
			Wadan Samy
*  Creation: 26/06/2018
*  Modification: 28/06/2018*/
#ifndef __VAISSEAU__
#define __VAISSEAU__

#include "Deplacement.h"
#include "Vitesse.h"
#include "Tires.h"

typedef enum {
    JOUEUR,
    BOT,
    MIBOSS,
    BOSSFINALE
    
}Type_vaisseau;

typedef struct {
	int x;
	int y;
	Type_vaisseau vaisseau;
	Deplacement dep;
	Vitesse vi;
	Tir tir;
}Vaisseau;

/* Cette fonction sert à afficher un vaisseau.*/
void afficher_vaisseau(const Type_vaisseau vaisseau);

/* Cette fonction sert à afficher tous les vaisseaux.*/
void afficher_vaisseaux(const Vaisseau* vaisseaux, const int nb_vaisseaux);

/* Cette fonction affiche tous les details d'un vaisseau.*/
void afficher_vaisseau_details(const Vaisseau vaisseau);
 
/* Cette fonction affiche tous les details de tous les vaisseaux.*/
void afficher_vaisseaux_details(const Vaisseau* vaisseaux, const int nb_vaisseaux);


/*Cette fonction alloue les vaisseaux.*/
Vaisseau* allouer_vaisseaux(const int nb_vaisseaux);


/* Libere les vaisseaux.*/
void libere_vaisseaux(Vaisseau* vaisseaux, const int nb_vaisseaux);

#endif