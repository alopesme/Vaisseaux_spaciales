/* Auteurs: LOPES MENDES Ailton
*  Creation: 15/07/2018
*  Modification: 15/07/2018*/

#ifndef __TEST_GRAP__
#define __TEST_GRAP__

/*
Espace commentaire : Pour test graphique
*/

/* Affiche l'image au milieu de la fenetre.*/
void test_affichage_image(const int l_fen, const int h_fen, const char* nom_im);

/* Clic l'image tourne vers la direction du clique.*/
void test_rotation_image(const int l_fen, const int h_fen, const char* nom_im);

/* Affiche le tir.*/
void test_un_tir_image(const int l_fen, const int h_fen, const char* nom_im);

/* Déplace le vaisseau avec les flèches directionnelles. */
void test_deplacement_vaisseau(const int l_fen, const int h_fen);


#endif
