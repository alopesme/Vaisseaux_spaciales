#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include <math.h>
#include "Images.h"

void charger_image(MLV_Image** image, const char* nom_image, const int l_fen, const int h_fen) {
	assert(NULL != nom_image);
	assert(l_fen > 0);
	assert(h_fen > 0);

	*image = MLV_load_image(nom_image);
	MLV_resize_image_with_proportions(*image, l_fen / 10, h_fen /10);
}

void dessiner_image(MLV_Image* image, const int x, const int y, const int largeur) {
	assert(NULL != image);
	assert(x >= 0);
	assert(y >= 0);
	assert(largeur >= 0);

	MLV_draw_image(image, x - largeur, y - largeur);
}

void rotation_vaisseau(MLV_Image* image, const int x, const int y) {
	int x_souris, y_souris;
	double res;
	assert(NULL != image);
	assert(x >= 0);
	assert(y >= 0);

	MLV_get_mouse_position(&x_souris, &y_souris);
	res = 180;
	printf("%lf\n", res);

	MLV_rotate_image(image, res);
}

void liberer_image(MLV_Image** image) {
	assert(NULL != image);

	MLV_free_image(*image);
	*image = NULL;
}