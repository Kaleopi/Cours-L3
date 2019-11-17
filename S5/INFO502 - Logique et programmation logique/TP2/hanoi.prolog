hanoi(N):-hanoi(N,"gauche","milieu","droite").
hanoi(0,_,_,_).
hanoi(N,A,B,C):-
    N>0,N1 is N-1,
    hanoi(N1,A,C,B),
    write(A),write(" -> "),write(B),write("\n"),
    hanoi(N1,C,B,A).

hanoiCpt(N,I):-hanoiCpt(N,"gauche","milieu","droite",I).
hanoiCpt(0,_,_,_,0).
hanoiCpt(N,A,B,C,I):-
    N>0,N1 is N-1,
    hanoiCpt(N1,A,C,B,I1),
    write(A),write(" -> "),write(B),write("\n"),
    hanoiCpt(N1,C,B,A,I2),I is I1+I2+1,
    hanoiCpt(N, A, B, C, I).
