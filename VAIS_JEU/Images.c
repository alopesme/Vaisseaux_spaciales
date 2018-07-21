#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include "Images.h"

void charger_image(MLV_Image** image, const char* nom_image, const int largeur) {
	assert(NULL != nom_image);

	*image = MLV_load_image(nom_image);
	MLV_resize_image_with_proportions(*image, largeur, largeur);
}

void dessiner_image(MLV_Image** image, const char* nom_image, const int x, const int y, const int largeur) {
	int largeur_image, hauteur_image;

	assert(NULL != image);
	assert(x >= 0);
	assert(y >= 0);
	assert(largeur >= 0);

	charger_image(image, nom_image, largeur);

	MLV_get_image_size(*image, &largeur_image, &hauteur_image);

	MLV_draw_image(*image, (x - largeur_image/2), (y - hauteur_image/2));

	liberer_image(image);
}

void dessiner_vaisseau(MLV_Image** image, const char* nom_image, const int x, const int y, const int largeur) {
	int largeur_image, hauteur_image;

	assert(NULL != nom_image);
	assert(x >= 0);
	assert(y >= 0);
	assert(largeur >= 0);

	charger_image(image, nom_image, largeur);
	rotation_vaisseau(image, x, y);
	MLV_get_image_size(*image, &largeur_image, &hauteur_image);

	MLV_draw_image(*image, (x - largeur_image/2), (y - hauteur_image/2));
	liberer_image(image);

}
	
void rotation_vaisseau(MLV_Image** image, const int x, const int y) {
	int x_souris, y_souris;
	double res, val = 180 / PI, yl, xl;
	assert(NULL != image);
	assert(x >= 0);
	assert(y >= 0);

	MLV_get_mouse_position(&x_souris, &y_souris);
	yl = (y - y_souris); xl = (x - x_souris);
	res = atan2(xl, yl) * val;

	MLV_rotate_image(*image, res);
}

void liberer_image(MLV_Image** image) {
	assert(NULL != image);

	MLV_free_image(*image);
	*image = NULL;
}
