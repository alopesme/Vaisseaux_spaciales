#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <assert.h>
#include "Menu_Option.h"
#include "Clic_Menu_Option.h"
#include "Couleur.h"

void menu_depart(Menu_option menu, int nb_x, int nb_y){
    int i, j, mess;
    for(i = 0, mess = 0; i < nb_y; i++) {
        for (j = 0; j < nb_x; j++, mess++)
            MLV_draw_text_box(
                menu.x[j], menu.y[i],
                menu.largeur_x, menu.largeur_y,
                menu.message[mess], 0,
                MLV_COLOR_RED, MLV_COLOR_RED, PARTIE_FOND,
                MLV_TEXT_CENTER,
                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
            );
    }

    MLV_actualise_window();
}

int verification_position_souris(Menu_option menu, MLV_Color couleur, int x, int y, int nb_x, int nb_y, int *veri){
    int i, j, mess, min, max,retour = 0, cpt_x, cpt_y;
    assert(NULL != veri);
    max = (nb_x > nb_y) ? nb_x : nb_y;
    min = (nb_x < nb_y) ? nb_x : nb_y;

    for(i = 0, mess = 0; i < (min == 0) ? 1 : min; i++) {
        for (j = 0; j < max; j++, mess++) {
            cpt_x = (max == nb_x) ? j : i; cpt_y = (max == nb_y) ? j : i;
            if ((menu.x[cpt_x] <= x && x <= menu.x[cpt_x] + menu.largeur_x) && (menu.y[cpt_y] <= y && y <= menu.y[cpt_y] + menu.largeur_y)) {

                MLV_draw_text_box(
                    menu.x[cpt_x], menu.y[cpt_y],
                    menu.largeur_x, menu.largeur_y,
                    menu.message[mess], 0,
                    MLV_COLOR_RED, MLV_COLOR_RED, couleur, 
                    MLV_TEXT_CENTER,
                    MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
                );
                retour = 1;
                *veri = mess + 1;
            }
            else {
                MLV_draw_text_box(
                menu.x[cpt_x], menu.y[cpt_y],
                menu.largeur_x, menu.largeur_y,
                menu.message[mess], 0,
                MLV_COLOR_RED, MLV_COLOR_RED, PARTIE_FOND,
                MLV_TEXT_CENTER,
                MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
                );
            }
        }
        
    }    
    return retour;
}

