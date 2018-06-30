CC = gcc
CFLAGS = -Wall -Wfatal-errors -O3
OBJ = Main.o Deplacement.o  Monde.o  Test.o  Tires.o  Vaisseaux.o  Vitesse.o  Bonus.o  Interface_graphique.o  Jeu.o  Ia.o
LDFLAGS = -lMLV

Vaisseaux_spaciales: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) -lm

Main.o: Main.c Test.h Monde.h Vaisseaux.h Vitesse.h Deplacement.h Tires.h Interface_graphique.h

Deplacement.o: Deplacement.c Deplacement.h

Monde.o: Monde.c Monde.h Bonus.h Vaisseaux.h

Test.o: Test.c Test.h Monde.h Vaisseaux.h Vitesse.h Deplacement.h Tires.h

Tires.o: Tires.c Tires.h

Vaisseaux.o: Vaisseaux.c Vaisseaux.h Deplacement.h Tires.h Vitesse.h

Vitesse.o: Vitesse.c Vitesse.h

Bonus.o: Bonus.c Bonus.h

Interface_graphique.o: Interface_graphique.c Interface_graphique.h Vaisseaux.h Monde.h

Jeu.o: Jeu.c Jeu.h Vaisseaux.h Monde.h

Ia.o: Ia.c Ia.h Vaisseaux.h Monde.h

clean:
	rm -f *.o
	
%.o: %.c
	$(CC) -c $< $(CFLAGS)

mrproper: clean
	rm -f Vaisseaux_spaciales
