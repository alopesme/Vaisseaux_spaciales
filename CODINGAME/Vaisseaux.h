/* Auteurs: LOPES MENDES Ailton
*  Creation: 26/06/2018
*  Modification: 27/06/2018*/
#ifndef __VAISSEAU__
#define __VAISSEAU__

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
	Tires tires;
}Vaisseau;

typedef struct {
	Vaisseau *vaisseaux;
	int nb_vaisseaux;
}Vaisseaux;

/* Cette fonction sert à afficher un vaisseau.*/
void afficher_vaisseau(const Type_vaisseau vaisseau);

/* Cette fonction sert à afficher tous les vaisseaux.*/
void afficher_vaisseaux(const Vaisseaux *vaisseaux, const int nb_vaisseaux);

/* Cette fonction affiche tous les details d'un vaisseau.*/
void afficher_vaisseau_details(const Vaisseau vaisseau);
 
/* Cette fonction affiche tous les details de tous les vaisseaux.*/
void afficher_vaisseaux_details(const Vaisseaux *vaisseaux, const int nb_vaisseaux);


/*Cette fonction alloue les vaisseaux.*/
int allouer_vaisseaux(const int nb_vaisseaux, Vaisseaux *vaisseaux);


/* Libere les vaisseaux.*/
void libere_vaisseaux(Vaisseaux *vaisseaux, const int nb_vaisseaux);

#endif