pgcdTest(X,Y,R):-number(X),number(Y),pgcd(X,Y,R).
pgcd(X,X,X).
pgcd(X,Y,R):-X<Y,pgcd(Y,X,R).
pgcd(X,Y,Y):-X>Y,Reste is X mod Y,Reste==0.
pgcd(X,Y,R):-X>Y,Reste is X mod Y,Reste\==0,pgcd(Y,Reste,R).


fiboTest(M,R),number(M),fibo(M,R).
fibo(M,R):-M==0,R=0.
fibo(M,R):-M==1,R=1.
fibo(M,R):-M==2,R=2.
fibo(M,R):-M>2,(fibo(M-1)+fibo(M-2)).
