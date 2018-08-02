CC = gcc
CFLAGS = -Wall -Wfatal-errors -O3
OBJ = Main.o Deplacement.o  Monde.o  Test.o  Tires.o  Vaisseaux.o  Vitesse.o  Bonus.o  Interface_graphique.o Images.o Test_grap.o Jeu.o Ia.o Music_Sons.o Page_Accueil.o Clic_Menu_Option.o Menu_Option.o Couleur.o
LDFLAGS = -lMLV

Vaisseaux_spaciales: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -lm

Main.o: Main.c Test.h Monde.h Vaisseaux.h Vitesse.h Deplacement.h Tires.h Interface_graphique.h Test_grap.h Music_Sons.h Page_Accueil.h Clic_Menu_Option.h Menu_Option.h Couleur.h

Deplacement.o: Deplacement.c Deplacement.h

Monde.o: Monde.c Monde.h Bonus.h Vaisseaux.h Vitesse.h Deplacement.h Tires.h

Test.o: Test.c Test.h Monde.h Vaisseaux.h Vitesse.h Deplacement.h Tires.h

Test_grap.o: Test_grap.c Test_grap.h Interface_graphique.h Vaisseaux.h Deplacement.h Tires.h Vitesse.h Images.h Monde.h Jeu.h Music_Sons.h Page_Accueil.h Clic_Menu_Option.h Menu_Option.h Couleur.h Ia.h

Tires.o: Tires.c Tires.h

Images.o: Images.c Images.h

Music_Sons.o: Music_Sons.c Music_Sons.h

Vaisseaux.o: Vaisseaux.c Vaisseaux.h Deplacement.h Tires.h Vitesse.h

Vitesse.o: Vitesse.c Vitesse.h

Bonus.o: Bonus.c Bonus.h

Interface_graphique.o: Interface_graphique.c Interface_graphique.h Vaisseaux.h Deplacement.h Tires.h Vitesse.h Images.h Monde.h Music_Sons.h Couleur.h

Jeu.o: Jeu.c Jeu.h Monde.h Bonus.h Vaisseaux.h Vitesse.h Deplacement.h Tires.h Interface_graphique.h Ia.h Music_Sons.h Page_Accueil.h Clic_Menu_Option.h Menu_Option.h Couleur.h

Ia.o: Ia.c Ia.h Monde.h Bonus.h Vaisseaux.h Vitesse.h Deplacement.h Tires.h

Menu_Option.o: Menu_Option.c Menu_Option.h

Couleur.o: Couleur.c Couleur.h

Clic_Menu_Option.o: Clic_Menu_Option.c Clic_Menu_Option.h Menu_Option.h Couleur.h

Page_Accueil.o: Page_Accueil.c Page_Accueil.h Clic_Menu_Option.h Menu_Option.h Couleur.h

clean:
	rm -f *.o
	
%.o: %.c
	$(CC) -c $< $(CFLAGS)

mrproper: clean
	rm -f Vaisseaux_spaciales