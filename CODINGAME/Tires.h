/* Auteurs: LOPES MENDES Ailton
*  Creation: 26/06/2018
*  Modification: 27/06/2018*/
#ifndef __TIRES__
#define __TIRES__

typedef enum {
	SIMPLE,
	DOUBLE,
	TRIPLE,
	CANON,
	RIEN

}Tires;

void afficher_tires(Tires t);

#endif