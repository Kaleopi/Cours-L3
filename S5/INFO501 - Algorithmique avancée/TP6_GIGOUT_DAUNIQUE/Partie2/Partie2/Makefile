CC = gcc -Wall -O3 -g
OBJETS = prog_table_hachage.o table_hachage.o liste.o cellule.o

prog_table_hachage : $(OBJETS)
	$(CC) -o prog_table_hachage $(OBJETS)

prog_table_hachage.o : prog_table_hachage.c table_hachage.h liste.h cellule.h
	$(CC) -c prog_table_hachage.c

table_hachage.o : table_hachage.c table_hachage.h liste.h
	$(CC) -c table_hachage.c

liste.o : liste.c liste.h cellule.h
	$(CC) -c liste.c

cellule.o : cellule.c cellule.h
	$(CC) -c cellule.c

clean:
		rm prog_table_hachage $(OBJETS)
