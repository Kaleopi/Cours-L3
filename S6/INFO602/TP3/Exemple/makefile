calculatrice : y.tab.o lex.yy.o
	gcc -o calculatrice y.tab.o lex.yy.o -lm -lfl

y.tab.o : y.tab.h y.tab.c
	gcc -c y.tab.c

y.tab.c y.tab.h : calculatrice.yacc.y
	yacc -vd calculatrice.yacc.y

lex.yy.o : lex.yy.c y.tab.h
	gcc -c lex.yy.c

lex.yy.c : calculatrice.lex 
	flex calculatrice.lex

clean:
	rm -f y.tab.*
	rm -f lex.yy.*
	rm -f calculatrice calculatrice.exe
	rm -f *~
	rm -f *.stackdump