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
	/*
	test_monde_vide(atoi(argv[1]), atoi(argv[2]));

	test_affichage_image(atoi(argv[1]), atoi(argv[1]), "../Images/v_joueur.png");

	test_rotation_image(atoi(argv[1]), atoi(argv[1]), "../Images/v_joueur.png");
	
	test_un_tir_image(atoi(argv[1]), atoi(argv[1]), "../Images/v_beam.png"); 
	
	test_deplacement_vaisseau(atoi(argv[1]), atoi(argv[1]));*/

	test_monde_tir(atoi(argv[1]), atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	return 0;
}
