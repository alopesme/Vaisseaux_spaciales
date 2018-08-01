#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Menu_Option.h"


Menu_option initialisation_Menu_option(int taille_x, int taille_y, int nb_x, int nb_y, char *texte[]){

    Menu_option menu;
    int i, mess;
    mess = nb_x + nb_y;


    for (i = 0; i < mess; i++) 
        strcpy(menu.message[i], texte[i]);

    menu.x[0] = taille_x / 10; 
    menu.largeur_x = taille_x - (2 * menu.x[0]);

    menu.largeur_y = taille_y / (nb_y * 2 + 1);
    menu.y[0] = (taille_y / 2 - nb_y * menu.largeur_y);

    for (i = 1; i <= nb_y + 1; i++)
        menu.y[i] = menu.y[i - 1] + 2 * menu.largeur_y;

    for (i = 1; i <= nb_x + 1; i++)
        menu.x[i] = menu.x[i - 1] + 2 * menu.largeur_y;

    return menu;

}

