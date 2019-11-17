retourner(pile,face).
retourner(face,pile).

%iteration(Xa,Ya,Za,Xb,Yb,Zb):-Xa="pile",Za="pile",Ya="face",retourner(Za,face),retourner(Ya,pile).
affichage(X,Y,Z):-write(X),write(" "),write(Y),write(" "),write(Z),write("\n").
iteration(Xa,Ya,Z,Xb,Yb,Z):-retourner(Xa,Xb),retourner(Ya,Yb).
iteration(Xa,Y,Za,Xb,Y,Zb):-retourner(Xa,Xb),retourner(Za,Zb).
iteration(X,Ya,Za,X,Yb,Zb):-retourner(Ya,Yb),retourner(Za,Zb).
jeuDePieces(X,Y,Z,R,R,R):-iteration(X,Y,Z,X1,Y1,Z1),iteration(X1,Y1,Z1,X2,Y2,Z2),iteration(X2,Y2,Z2,R,R,R),affichage(X,Y,Z),affichage(X1,Y1,Z1),affichage(X2,Y2,Z2),affichage(R,R,R).
