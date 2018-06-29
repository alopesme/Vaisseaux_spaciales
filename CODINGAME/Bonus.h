/* Auteurs: LOPES MENDES Ailton
*  Creation: 26/06/2018
*  Modification: 26/06/2018*/
#ifndef __BONUS__
#define __BONUS__

typedef enum {
	BONUS1,
	BONUS2,
	BONUS3
} Type_bonus;

typedef struct {
	int x;
	int y;
	Type_bonus type;
} Bonus;

/* Alloue l'espace nécéssaire pour `nb_bonus` bonus et renvoie l'adresse du tableau. */
Bonus* allouer_bonus(const int nb_bonus);

#endif