CC=gcc -Wall -O3
OBJETS=main.o strangeFunction.o

main: $(OBJETS)
	$(CC) -o main $(OBJETS)

main.o : main.c strangeFunction.h
	$(CC) -c main.c

strangeFunction.o : strangeFunction.c
	$(CC) -c strangeFunction.c


clean:rm prog_liste $(OBJETS)
