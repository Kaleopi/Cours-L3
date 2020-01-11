CC=gcc -Wall -O3
OBJETS=prog.o liste.o cellule.o

prog: $(OBJETS)
	$(CC) -o prog $(OBJETS)

prog.o : prog.c liste.h
	$(CC) -c prog.c

liste.o : liste.c liste.h cellule.h
	$(CC) -c liste.c

cellule.o : cellule.c cellule.h
	$(CC) -c cellule.c

clean:rm prog_liste $(OBJETS)
