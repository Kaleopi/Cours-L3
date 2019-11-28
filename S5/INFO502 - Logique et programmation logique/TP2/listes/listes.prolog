affiche([]).
affiche([X|L]):-
    write(X), write(" "),affiche(L).
afficheR([X|L]):-
    afficheR(L),write(X),write(' ').

creeListeTroisElements(A,B,C,[A,B,C]).
creeListeTroisElements(A,B,C,Z):-
    Z=[A,B,C],
    affiche(Z).

taille([],0).
taille([X|L],T):-taille(L,TsL), T is TsL+1.
