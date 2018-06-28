/* Auteurs: LOPES MENDES Ailton
*  Creation: 26/06/2018
*  Modification: 27/06/2018*/
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

/* Cette fonction */
int gestion_deplacement(Deplacement dep, int *dep_x, int *dep_y);

#endif