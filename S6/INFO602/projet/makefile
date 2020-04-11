projet : y.tab.o lex.yy.o
	gcc -o projet y.tab.o lex.yy.o -lm -lfl

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

y.tab.c y.tab.h : projet.yacc.y
	yacc -vd projet.yacc.y

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

lex.yy.c : projet.lex
	flex projet.lex

clean:
	rm -f y.tab.*
	rm -f lex.yy.*
	rm -f projet projet.exe
	rm -f *~
	rm -f *.stackdump
	rm -f y.output
