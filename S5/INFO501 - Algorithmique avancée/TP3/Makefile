CC=gcc -Wall -O3
OBJETS=prog_liste.o graphe.o liste.o cellule.o Arcs.o

prog_liste: $(OBJETS)
	$(CC) -o prog_liste $(OBJETS)

prog_liste.o : prog_liste.c liste.h
	$(CC) -c prog_liste.c

graphe.o : graphe.c
	$(CC) -c graphe.c

liste.o : liste.c liste.h cellule.h
	$(CC) -c liste.c
	
	Arcs.o :Arcs.c Arcs.h
	$(CC) -c Arcs.c

cellule.o : cellule.c cellule.h
	$(CC) -c cellule.c

clean:rm prog_liste $(OBJETS)
