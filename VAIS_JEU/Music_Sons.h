/* Auteurs: LOPES MENDES Ailton
*  Creation: 30/07/2018
*  Modification: 30/07/2018*/

#ifndef __MUSIC_SONS__
#define __MUSIC_SONS__

#include <MLV/MLV_all.h>

void jouer_son(MLV_Sound** son, const char* nom_son);

void init_music(MLV_Music** musique, const char *nom_mu);

void libere_musique(MLV_Music** musique);

#endif