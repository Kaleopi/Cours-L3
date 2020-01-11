superHeros(darkevil).
superHeros(hulk).
superHeros(wolverine).

superVilain(jackhammer).
superVilain(ultron).
superVilain(scrambler).

superHV(X,Y):-superHeros(X),superVilain(Y).
duoSV(X,Y):-X\=Y,superVilain(X),superVilain(Y).


sommeValeursPaires(N,R):-N mod 2 = 0, R is R+N, sommeValeursPaires(N-1,R).
sommeValeursPaires(N,R):-N mod 2 \= 0, sommeValeursPaires(N-1,R).
% sommeValeursPaires(N,R):-N = 0, 
codage7(N):-number(N),N\=0,write(N), write(' en base 7 : '),write(N mod 7).