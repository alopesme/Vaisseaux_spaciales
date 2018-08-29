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


void afficher_background(Monde* monde, MLV_Image** image) {
	char nom_image[50] = "../Images/espace2.png";
	int x, y;
	assert(NULL != monde);
	x = MLV_get_window_width();
	y = MLV_get_window_height();
	dessiner_fond(image, nom_image, x, y);
}

void dessiner_element(Monde* monde, MLV_Sound** son, MLV_Image** image, int x, int y) {
	int dessin_x = 0, dessin_y = 0, l, h;
	char nom_image[50] = "../Images/";
	assert(x >= 0);
	assert(x < monde->taille_x);
	assert(y >= 0);
	assert(y < monde->taille_y);
	assert(NULL != monde);

	l = monde->larg; h = monde->haut;
	dessin_x = x * monde->larg + monde->larg / 2;
	dessin_y = y * monde->haut + monde->haut / 2;

	switch ( monde->tab[x][y].etats ) {
		case PLANETE:
			strcat(nom_image, "planete1.png");
			break;
		case OBSTACLE:
			dessin_x = (int)monde->tab[x][y].tir.coord_t.tir_x;
			dessin_y = (int)monde->tab[x][y].tir.coord_t.tir_y;
			strcat(nom_image, "asteroid.png");
			break;
		case PLANETE_CASSE:
			strcat(nom_image, "planete_casse2.png");
			break;
		case TIR:
			dessin_x = (int)monde->tab[x][y].tir.coord_t.tir_x;
			dessin_y = (int)monde->tab[x][y].tir.coord_t.tir_y;
			l = h = monde->tab[x][y].tir.coord_t.larg;
			strcat(nom_image, "v_beam.png");
			break;
		case EXPLOSION:
			strcat(nom_image, "explosion.png");
			effets_speciaux(son, "../SONS_MUSIC/small_blast.ogg");
			monde->tab[x][y].etats = VIDE;

			break;
		case JOUEUR:
			dessin_x = monde->vaisseaux[monde->tab[x][y].indice].x;
			dessin_y = monde->vaisseaux[monde->tab[x][y].indice].y;
			strcat(nom_image, "v_joueur.png");
			dessiner_vaisseau(image, nom_image, dessin_x, dessin_y, l, h);
			return;
		case BOT:
			dessin_x = monde->vaisseaux[monde->tab[x][y].indice].x;
			dessin_y = monde->vaisseaux[monde->tab[x][y].indice].y;
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
	dessiner_image(image, nom_image, dessin_x, dessin_y, l, h);
	/*image = MLV_load_image(nom_image);
	
	MLV_resize_image_with_proportions(image, (int) monde->taille_x * (dim / 100.0), (int) monde->taille_y * (dim / 100.0));

	if ( monde->tab[x][y].etats == JOUEUR )
		rotation_vaisseau(&image, x, y);

	MLV_get_image_size(image, &largeur_image, &hauteur_image);

	MLV_draw_image(image, x - largeur_image / 2, y - hauteur_image / 2);

	liberer_image(&image);*/
}

void effets_speciaux(MLV_Sound** son, const char* nom_son) {
	jouer_son(son, nom_son);
}
