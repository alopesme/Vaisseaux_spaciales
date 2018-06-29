/* Auteurs: LOPES MENDES Ailton
*  Creation: 27/06/2018
*  Modification: 27/06/2018*/
#ifndef __VITESSE__
#define __VITESSE__

typedef enum {
	TRES_LENT = 1,
	LENT = 3,
	MOYEN = 5,
	RAPIDE = 7
}Vitesse;

/* Cette fonction sert à afficher la vitesse.*/
void afficher_vitesse(Vitesse vi);

/* Cette fonction va determine la valeur `mut` par rapport à `vi`.
 * Elle revoie 1 si `vi` est un des ces 3 `LENT,MOYEN,RAPIDE`.
 * Renvoie 2 si `vi` c'est `RALENTI_TEMPS` et variable `mut` n'est pas modifie.
 * Sinon renvoye 0.*/
int mutiple_vitesse(const Vitesse *vi, int *mut);

#endif