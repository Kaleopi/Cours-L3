CC=gcc -Wall -O3
OBJETS=prog_liste.o graphe.o kruskal.o prim.o liste.o cellule.o arete.o tas.o

prog_liste: $(OBJETS)
	$(CC) -o prog_liste $(OBJETS)

prim.o :prim.c prim.h
	$(CC) -c prim.C

prog_liste.o : prog_liste.c liste.h
	$(CC) -c prog_liste.c

arete.o : arete.c arete.h
	$(CC) -c arete.c

graphe.o : graphe.c
	$(CC) -c graphe.c

liste.o : liste.c liste.h cellule.h
	$(CC) -c liste.c

kruskal.o : kruskal.c kruskal.h
	$(CC) -c kruskal.c
	
tas.o : tas.c tas.h
	$(CC) -c tas.c

cellule.o : cellule.c cellule.h
	$(CC) -c cellule.c



clean:rm prog_liste $(OBJETS)
