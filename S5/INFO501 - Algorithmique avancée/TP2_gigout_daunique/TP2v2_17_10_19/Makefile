CC = gcc -Wall -O3
OBJETS = main.o pile.o sommet.o liste.o graphe.o cellule.o
main : $(OBJETS)
	$(CC) -o main $(OBJETS)

main.o : main.c pile.h liste.h cellule.h graphe.h sommet.h
	$(CC) -c main.c

pile.o : pile.c pile.h sommet.h
	$(CC) -c pile.c

sommet.o : sommet.c sommet.h
	$(CC) -c sommet.c

liste.o : liste.c liste.h cellule.h
	$(CC) -c liste.c

cellule.o : cellule.c cellule.h
	$(CC) -c cellule.c

graphe.o : graphe.c graphe.h sommet.h
	$(CC) -c graphe.c

clean:
	rm main $(OBJETS)
