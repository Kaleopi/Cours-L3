projet : y.tab.o lex.yy.o ncurses.o includes.o
	gcc -o projet y.tab.o lex.yy.o ncurses.o includes.o -lm -lfl -lncurses

y.tab.o : y.tab.h y.tab.c
	gcc -c -g y.tab.c

y.tab.c y.tab.h : projet.yacc.y
	yacc -vd projet.yacc.y

lex.yy.o : lex.yy.c y.tab.h
	gcc -c -g lex.yy.c

lex.yy.c : projet.lex
	flex projet.lex

includes.o : includes.h includes.c
	gcc -c -g includes.c

ncurses.o : ncurses.h ncurses.c
	gcc -c -g ncurses.c

clean:
	rm -f y.tab.*
	rm -f lex.yy.*
	rm -f projet projet.exe
	rm -f *~
	rm -f *.o
	rm -f *.stackdump
	rm -f y.output
