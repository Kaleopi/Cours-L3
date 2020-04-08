CODE_ALGO = jeux.json Exemple1.alg
CODE_C = code.c
NOM_EXECUTABLE = prog

exe : $(NOM_EXECUTABLE)
	./$(NOM_EXECUTABLE)

$(NOM_EXECUTABLE) : $(CODE_C)
	gcc -o $(NOM_EXECUTABLE) $(CODE_C)

$(CODE_C) : calculatrice
	./calculatrice $(CODE_ALGO) 

calculatrice : y.tab.o lex.yy.o liste.o
	gcc -o calculatrice y.tab.o lex.yy.o liste.o -lm -lfl
	
liste.o : 
	gcc -c liste.c liste.h

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
	rm -f liste.o
