#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <assert.h>
#include "Menu_Option.h"
#include "Clic_Menu_Option.h"
#include "Couleur.h"
#include "Page_Accueil.h"

#define NB_X 0
#define NB_Y 4


int cliquer_sur_menu_depart(int taille_x, int taille_y){
    int x, y, i, veri;
    char *texte[NB_X + NB_Y] = {"Jouer", "Option", "Aide", "Quitter"};
    Menu_option menu  = initialisation_Menu_option(taille_x, taille_y, NB_X, NB_Y, texte);
    menu_depart(menu, NB_X, NB_Y);

    while (1){
        MLV_clear_window(COULEUR_FOND_PARTIE);
        MLV_get_mouse_position(&x, &y);
        i = verification_position_souris(menu, MLV_rgba(255, 217, 102, 255), x, y, NB_X, NB_Y, &veri);
        MLV_actualise_window();
        if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED && i == 1)

            break;
    }
    while (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) != MLV_RELEASED);

    return veri;
}