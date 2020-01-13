CC = gcc -Wall -O3
OBJETS = main.o pile.o sommet_pile.o Liste_Pile.o graphe_Pile.o Cellule_Pile.o
main : $(OBJETS)
	$(CC) -o main $(OBJETS)
main.o : main.c pile.h Liste_Pile.h Cellule_Pile.h graphe_Pile.h sommet_pile.h
	$(CC) -c main.c
pile.o : pile.c pile.h sommet_pile.h
	$(CC) -c pile.c
sommet_pile.o : sommet_pile.c sommet_pile.h
	$(CC) -c sommet_pile.c
Liste_Pile.o : Liste_Pile.c Liste_Pile.h Cellule_Pile.h
	$(CC) -c Liste_Pile.c
Cellule_Pile.o : Cellule_Pile.c Cellule_Pile.h
	$(CC) -c Cellule_Pile.c
graphe_Pile.o : graphe_Pile.c graphe_Pile.h sommet_pile.h
	$(CC) -c graphe_Pile.c
clean:
	rm main $(OBJETS)