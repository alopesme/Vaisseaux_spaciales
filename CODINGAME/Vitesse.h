/* Auteurs: LOPES MENDES Ailton
*  Creation: 27/06/2018
*  Modification: 27/06/2018*/
#ifndef __VITESSE__
#define __VITESSE__

typedef enum {
	RALENTI_TEMPS,
	LENT,
	MOYEN,
	RAPIDE
}Vitesse;

void afficher_vitesse(Vitesse vi);

#endif