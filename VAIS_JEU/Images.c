#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include "Images.h"

void charger_image(MLV_Image** image, const char* nom_image, const int l_fen, const int h_fen, const int largeur) {
	assert(NULL != nom_image);
	assert(l_fen > 0);
	assert(h_fen > 0);

	*image = MLV_load_image(nom_image);
	MLV_resize_image_with_proportions(*image, largeur, largeur);
}

void dessiner_image(MLV_Image* image, const int x, const int y, const int largeur) {
	assert(NULL != image);
	assert(x >= 0);
	assert(y >= 0);
	assert(largeur >= 0);

	MLV_draw_image(image, x - largeur, y - largeur);
}

void dessiner_vaisseau(MLV_Image** image, const char* nom_image, const int l_fen, const int h_fen, const int x, const int y, const int largeur) {
	assert(NULL != nom_image);
	assert(l_fen > 0);
	assert(h_fen > 0);
	assert(x >= 0);
	assert(x <= l_fen);
	assert(y >= 0);
	assert(y <= h_fen);
	assert(largeur >= 0);

	charger_image(image, nom_image, l_fen, h_fen, largeur);
	rotation_vaisseau(image, x, y, largeur);
	dessiner_image(*image, x , y, largeur / 2);
	liberer_image(image);

}
	
void rotation_vaisseau(MLV_Image** image, const int x, const int y, const int largeur) {
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