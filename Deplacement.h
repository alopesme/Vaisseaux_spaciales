/* Auteurs: LOPES MENDES Ailton
			Lin Gerald
			Wadan Samy
*  Creation: 26/06/2018
*  Modification: 28/06/2018*/
#ifndef __DEPLACEMENT__
#define __DEPLACEMENT__

typedef enum {   
    ROTATION,
    NORD,
    SUD,
    EST,
    OUEST,
    STOP
}Deplacement;

/*Cette fonction set à afficher le deplacement.*/
void afficher_deplacement(Deplacement dep);

/* Cette fonction va determiner les valeur `dep_x` et `dep_y`.
 * Les valeurs `dep_x` et `dep_y` vont etre determiner par rapport au deplacement.
 * Elles seront modifie que pour les 4 directions `NORD,SUD,EST,OUEST` et la fonction renvoie 1.
 * Cette renvoie 2 si le deplacement est `ROTATION` et 3 si c'est `STOP`.
 * Sinon la fonction renvoie 0.*/
int action_deplacement(const Deplacement *dep, int *dep_x, int *dep_y);

#endif