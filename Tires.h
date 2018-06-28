/* Auteurs: LOPES MENDES Ailton
			Lin Gerald
			Wadan Samy
*  Creation: 26/06/2018
*  Modification: 28/06/2018*/
#ifndef __TIRES__
#define __TIRES__

typedef enum {
	SIMPLE,
	DOUBLE,
	TRIPLE,
	CANON,
	RIEN

}Tires;

/* Affice le Tir.*/
void afficher_tires(Tires t);

/* Determine `tir_x` et `tir_y` par rapport à `tir`.
 * Si `tir` est un de ces tirs `SIMPLE,DOUBLE,TRIPLE,CANON` renvoie 1.
 * Si `tir` est `RIEN` renvoie 2.
 * Sinon renvoie 0.*/
int action_tir(const Tires *tir, int *tir_x, int *tir_y);

#endif