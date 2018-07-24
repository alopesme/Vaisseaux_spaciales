#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_time.h>
#include "Bonus.h"
#include "Monde.h"

int doit_detruire_bonus(Element bonus) {
	return (MLV_get_time() - bonus.vie) / 1000 > DUREE_BONUS;
}