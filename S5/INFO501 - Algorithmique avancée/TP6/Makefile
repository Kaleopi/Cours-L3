CC=gcc -Wall -O3
OBJETS=prog_liste.o liste.o cellule.o

prog_liste: $(OBJETS)
	$(CC) -o prog_liste $(OBJETS)

prog_liste.o : prog_liste.c liste.h
	$(CC) -c prog_liste.c

liste.o : liste.c liste.h cellule.h
	$(CC) -c liste.c

cellule.o : cellule.c cellule.h
	$(CC) -c cellule.c

clean:rm prog_liste $(OBJETS)
