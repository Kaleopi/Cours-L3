male(pierre).
male(jules).
male(paul).
male(leo).
male(marc).
male(albert).
male(arthur).
male(leopold).

femelle(marie).
femelle(chloee).
femelle(cathy).
femelle(lea).
femelle(sophie).
femelle(julie).

enfant(jules,pierre).
enfant(jules,marie).
enfant(paul,pierre).
enfant(paul,marie).
enfant(lea,pierre).
enfant(lea,marie).
enfant(marc,chloee).
enfant(marc,jules).
enfant(sophie,chloee).
enfant(sophie,jules).
enfant(julie,chloee).
enfant(julie,jules).
enfant(albert,paul).
enfant(albert,cathy).
enfant(arthur,leo).
enfant(arthur,lea).
enfant(leopold,lea).
enfant(leopold,leo).

mari(pierre,marie).
mari(jules,chloee).
mari(paul,cathy).
mari(leo,lea).

pere(X,Y):-enfant(Y,X),male(X).
mere(X,Y):-enfant(Y,X),femelle(X).

grandpere(X,Y):-pere(X,Z),pere(Z,Y).
grandpere(X,Y):-pere(X,Z),mere(Z,Y).

parent(X,Y):-enfant(Y,X).

ancetre1(X,Y):parent(X,Y).
ancetre1(X,Y):-parent(X,Z),ancetre1(Z,Y).

ancetre2(X,Y):-parent(X,Y).
ancetre2(X,Y):-ancetre2(Z,Y),parent(X,Z).

famille(X):-famille(X,Y).
famille(X,Y):-pere(X,Y), write(X), write(" est le pere de "),write(Y),nl.
famille(X,Y):-mere(X,Y), write(X), write(" est la mere de "),write(Y),nl.
