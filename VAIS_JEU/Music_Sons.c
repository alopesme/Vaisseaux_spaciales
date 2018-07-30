#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "Music_Sons.h"

void jouer_son(MLV_Sound** son, const char* nom_son) {
	if (nom_son != NULL) {
		*son = MLV_load_sound(nom_son);
		MLV_play_sound(*son, 1.0);
		
	}
}

void init_music(MLV_Music** musique, const char *nom_mu) {
	*musique = MLV_load_music(nom_mu);
	MLV_play_music(*musique, 0.5, -1 );

}

void libere_musique(MLV_Music** musique) {
	MLV_stop_music();
	MLV_free_music(*musique);
}