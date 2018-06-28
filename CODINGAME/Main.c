#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Test.h"
#include <MLV/MLV_all.h>

int main(int argc, char const *argv[]) {

	test_allouer_vaisseaux(atoi(argv[1]));
	
	return 0;
}
