#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <MLV/MLV_random.h>
#include <MLV/MLV_time.h>
#include "Vitesse.h"
#include "Tires.h"
#include "Deplacement.h"
#include "Vaisseaux.h"
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

static int controle_vie(Element *elem, Element *elem_modifiable) {
    int temp;
    assert(NULL != elem);
    if (elem_modifiable->vie <= 0) {
        if (elem->vie <= 0)
            elem->etats = VIDE;
        elem_modifiable->vie = 0;
        elem_modifiable->etats = VIDE;
        return 1;
    }

    temp = elem->vie;

    elem->vie -= elem_modifiable->vie;
    elem_modifiable->vie -= temp;
    if (elem->vie <= 0) {
        elem->vie = 0;
        elem->etats = VIDE;
        elem->indice = -1;
    }
    if (elem_modifiable->vie <= 0) {
        elem_modifiable->etats = VIDE;
        elem_modifiable->vie = 0;
        elem_modifiable->indice = -1;

    }
    return 1;
}

static int condition_tir_vaisseau(Monde* monde, int x, int y, const int larg) {
    Tir tir;
    int t_x, t_y, l, x1, x2, y1, y2;
    assert(NULL != monde);
    assert(x >= 0);
    assert(y >= 0);
    assert(x < monde->taille_x);
    assert(y < monde->taille_y);
    tir = monde->tab[y][x].tir;
    tir.coord_t.tir_x -= larg / 4;
    tir.coord_t.tir_y -= larg / 4;
    t_x = (int)tir.coord_t.tir_x; 
    t_y = (int)tir.coord_t.tir_y;
    l = larg / 2;

    if ((monde->tab[t_y / larg][t_x / larg].etats >= JOUEUR && monde->tab[t_y / larg][t_x / larg].etats <= BOSSFINALE)) {
        if (monde->tab[t_y / larg][t_x / larg].indice < 0 || monde->tab[t_y / larg][t_x / larg].indice > monde->nb_vaisseaux_max)
            return 0;
        x1 = monde->vaisseaux[monde->tab[t_y / larg][t_x / larg].indice].x - larg / 2;
        y1 = monde->vaisseaux[monde->tab[t_y / larg][t_x / larg].indice].y - larg / 2;
        x2 = x1 + larg;
        y2 = y1 + larg;
        return coord_tir_touche(tir, x1, x2, y1, y2) && controle_vie(&(monde->tab[t_y / larg][t_x / larg]), &(monde->tab[y][x]));
    }

    if ((monde->tab[t_y / larg][(t_x + l) / larg].etats >= JOUEUR || monde->tab[t_y / larg][(t_x + l) / larg].etats <= BOSSFINALE)) {
        if (monde->tab[t_y / larg][(t_x + l) / larg].indice < 0 || monde->tab[t_y / larg][(t_x + l) / larg].indice > monde->nb_vaisseaux_max)
            return 0;
        tir.coord_t.tir_x += l;
        x1 = monde->vaisseaux[monde->tab[t_y / larg][(t_x + l) / larg].indice].x - larg / 2;
        y1 = monde->vaisseaux[monde->tab[t_y / larg][(t_x + l) / larg].indice].y - larg / 2;
        x2 = x1 + larg;
        y2 = y1 + larg;
        return coord_tir_touche(tir, x1, x2, y1, y2) && controle_vie(&(monde->tab[t_y / larg][(t_x + l) / larg]), &(monde->tab[y][x]));
    }
    
    if ((monde->tab[(t_y + l) / larg][t_x / larg].etats >= JOUEUR || monde->tab[(t_y + l) / larg][t_x / larg].etats <= BOSSFINALE)) {
        if (monde->tab[(t_y + l) / larg][t_x / larg].indice < 0 || monde->tab[(t_y + l) / larg][t_x / larg].indice > monde->nb_vaisseaux_max)
            return 0;
        tir.coord_t.tir_y += l;
        x1 = monde->vaisseaux[monde->tab[(t_y + l) / larg][t_x / larg].indice].x - larg / 2;
        y1 = monde->vaisseaux[monde->tab[(t_y + l) / larg][t_x / larg].indice].y - larg / 2;
        x2 = x1 + larg;
        y2 = y1 + larg;
        return coord_tir_touche(tir, x1, x2, y1, y2) && controle_vie(&(monde->tab[(t_y + l) / larg][t_x / larg]), &(monde->tab[y][x]));
    }
    

    if ((monde->tab[(t_y + l) / larg][(t_x + l) / larg].etats >= JOUEUR || monde->tab[(t_y + l) / larg][(t_x + l) / larg].etats <= BOSSFINALE)) {
        if (monde->tab[(t_y + l) / larg][(t_x + l) / larg].indice < 0 || monde->tab[(t_y + l) / larg][(t_x + l) / larg].indice > monde->nb_vaisseaux_max)
            return 0;
        tir.coord_t.tir_x += l;
        tir.coord_t.tir_y += l;
        x1 = monde->vaisseaux[monde->tab[(t_y + l) / larg][(t_x + l) / larg].indice].x - larg / 2;
        y1 = monde->vaisseaux[monde->tab[(t_y + l) / larg][(t_x + l) / larg].indice].y - larg / 2;
        x2 = x1 + larg;
        y2 = y1 + larg;
        return coord_tir_touche(tir, x1, x2, y1, y2) && controle_vie(&(monde->tab[(t_y + l) / larg][(t_x + l) / larg]), &(monde->tab[y][x]));
    }
    return 0;
}

static int condition_tir(Monde* monde, int x, int y, const int larg) {
    int t_x, t_y, l;
    assert(NULL != monde);
    assert(x >= 0);
    assert(y >= 0);
    assert(x < monde->taille_x);
    assert(y < monde->taille_y);
    t_x = (int)monde->tab[y][x].tir.coord_t.tir_x - larg / 4;
    t_y = (int)monde->tab[y][x].tir.coord_t.tir_y - larg / 4;
    l = larg / 2;

   

    if ((monde->tab[t_y / larg][t_x / larg].etats != VIDE) &&
        (monde->tab[t_y / larg][t_x / larg].etats > TIR || monde->tab[t_y / larg][t_x / larg].etats < TIR))
        return controle_vie(&(monde->tab[t_y / larg][t_x / larg]), &(monde->tab[y][x]));

    if ((monde->tab[t_y / larg][(t_x + l) / larg].etats != VIDE) &&
        (monde->tab[t_y / larg][(t_x + l) / larg].etats < TIR || monde->tab[t_y / larg][(t_x + l) / larg].etats > TIR))
        return controle_vie(&(monde->tab[t_y / larg][(t_x + l) / larg]), &(monde->tab[y][x]));
    
    if ((monde->tab[(t_y + l) / larg][t_x / larg].etats != VIDE) &&
        (monde->tab[(t_y + l) / larg][t_x / larg].etats < TIR || monde->tab[(t_y + l) / larg][t_x / larg].etats > TIR))
        return controle_vie(&(monde->tab[(t_y + l) / larg][t_x / larg]), &(monde->tab[y][x]));
    

    if ((monde->tab[(t_y + l) / larg][(t_x + l) / larg].etats != VIDE) &&
        (monde->tab[(t_y + l) / larg][(t_x + l) / larg].etats < TIR || monde->tab[(t_y + l) / larg][(t_x + l) / larg].etats > TIR))
        return controle_vie(&(monde->tab[(t_y + l) / larg][(t_x + l) / larg]), &(monde->tab[y][x]));
    
    return 0;
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
    monde->vaisseaux = allouer_vaisseaux(BLOC_VAISSEAUX, (t_x / 2) * larg + larg / 2, (t_y / 2) * larg + larg / 2, larg);
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

void configure_matiere_monde(Monde* monde, Etats etats, const int x, const int y, const int vie, const int bvie) {
    assert(NULL != monde);
    assert(x >= 0);
    assert(x < monde->taille_x);
    assert(y >= 0);
    assert(y < monde->taille_y);
    if (etats <= OBSTACLE) {
        if (vie > 0 && vie < bvie)
            etats += 2;
        monde->tab[x][y].etats = etats;
        monde->tab[x][y].vie = vie;
        monde->tab[x][y].indice = -1;
    }

}

int configure_tir_monde(Monde* monde, Tir tir, Etats etats, const int larg) {
    assert(NULL != monde);
    if (etats <= TIR && etats >= TIR) {
        if (monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].etats == VIDE) {
            monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].etats = etats;
            monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].indice = -1;
            monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].vie = tir.degat;
            monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].tir = tir;
            return 1;
        }
    }
    return 0;
}

void ajouter_vaisseau_monde(Monde* monde, const int x, const int y, const int vie, const int larg, const Etats type) {
    assert(NULL != monde);
    assert(x >= 0);
    assert(y >= 0);
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
    
    monde->vaisseaux[monde->nb_vaisseaux].x = x * larg + larg / 2;
    monde->vaisseaux[monde->nb_vaisseaux].y = y * larg + larg / 2;
    monde->vaisseaux[monde->nb_vaisseaux].dep = STOP;
    monde->vaisseaux[monde->nb_vaisseaux].vi = LENT;

    monde->nb_vaisseaux += 1;
}


int ajouter_tir_monde(Monde* monde, const int x, const int y, const int larg, const int indice_v) {
    Tir tir, tir2;
    assert(NULL != monde);
    assert(x >= 0);
    assert(y >= 0);
    assert(larg > 0);

    tir2 = init_tirs(monde->vaisseaux[indice_v].x, monde->vaisseaux[indice_v].y, x, y);
    tir = tir2;
    if (!calculer_tir(&(tir2.coord_t), larg + larg / 5))
        return 0;

    if (!configure_tir_monde(monde, tir2, TIR, larg))
        return 0; 
    
    monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].tir.coord_t.d_x = tir.coord_t.d_x;
    monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].tir.coord_t.d_y = tir.coord_t.d_y;
    monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].tir.coord_t.x_f = tir.coord_t.x_f;
    monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].tir.coord_t.y_f = tir.coord_t.y_f;
    monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].tir.coord_t.tir_x = tir.coord_t.tir_x;
    monde->tab[(int)(tir.coord_t.tir_y / larg)][(int)(tir.coord_t.tir_x / larg)].tir.coord_t.tir_y = tir.coord_t.tir_y;
    return 1;
}

int tir_touche_element(Monde *monde, const int x, const int y, const int larg) {
    assert(x >= 0);
    assert(y >= 0);
    assert(larg > 0);
    assert(x < monde->taille_x);
    assert(y < monde->taille_y);

    if (monde->tab[y][x].etats < TIR && monde->tab[y][x].etats > TIR)
        return 0;

    if (condition_tir_vaisseau(monde, x, y, larg))
        return 1;

    if (condition_tir(monde, x, y, larg))
        return 1;
    
    return 0;
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
    int i;
    Vaisseau copie = {monde->vaisseaux[indice_vaisseau].x, monde->vaisseaux[indice_vaisseau].y, monde->vaisseaux[indice_vaisseau].dep, monde->vaisseaux[indice_vaisseau].vi};
    Rectangle hitbox1, hitbox2;

    assert(NULL != monde);
    assert(indice_vaisseau >= 0);

    calculer_prochaine_case_vaisseau(&copie, &nouvelle_case_x, &nouvelle_case_y, larg);

    /* On vérifie si on ne va pas en hors map. */

    if ( nouvelle_case_x < 0 || nouvelle_case_x >= monde->taille_x ||
         nouvelle_case_y < 0 || nouvelle_case_y >= monde->taille_y )

        return 0;

    if ((copie.x < larg / 2 || copie.x + larg / 2 > monde->taille_x * larg) ||
        (copie.y < larg / 2 || copie.y + larg / 2 > monde->taille_y * larg))
        return 0;

    hitbox1.x = copie.x - larg / 2;
    hitbox1.y = copie.y - larg / 2;
    hitbox1.largeur = larg;
    hitbox1.hauteur = larg;

    /* On vérifie s'il n'y a pas un vaisseau sur la prochaine case. */
    for (i = 0; i < monde->nb_vaisseaux; i++) {
        if ( i == indice_vaisseau )
            continue;

        hitbox2.x = monde->vaisseaux[i].x - larg / 2;
        hitbox2.y = monde->vaisseaux[i].y - larg / 2;
        hitbox2.largeur = larg;
        hitbox2.hauteur = larg;

        if (intersection(hitbox1, hitbox2))
            return 0;

    }

    return 1;
}

void deplacer_vaisseau(Monde* monde, const int x, const int y, const int larg) {
    int nouvelle_case_x, nouvelle_case_y;

    assert(NULL != monde);

    calculer_prochaine_case_vaisseau(&(monde->vaisseaux[monde->tab[y][x].indice]), &nouvelle_case_x, &nouvelle_case_y, larg);

    if (nouvelle_case_x != x || nouvelle_case_y != y) {
        /* On déplace le vaisseau vers sa nouvelle case. */
        monde->tab[nouvelle_case_y][nouvelle_case_x] = monde->tab[y][x];

        /* Son ancienne case devient libre. */
        monde->tab[y][x].etats = VIDE;
        monde->tab[y][x].vie = 0;
        monde->tab[y][x].indice = -1;


    }
}


void ajouter_bonus_aleatoire(Monde* monde) {
    Element elem;
    int proba, x, y;

    assert(NULL != monde);

    proba = PROBA_BONUS; /* Pourcentage de chance qu'un bonus apparaisse. */

    if ( proba > MLV_get_random_integer(0, 100) ) {
        elem.etats = MLV_get_random_integer(BONUS1, BONUS3);
        elem.vie = MLV_get_time();

        do {
            x = MLV_get_random_integer(0, monde->taille_x);
            y = MLV_get_random_integer(0, monde->taille_y);
        } while ( monde->tab[y][x].etats != VIDE );

        monde->tab[y][x] = elem;
    }
}


void ajouter_mur_monde(Monde *monde, const int x, const int y, const int vie, const Etats type) {
    assert(NULL != monde);
    assert(x >= 0);
    assert(x < monde->taille_x);
    assert(y >= 0);
    assert(y < monde->taille_y);
    if (type <= MUR && type >= MUR) 
        configure_matiere_monde(monde, type, x, y, vie, 5);
    
}

int intersection(Rectangle rect1, Rectangle rect2) {
    int horizontal, vertical;

    horizontal = (rect1.x  < rect2.x + rect2.largeur) && (rect2.x < rect1.x + rect1.largeur);
    vertical = (rect1.y < rect2.y + rect2.hauteur) && (rect2.y < rect1.y + rect1.hauteur);

    return horizontal && vertical;
}

void supprimer_vaisseau_monde(Monde* monde, int i_vaisseau) {
    int i;

    assert(NULL != monde);
    assert(i_vaisseau >= 0);

    /* On décale les vaisseaux en écrasant celui qu'on veut supprimer. */
    for (i = i_vaisseau; i < monde->nb_vaisseaux - 1; i++) {
        monde->vaisseaux[i] = monde->vaisseaux[i+1];
    }

    /* On réduit le nombre de vaisseaux. */
    monde->nb_vaisseaux--;
}
