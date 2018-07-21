#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
#include "Bonus.h"
#include "Monde.h"

static Element **initialise_tab(const int t_x, const int t_y) {
    int i;
    Element **tab;    
    assert(t_x > 0);
    assert(t_y > 0);
    if (NULL == (tab = (Element**)malloc(sizeof(Element*) * t_x))) {
        printf("Malloc rate initialiser_monde\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < t_x; ++i) {
        if(NULL == (tab[i] = (Element*)malloc(sizeof(Element) * t_y))) {
            printf("Malloc rate initialiser_monde %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    return tab;

}

void initialiser_monde(Monde* monde, const int t_x, const int t_y, const int larg) {
    int i, j;   
    assert(t_x > 0);
    assert(t_y > 0);
    
    monde->tab = initialise_tab(t_x, t_y);
    for (i = 0; i < t_y; ++i) {
        for (j = 0; j < t_x; ++j) {
            monde->tab[i][j].etats = VIDE;
            monde->tab[i][j].vie = 0;
            monde->tab[i][j].indice = -1;
        }
    }
    monde->vaisseaux = allouer_vaisseaux(BLOC_VAISSEAUX, (t_x / 2) * larg, (t_y / 2) * larg, larg);
    monde->tab[t_y / 2][t_x / 2].etats = JOUEUR;
    monde->tab[t_y / 2][t_x / 2].vie = 500;
    monde->tab[t_y / 2][t_x / 2].indice = 0;
    monde->nb_vaisseaux_max = BLOC_VAISSEAUX;
    monde->nb_vaisseaux = 1;

    monde->taille_x = t_x;
    monde->taille_y = t_y;
}

void afficher_monde_details(Monde monde) {
    printf("taille_x = %d\n", monde.taille_x);
    printf("taille_y = %d\n", monde.taille_y);
    printf("---------------------\n");
    printf("Adresse tab = %p\n", monde.tab);
    printf("---------------------\n");
    printf("Adresse vaisseaux = %p\n", monde.vaisseaux);
    printf("Nb vaisseaux = %d\n", monde.nb_vaisseaux);
    printf("capacité vaisseaux = %d\n", monde.nb_vaisseaux_max);
}

void afficher_monde(Monde mo) {
    int i, j;
    for (i = 0; i < mo.taille_x; ++i) {
        for (j = 0; j < mo.taille_y; ++j) {
            printf("[%d vie %d] ", mo.tab[i][j].etats, mo.tab[i][j].vie);
        }
        printf("\n");
    }
    printf("\n\n\nVaisseaux\n\n\n");
    afficher_vaisseaux_details(mo.vaisseaux, mo.nb_vaisseaux);
}

void configure_matiere_monde(Monde* monde, Etats etats, const int x, const int y, const int vie) {
    assert(NULL != monde);
    assert(x > 0);
    assert(y > 0);
    assert(vie > 0);
    if (etats < TIR) {
        monde->tab[x][y].etats = etats;
        monde->tab[x][y].vie = vie;
        monde->tab[x][y].indice = -1;
    }

}

void configure_tir_monde(Monde* monde, Tir tir, Etats etats, const int larg) {
    assert(NULL != monde);
    if (etats == TIR) {
        monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].etats = etats;
        monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].indice = -1;
        monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].vie = tir.degat;
        monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].tir = tir;
    }
}

void ajouter_vaisseau_monde(Monde* monde, const int x, const int y, const int vie, const int larg, const Etats type) {
    assert(NULL != monde);
    assert(x > 0);
    assert(y > 0);
    assert(JOUEUR <= type && type <= BOSSFINALE);
    assert(vie > 0);

    /* Si on a atteint la capacité maximum de vaisseau, on la double. */
    if ( monde->nb_vaisseaux >= monde->nb_vaisseaux_max ) {
        monde->nb_vaisseaux_max *= 2;
        monde->vaisseaux = (Vaisseau*)realloc(monde->vaisseaux, sizeof(Vaisseau) * monde->nb_vaisseaux_max);
        if ( NULL == monde->vaisseaux )
            exit(EXIT_FAILURE);
    }

    monde->tab[y][x].etats = type;
    monde->tab[y][x].vie = vie;
    monde->tab[y][x].indice = monde->nb_vaisseaux;
    
    monde->vaisseaux[monde->nb_vaisseaux].x = x * larg;
    monde->vaisseaux[monde->nb_vaisseaux].y = y * larg;
    monde->vaisseaux[monde->nb_vaisseaux].dep = STOP;
    monde->vaisseaux[monde->nb_vaisseaux].vi = LENT;

    monde->nb_vaisseaux += 1;
}


int ajouter_tir_monde(Monde* monde, const int x, const int y, const int larg, const int indice_v) {
    Tir tir;
    assert(NULL != monde);
    assert(x >= 0);
    assert(y >= 0);
    assert(larg > 0);

    tir = init_tirs(monde->vaisseaux[indice_v].x / larg, monde->vaisseaux[indice_v].y / larg, x / larg, y / larg);
    if (!validation_tir(&(tir.coord_t), 0, 0, monde->taille_x, monde->taille_y))
        return 0;

    configure_tir_monde(monde, tir, TIR, 1);
    monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].tir.coord_t.d_x = monde->vaisseaux[indice_v].x;
    monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].tir.coord_t.d_y = monde->vaisseaux[indice_v].y;
    monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].tir.coord_t.x_f = x;
    monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].tir.coord_t.y_f = y;
    monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].tir.coord_t.tir_x *= larg;
    monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].tir.coord_t.tir_y *= larg;
    return 1;
}


void libere_monde(Monde* monde) {
    int i;
    assert(NULL != monde);

    for (i = 0; i < monde->taille_x; ++i) {
        free(monde->tab[i]);
        monde->tab[i] = NULL;
    }

    free(monde->tab);
    monde->tab = NULL;

}


int peut_se_deplacer(Monde* monde, const int x, const int y, const int indice_vaisseau, const int larg) {
    int nouvelle_case_x, nouvelle_case_y;
    Vaisseau v;

    assert(NULL != monde);
    assert(indice_vaisseau >= 0);

    /* On vérifie si on ne va pas en hors map. */
    v = monde->vaisseaux[indice_vaisseau];
    calculer_prochaine_case_vaisseau(&(v));
    nouvelle_case_x = v.x / larg;
    nouvelle_case_y = v.y / larg;
    if ( nouvelle_case_x < 0 || nouvelle_case_x >= monde->taille_x ||
         nouvelle_case_y < 0 || nouvelle_case_y >= monde->taille_y )

        return 0;

    /* On regarde case par case si il n'y a pas quelque chose qui barre la route du vaisseau. */
    /*switch ( monde->vaisseaux[indice_vaisseau].dep ) {
        case NORD: for (i=1; i < monde->vaisseaux[indice_vaisseau].vi + 1; i++) {
            if ( monde->tab[y - i][x].etats != VIDE ) return 0; }
            break;
        case OUEST: for (i=1; i < monde->vaisseaux[indice_vaisseau].vi + 1; i++) {
            if ( monde->tab[y][x + i].etats != VIDE ) return 0; }
            break;
        case SUD: for (i=1; i < monde->vaisseaux[indice_vaisseau].vi + 1; i++) {
            if ( monde->tab[y + i][x].etats != VIDE ) return 0; }
            break;
        case EST: for (i=1; i < monde->vaisseaux[indice_vaisseau].vi + 1; i++) {
            if ( monde->tab[y][x - i].etats != VIDE ) return 0; }
            break;
        default:
            return 0;
    }*/

    return 1;
}

void deplacer_vaisseau(Monde* monde, const int x, const int y, const int larg) {
    int nouvelle_case_x, nouvelle_case_y;

    assert(NULL != monde);

    calculer_prochaine_case_vaisseau(&(monde->vaisseaux[monde->tab[y][x].indice]));
    nouvelle_case_x = monde->vaisseaux[monde->tab[y][x].indice].x / larg;
    nouvelle_case_y = monde->vaisseaux[monde->tab[y][x].indice].y / larg;

    if (nouvelle_case_x != x || nouvelle_case_y != y) {
        /* On déplace le vaisseau vers sa nouvelle case. */
        monde->tab[nouvelle_case_y][nouvelle_case_x] = monde->tab[y][x];

        /* Son ancienne case devient libre. */
        monde->tab[y][x].etats = VIDE;
        monde->tab[y][x].vie = 0;
        monde->tab[y][x].indice = -1;
    }
}
