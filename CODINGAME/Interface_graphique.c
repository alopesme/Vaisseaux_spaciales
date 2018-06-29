#include <MLV/MLV_all.h>
#include <string.h>
#include <assert.h>
#include "Interface_graphique.h"
#include "Vaisseaux.h"
#include "Monde.h"

void afficher_background() {
	MLV_clear_window(FOND);
}

void afficher_vaisseau(Vaisseau vaisseau, int largeur_fenetre, int hauteur_fenetre, int x, int y) {
	char nom_image[20] = "../Images/v_";
	MLV_Image* image = NULL;
	int largeur_image, hauteur_image;

	assert(x >= 0);
	assert(y >= 0);

	/* On récupère l'image associé au type de vaisseau. */
	switch ( vaisseau.type ) {
		case JOUEUR:
			strcat(nom_image, "joueur.png");
			break;
		case BOT:
			strcat(nom_image, "joueur.png");
			break;
		case MIBOSS:
			strcat(nom_image, "joueur.png");
			break;
		case BOSSFINALE:
			strcat(nom_image, "joueur.png");
			break;
	}

	image = MLV_load_image(nom_image);
	MLV_resize_image_with_proportions(image, largeur_fenetre*LARGEUR_VAISSEAU, hauteur_fenetre*HAUTEUR_VAISSEAU);
	MLV_get_image_size(image, &largeur_image, &hauteur_image);

	MLV_draw_image(image, x - largeur_image/2, y - hauteur_image/2);
}

void afficher_vaisseaux(Monde* monde) {
	int i;

	assert(NULL != monde);

	for (i = 0; i < monde->nb_vaisseaux; i++)
		afficher_vaisseau(monde->vaisseaux[i], monde->largeur_fenetre, monde->hauteur_fenetre, monde->vaisseaux[i].x, monde->vaisseaux[i].y);
}