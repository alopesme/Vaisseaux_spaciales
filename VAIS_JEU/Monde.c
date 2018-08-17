#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
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

/* Gere la vie des element.
 * Pour effacer les vaisseaux verifie l'indice et echange avec le dernier vaisseau puis diinue le nombre.*/
static int controle_vie(Monde *monde, Element *elem, Element *elem_modifiable) {
    int temp;
    assert(NULL != elem);
    if (elem->etats >= BONUS1) {
        if (elem_modifiable->etats >= JOUEUR && elem_modifiable->etats <= BOSSFINALE) 
            elem_modifiable->vie += elem->etats;
        return 0;
    }

    if (elem_modifiable->vie <= 0 || elem->vie < 0) {
        if (elem_modifiable->etats >= JOUEUR && elem_modifiable->etats <= BOSSFINALE) 
            supprimer_vaisseau_monde(monde, &(elem_modifiable->indice));
        
        elem_modifiable->vie = 0;
        elem_modifiable->etats = EXPLOSION;
        return 1;
    }

    temp = elem->vie;

    elem->vie -= elem_modifiable->vie;
    elem_modifiable->vie -= temp;
    if (elem->vie <= 0) {
        if (elem->etats >= JOUEUR && elem->etats <= BOSSFINALE) 
            supprimer_vaisseau_monde(monde, &(elem->indice));
        
        elem->vie = 0;
        elem->etats = EXPLOSION;
    }

    if (elem_modifiable->vie <= 0) {
        if (elem_modifiable->etats >= JOUEUR && elem_modifiable->etats <= BOSSFINALE) 
            supprimer_vaisseau_monde(monde, &(elem_modifiable->indice));
        
        elem_modifiable->etats = EXPLOSION;
        elem_modifiable->vie = 0;
    }
    return 1;
}

/* Verifie si un des points du tir à touche un vaisseau.*/
static int condition_tir_vaisseau(Monde* monde, int x, int y) {
    Tir tir;
    int t_x, t_y, l, h, x1, x2, y1, y2;
    assert(NULL != monde);
    assert(x >= 0);
    assert(y >= 0);
    assert(x < monde->taille_x);
    assert(y < monde->taille_y);
    tir = monde->tab[y][x].tir;
    tir.coord_t.tir_x -= monde->larg / 4;
    tir.coord_t.tir_y -= monde->haut / 4;
    t_x = (int)tir.coord_t.tir_x; 
    t_y = (int)tir.coord_t.tir_y;
    l = monde->larg / 2; h = monde->haut / 2;

    if ((monde->tab[t_y / monde->haut][t_x / monde->larg].etats >= JOUEUR && monde->tab[t_y / monde->haut][t_x / monde->larg].etats <= BOSSFINALE)) {
        if (monde->tab[t_y / monde->haut][t_x / monde->larg].indice < 0 || monde->tab[t_y / monde->haut][t_x / monde->larg].indice > monde->nb_vaisseaux_max)
            return 0;
        x1 = monde->vaisseaux[monde->tab[t_y / monde->haut][t_x / monde->larg].indice].x - monde->larg / 2;
        y1 = monde->vaisseaux[monde->tab[t_y / monde->haut][t_x / monde->larg].indice].y - monde->haut / 2;
        x2 = x1 + monde->larg;
        y2 = y1 + monde->haut;
        return coord_tir_touche(tir, x1, x2, y1, y2) && controle_vie(monde, &(monde->tab[t_y / monde->haut][t_x / monde->larg]), &(monde->tab[y][x]));
    }

    if ((monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].etats >= JOUEUR || monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].etats <= BOSSFINALE)) {
        if (monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].indice < 0 || monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].indice > monde->nb_vaisseaux_max)
            return 0;
        tir.coord_t.tir_x += l;
        x1 = monde->vaisseaux[monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].indice].x - monde->larg / 2;
        y1 = monde->vaisseaux[monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].indice].y - monde->haut / 2;
        x2 = x1 + monde->larg;
        y2 = y1 + monde->haut;
        return coord_tir_touche(tir, x1, x2, y1, y2) && controle_vie(monde, &(monde->tab[t_y / monde->haut][(t_x + l) / monde->larg]), &(monde->tab[y][x]));
    }
    
    if ((monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].etats >= JOUEUR || monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].etats <= BOSSFINALE)) {
        if (monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].indice < 0 || monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].indice > monde->nb_vaisseaux_max)
            return 0;
        tir.coord_t.tir_y += l;
        x1 = monde->vaisseaux[monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].indice].x - monde->larg / 2;
        y1 = monde->vaisseaux[monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].indice].y - monde->haut / 2;
        x2 = x1 + monde->larg;
        y2 = y1 + monde->haut;
        return coord_tir_touche(tir, x1, x2, y1, y2) && controle_vie(monde, &(monde->tab[(t_y + h) / monde->haut][t_x / monde->larg]), &(monde->tab[y][x]));
    }
    

    if ((monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].etats >= JOUEUR || monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].etats <= BOSSFINALE)) {
        if (monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].indice < 0 || monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].indice > monde->nb_vaisseaux_max)
            return 0;
        tir.coord_t.tir_x += l;
        tir.coord_t.tir_y += l;
        x1 = monde->vaisseaux[monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].indice].x - monde->larg / 2;
        y1 = monde->vaisseaux[monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].indice].y - monde->haut / 2;
        x2 = x1 + monde->larg;
        y2 = y1 + monde->haut;
        return coord_tir_touche(tir, x1, x2, y1, y2) && controle_vie(monde, &(monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg]), &(monde->tab[y][x]));
    }
    return 0;
}

/* Verifie si le tire touche un element.*/
static int condition_tir(Monde* monde, int x, int y) {
    int t_x, t_y, l, h;
    assert(NULL != monde);
    assert(x >= 0);
    assert(y >= 0);
    assert(x < monde->taille_x);
    assert(y < monde->taille_y);
    t_x = (int)monde->tab[y][x].tir.coord_t.tir_x - monde->larg / 4;
    t_y = (int)monde->tab[y][x].tir.coord_t.tir_y - monde->haut / 4;
    l = monde->larg / 2; h = monde->haut / 2;

   

    if ((monde->tab[t_y / monde->haut][t_x / monde->larg].etats != VIDE) &&
        (monde->tab[t_y / monde->haut][t_x / monde->larg].etats > TIR || monde->tab[t_y / monde->haut][t_x / monde->larg].etats < TIR))
        return controle_vie(monde, &(monde->tab[t_y / monde->haut][t_x / monde->larg]), &(monde->tab[y][x]));

    if ((monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].etats != VIDE) &&
        (monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].etats < TIR || monde->tab[t_y / monde->haut][(t_x + l) / monde->larg].etats > TIR))
        return controle_vie(monde, &(monde->tab[t_y / monde->haut][(t_x + l) / monde->larg]), &(monde->tab[y][x]));
    
    if ((monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].etats != VIDE) &&
        (monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].etats < TIR || monde->tab[(t_y + h) / monde->haut][t_x / monde->larg].etats > TIR))
        return controle_vie(monde, &(monde->tab[(t_y + h) / monde->haut][t_x / monde->larg]), &(monde->tab[y][x]));
    

    if ((monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].etats != VIDE) &&
        (monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].etats < TIR || monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg].etats > TIR))
        return controle_vie(monde, &(monde->tab[(t_y + h) / monde->haut][(t_x + l) / monde->larg]), &(monde->tab[y][x]));
    
    return 0;
}

/* Definie les coordonnees de `hitbox2` à la case de `temp_x, temp_y` si element n'est pas un tir ou vide.*/
static int condition_contact_vaisseau(Monde *monde, Rectangle *hitbox2, const Rectangle hitbox1, const int temp_x, const int temp_y, const int x, const int y) {
    assert(NULL != monde);
    assert(NULL != hitbox2);
    assert(temp_x >= 0);
    assert(temp_x < monde->taille_x); 
    assert(temp_y >= 0);
    assert(temp_y < monde->taille_y);
    assert(x >= 0);
    assert(x < monde->taille_x);
    assert(y >= 0);
    assert(y < monde->taille_y);

    if (monde->tab[temp_y][temp_x].etats != VIDE) {
        if ((monde->tab[temp_y][temp_x].etats <= MUR_CASSE && monde->tab[temp_y][temp_x].etats >= MUR) 
            || (monde->tab[temp_y][temp_x].etats <= BONUS3 && monde->tab[temp_y][temp_x].etats >= BONUS1)){
            hitbox2->x = temp_x * hitbox1.largeur;
            hitbox2->y = temp_y * hitbox1.hauteur;
            hitbox2->largeur = hitbox1.largeur;
            hitbox2->hauteur = hitbox1.hauteur;
            return 1;
        }

        if ((monde->tab[temp_y][temp_x].etats <= BOSSFINALE && monde->tab[temp_y][temp_x].etats >= JOUEUR)
            && monde->tab[temp_y][temp_x].indice != monde->tab[y][x].indice) {
            hitbox2->x = monde->vaisseaux[monde->tab[temp_y][temp_x].indice].x - hitbox1.largeur / 2;
            hitbox2->y = monde->vaisseaux[monde->tab[temp_y][temp_x].indice].y - hitbox1.hauteur / 2;
            hitbox2->largeur = hitbox1.largeur;
            hitbox2->hauteur = hitbox1.hauteur;
            return 1;
        }
    }
    return 0;
}

/* Verifie si un des point de `hitbox1` est dans une case non vide ou qui n'est pas un tir avec `condition_contact_vaisseau`.
 * Renvoye `hitbox2`.*/
static Rectangle contact_vaisseau(Monde* monde, const Rectangle hitbox1, const int x, const int y) {
    Rectangle hitbox2 = {-1, -1, -1, -1};
    int temp_x, temp_y;
    assert(NULL != monde);
    assert(x >= 0);
    assert(x < monde->taille_x);
    assert(y >= 0);
    assert(y < monde->taille_y);

    temp_x = (hitbox1.x / hitbox1.largeur);
    temp_y = (hitbox1.y / hitbox1.hauteur);
    if (condition_contact_vaisseau(monde, &hitbox2, hitbox1, temp_x, temp_y, x, y))
        return hitbox2;

    temp_x = ((hitbox1.x + hitbox1.largeur) / hitbox1.largeur);
    if (temp_x >= monde->taille_x || temp_x < 0)
        temp_x--;
    temp_y = (hitbox1.y / hitbox1.hauteur);
    if (condition_contact_vaisseau(monde, &hitbox2, hitbox1, temp_x, temp_y, x, y))
        return hitbox2;

    temp_x = (hitbox1.x / hitbox1.largeur);
    temp_y = ((hitbox1.y + hitbox1.hauteur) / hitbox1.hauteur);
    if (temp_y >= monde->taille_y || temp_y < 0)
        temp_y--;
    if (condition_contact_vaisseau(monde, &hitbox2, hitbox1, temp_x, temp_y, x, y))
        return hitbox2;

    temp_x = ((hitbox1.x + hitbox1.largeur) / hitbox1.largeur);
    temp_y = ((hitbox1.y + hitbox1.hauteur) / hitbox1.hauteur);
    if (temp_x >= monde->taille_x || temp_x < 0 || temp_y >= monde->taille_y || temp_y < 0) {
        temp_x--;temp_y--;
    }
        
    if (condition_contact_vaisseau(monde, &hitbox2, hitbox1, temp_x, temp_y, x, y))
        return hitbox2;

    return hitbox2;
}

void initialiser_monde(Monde* monde, const int t_x, const int t_y, const int larg, const int haut) {
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
    monde->vaisseaux = allouer_vaisseaux(BLOC_VAISSEAUX, (t_x / 2) * larg + larg / 2, (t_y / 2) * larg + larg / 2, larg, haut);
    monde->tab[t_y / 2][t_x / 2].etats = JOUEUR;
    monde->tab[t_y / 2][t_x / 2].vie = 500;
    monde->tab[t_y / 2][t_x / 2].indice = 0;
    monde->nb_vaisseaux_max = BLOC_VAISSEAUX;
    monde->nb_vaisseaux = 1;

    monde->taille_x = t_x;
    monde->taille_y = t_y;
    monde->larg = larg;
    monde->haut = haut;
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

int configure_tir_monde(Monde* monde, Tir tir, Etats etats) {
    assert(NULL != monde);
    if ((etats <= TIR && etats >= TIR)) {
        if (monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].etats == VIDE) {
            monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].etats = etats;
            monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].indice = -1;
            monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].vie = tir.degat;
            monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].tir = tir;
            return 1;
        }
    }
    return 0;
}

void ajouter_vaisseau_monde(Monde* monde, const int x, const int y, const int vie, const Etats type) {
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
    
    monde->vaisseaux[monde->nb_vaisseaux].x = x * monde->larg + monde->larg / 2;
    monde->vaisseaux[monde->nb_vaisseaux].y = y * monde->haut + monde->haut / 2;
    monde->vaisseaux[monde->nb_vaisseaux].dep = STOP;
    monde->vaisseaux[monde->nb_vaisseaux].vi = LENT;

    monde->nb_vaisseaux += 1;
}


int ajouter_tir_monde(Monde* monde, const int x, const int y, const int indice_v) {
    Tir tir, tir2;
    assert(NULL != monde);
    assert(x >= 0);
    assert(y >= 0);

    tir2 = init_tirs(monde->vaisseaux[indice_v].x, monde->vaisseaux[indice_v].y, x, y);
    tir = tir2;
    if (!calculer_tir(&(tir2.coord_t), monde->larg + monde->larg / 5))
        return 0;

    if (!configure_tir_monde(monde, tir2, TIR))
        return 0; 
    
    monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].tir.coord_t.d_x = tir.coord_t.d_x;
    monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].tir.coord_t.d_y = tir.coord_t.d_y;
    monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].tir.coord_t.x_f = tir.coord_t.x_f;
    monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].tir.coord_t.y_f = tir.coord_t.y_f;
    monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].tir.coord_t.tir_x = tir.coord_t.tir_x;
    monde->tab[(int)(tir.coord_t.tir_y / monde->haut)][(int)(tir.coord_t.tir_x / monde->larg)].tir.coord_t.tir_y = tir.coord_t.tir_y;
    return 1;
}

int tir_touche_element(Monde *monde, const int x, const int y) {
    assert(x >= 0);
    assert(y >= 0);
    assert(x < monde->taille_x);
    assert(y < monde->taille_y);

    if (monde->tab[y][x].etats < TIR && monde->tab[y][x].etats > TIR)
        return 0;

    if (condition_tir_vaisseau(monde, x, y))
        return 1;

    if (condition_tir(monde, x, y))
        return 1;
    
    return 0;
}

void libere_monde(Monde* monde) {
    int i;
    assert(NULL != monde);
    libere_vaisseaux(monde->vaisseaux);
    for (i = 0; i < monde->taille_x; ++i) {
        free(monde->tab[i]);
        monde->tab[i] = NULL;
    }

    free(monde->tab);
    monde->tab = NULL;
}


int peut_se_deplacer(Monde* monde, const int x, const int y, const int indice_vaisseau) {
    int nouvelle_case_x, nouvelle_case_y, ind_x, ind_y;
    Vaisseau copie = monde->vaisseaux[indice_vaisseau];
    Rectangle hitbox1, hitbox2;

    assert(NULL != monde);
    assert(indice_vaisseau >= 0);

    calculer_prochaine_case_vaisseau(&copie, &nouvelle_case_x, &nouvelle_case_y, monde->larg, monde->haut);

    /* On vérifie si on ne va pas en hors map. */

    if ( nouvelle_case_x < 0 || nouvelle_case_x >= monde->taille_x ||
         nouvelle_case_y < 0 || nouvelle_case_y >= monde->taille_y )

        return 0;

    if ((copie.x < monde->larg / 2 || copie.x + monde->larg / 2 > monde->taille_x * monde->larg) ||
        (copie.y < monde->haut / 2 || copie.y + monde->haut / 2 > monde->taille_y * monde->haut))
        return 0;


    hitbox1.x = copie.x - monde->larg / 2;
    hitbox1.y = copie.y - monde->haut / 2;
    hitbox1.largeur = monde->larg;
    hitbox1.hauteur = monde->haut;
    hitbox2 = contact_vaisseau(monde, hitbox1, x, y);

    ind_x = (hitbox2.x + hitbox2.largeur / 2) / hitbox2.largeur;
    ind_y = (hitbox2.y + hitbox2.hauteur / 2) / hitbox2.hauteur;
    if (intersection(hitbox1, hitbox2)) 
        return controle_vie(monde, &(monde->tab[ind_y][ind_x]), &(monde->tab[y][x]));    
    
    return 1;
}

void deplacer_vaisseau(Monde* monde, const int x, const int y) {
    int nouvelle_case_x, nouvelle_case_y;

    assert(NULL != monde);

    calculer_prochaine_case_vaisseau(&(monde->vaisseaux[monde->tab[y][x].indice]), &nouvelle_case_x, &nouvelle_case_y, monde->larg, monde->haut);

    if (nouvelle_case_x != x || nouvelle_case_y != y) {
        /* On déplace le vaisseau vers sa nouvelle case. */
        monde->tab[nouvelle_case_y][nouvelle_case_x] = monde->tab[y][x];

        /* Son ancienne case devient libre. */
        monde->tab[y][x].etats = VIDE;
        monde->tab[y][x].vie = 0;
        monde->tab[y][x].indice = -1;
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

void supprimer_vaisseau_monde(Monde* monde, int *i_vaisseau) {
    int x, y;
    assert(NULL != monde);
    assert(NULL != i_vaisseau);
    x = monde->vaisseaux[monde->nb_vaisseaux - 1].x / monde->larg;
    y = monde->vaisseaux[monde->nb_vaisseaux - 1].y / monde->haut;
    monde->vaisseaux[*i_vaisseau] = monde->vaisseaux[monde->nb_vaisseaux - 1];
    monde->tab[y][x].indice = *i_vaisseau;
    monde->nb_vaisseaux--;
    *i_vaisseau = -1;
}