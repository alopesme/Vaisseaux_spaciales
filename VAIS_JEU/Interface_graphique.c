#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include "Couleur.h"
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Monde.h"
#include "Images.h"
#include "Music_Sons.h"
#include "Interface_graphique.h"


void afficher_background() {
	MLV_clear_window(FOND);
}

void dessiner_element(Monde* monde, MLV_Sound** son, MLV_Image** image, int x, int y, const int larg) {
	int dessin_x = 0, dessin_y = 0;
	char nom_image[20] = "../Images/";
	/*int largeur_image, hauteur_image;*/

	assert(NULL != monde);	
	dessin_x = x * larg + larg / 2;
	dessin_y = y * larg + larg / 2;

	switch ( monde->tab[y][x].etats ) {
		case MUR:
			strcat(nom_image, "v_wall.png");
			break;
		case OBSTACLE:
			break;
		case MUR_CASSE:

			strcat(nom_image, "v_crack2.png");
			break;
		case TIR:
			dessin_x = (int)monde->tab[y][x].tir.coord_t.tir_x;
			dessin_y = (int)monde->tab[y][x].tir.coord_t.tir_y;
			strcat(nom_image, "v_beam.png");
			break;
		case EXPLOSION:

			strcat(nom_image, "explosion.png");
			effets_speciaux(son, "../SONS_MUSIC/small_blast.ogg");
			monde->tab[y][x].etats = VIDE;

			break;
		case JOUEUR:
			dessin_x = monde->vaisseaux[monde->tab[y][x].indice].x;
			dessin_y = monde->vaisseaux[monde->tab[y][x].indice].y;
			strcat(nom_image, "v_joueur.png");
			dessiner_vaisseau(image, nom_image, dessin_x, dessin_y, larg);
			return;
		case BOT:
			dessin_x = monde->vaisseaux[monde->tab[y][x].indice].x;
			dessin_y = monde->vaisseaux[monde->tab[y][x].indice].y;
			strcat(nom_image, "v_bot.png");
			break;
		case MIBOSS:
			return;
		case BOSSFINALE:
			return;
		case BONUS1:
			strcat(nom_image, "bonus_1.png");
			break;
		case BONUS2:
			strcat(nom_image, "bonus_2.png");
			break;
		case BONUS3:
			strcat(nom_image, "bonus_3.png");
			break;
		default:
			return;
	}
	dessiner_image(image, nom_image, dessin_x, dessin_y, larg);
	/*image = MLV_load_image(nom_image);
	
	MLV_resize_image_with_proportions(image, (int) monde->taille_x * (dim / 100.0), (int) monde->taille_y * (dim / 100.0));

	if ( monde->tab[y][x].etats == JOUEUR )
		rotation_vaisseau(&image, x, y);

	MLV_get_image_size(image, &largeur_image, &hauteur_image);

	MLV_draw_image(image, x - largeur_image / 2, y - hauteur_image / 2);

	liberer_image(&image);*/
}

void effets_speciaux(MLV_Sound** son, const char* nom_son) {
	jouer_son(son, nom_son);
}
