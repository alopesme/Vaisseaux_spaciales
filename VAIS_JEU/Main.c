#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Test.h"
#include "Test_grap.h"
#include "Interface_graphique.h"
#include <MLV/MLV_all.h>

int main(int argc, char const *argv[]) {
	
	/*test_monde(atoi(argv[1]), atoi(argv[2]));

	test_affichage_image(atoi(argv[1]), atoi(argv[1]), "../Images/v_joueur.png");*/

	test_rotation_image(atoi(argv[1]), atoi(argv[1]), "../Images/v_joueur.png");


	return 0;
}