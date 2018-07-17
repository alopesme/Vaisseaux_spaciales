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

void initialiser_monde(Monde* monde, const int t_x, const int t_y) {
    int i, j;   
    assert(t_x > 0);
    assert(t_y > 0);
    
    monde->tab = initialise_tab(t_x, t_y);
    for (i = 0; i < t_x; ++i) {
        for (j = 0; j < t_y; ++j) {
            monde->tab[i][j].etats = VIDE;
            monde->tab[i][j].vie = 0;
            monde->tab[i][j].indice = -1;
        }
    }

    monde->vaisseaux = allouer_vaisseaux(BLOC_VAISSEAUX);
    monde->tab[t_y / 2][t_x / 2].etats = JOUEUR;
    monde->tab[t_y / 2][t_x / 2].vie = 500;
    monde->tab[t_y / 2][t_x / 2].indice = 0;
    monde->nb_vaisseaux_max = BLOC_VAISSEAUX;
    monde->nb_vaisseaux = 1;

    monde->taille_x = t_x;
    monde->taille_y = t_y;
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

void configure_tir_monde(Monde* monde, Tir tir, Etats etats) {
    assert(NULL != monde);
    if (etats == TIR) {
        monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].etats = etats;
        monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].indice = -1;
        monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].vie = tir.degat;
        monde->tab[(int)(tir.coord_t.tir_y)][(int)(tir.coord_t.tir_x)].tir = tir;
    }
}

void ajouter_vaisseau_monde(Monde* monde, Vaisseau vaisseau, int x, int y, Etats type, int vie) {
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

    monde->nb_vaisseaux += 1;
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

void calculer_prochaine_case_vaisseau(int x, int y, Vaisseau v, int* out_x, int* out_y) {
    assert(NULL != out_x);
    assert(NULL != out_y);

    switch ( v.dep ) {
        case NORD:
            *out_x = x;
            *out_y -= v.vi;
        case OUEST:
            *out_x += v.vi;
            *out_y = y;
        case SUD:
            *out_x = x;
            *out_y += v.vi;
        case EST:
            *out_x -= v.vi;
            *out_y = y;
        default:
            *out_x = -1;
            *out_y = -1;
    }
}

int peut_se_deplacer(Monde* monde, int x, int y, int indice_vaisseau) {
    int i;
    int nouvelle_case_x, nouvelle_case_y;

    assert(NULL != monde);
    assert(indice_vaisseau >= 0);

    /* On vérifie si on ne va pas en hors map. */
    calculer_prochaine_case_vaisseau(x, y, monde->vaisseaux[indice_vaisseau], &nouvelle_case_x, &nouvelle_case_y);
    if ( nouvelle_case_x < 0 || nouvelle_case_x > monde->taille_x ||
         nouvelle_case_y < 0 || nouvelle_case_y > monde->taille_y )

        return 0;


    /* On regarde case par case si il n'y a pas quelque chose qui barre la route du vaisseau. */
    switch ( monde->vaisseaux[indice_vaisseau].dep ) {
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
    }

    return 1;
}

void deplacer_vaisseau(Monde* monde, int x, int y) {
    int nouvelle_case_x, nouvelle_case_y;

    assert(NULL != monde);

    calculer_prochaine_case_vaisseau(x, y, monde->vaisseaux[monde->tab[y][x].indice], &nouvelle_case_x, &nouvelle_case_y);

    /* On déplace le vaisseau vers sa nouvelle case. */
    monde->tab[nouvelle_case_y][nouvelle_case_x] = monde->tab[y][x];
    /* Son ancienne case devient libre. */
    monde->tab[y][x].etats = VIDE;
    monde->tab[y][x].vie = 0;
    monde->tab[y][x].indice = -1;
}
