#include <stdio.h>
#include <stdlib.h>
#include "Bonus.h"

Bonus* allouer_bonus(const int nb_bonus) {
	Bonus* bonus;

	bonus = (Bonus*) malloc(sizeof(Bonus) * nb_bonus);
	if (NULL == bonus) {
		printf("Malloc rate \t\tinitialiser_monde -> bonus\n");
		exit(EXIT_FAILURE);
	}

	return bonus;
}