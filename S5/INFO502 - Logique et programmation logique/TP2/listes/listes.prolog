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
taille([_|L],T):-
    taille(L,TsL), T is TsL+1.

somme([],0).
somme([X|L],S):-
    somme(L,Ss), S is Ss+X.

sommeSE([],0).
sommeSE([X|L],S):-
    number(X), somme(L,SsL), S is SsL+X.
sommeSE([X|L],S):-
    not(number(X)),somme(L,S).

search(E,[E|_]).
search(E,[T|Q]):-
    E \= T, search(E,Q).

myConcat([],L,L).
myConcat([X|L1],L2,[X|L3]):-
    myConcat(L1,L2,L3).

min([X],X).
min([X|L],X):-L\=[],min(L,ML),X<ML.
min([X|L],ML):-L\=[],min(L,ML),X>ML.


minI([X|L],R):-minI(L,X,R).
minI([],M,M).
minI([X|L],M,R):-X<M,minI(L,X,R).
minI([X|L],M,R):-X>M,minI(L,M,R).

concatTrie([],L,L).
concatTrie(L,[],L).

concatTrie([X|L1],[Y|L2],[X|L3]):-X<Y, concatTrie(L1, [Y|L2], L3).
concatTrie([X|L1],[Y|L2],[Y|L3]):-X>=Y, concatTrie([X|L1], L2, L3).