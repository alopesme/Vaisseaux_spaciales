/* Auteurs: LOPES MENDES Ailton
			LAMBERT--DELAVAQUERIE Fabien
* Creation: 10/04/2018
* Modification: 10/04/2018*/

#ifndef __COULEUR__
#define __COULEUR__
#include <MLV/MLV_all.h>

#define COULEUR_FOND_PARTIE MLV_rgba(0, 26, 51, 255)
#define PARTIE_FOND MLV_rgba(100, 44, 32, 255)
#define BOITE_COULEUR MLV_rgba(102, 102, 153, 255)
#define COULEUR_INDICE MLV_rgba(83, 255, 26, 150)
#define FOND MLV_rgba(0, 4, 40, 255)

/* Teste les couleurs dans les define*/
void tester_couleur(MLV_Color tab[], int taille);

#endif