CC = gcc -Wall -O3
OBJETS = main.o file.o sommet.o Liste_File.o graphe_File.o Cellule_File.o
test : $(OBJETS)
	$(CC) -o test $(OBJETS)
main.o : main.c file.h Liste_File.h Cellule_File.h graphe_File.h
	$(CC) -c main.c
file.o : file.c file.h sommet.h
	$(CC) -c file.c
sommet.o : sommet.c sommet.h
	$(CC) -c sommet.c
Liste_File.o : Liste_File.c Liste_File.h Cellule_File.h
	$(CC) -c Liste_File.c
Cellule_File.o : Cellule_File.c Cellule_File.h
	$(CC) -c Cellule_File.c
graphe_File.o : graphe_File.c graphe_File.h
	$(CC) -c graphe_File.c
clean:
	rm main $(OBJETS)