Exercice 1:
1) Grammaire ambigue : deux arbres syntaxiques différents
1+1+1
E|- E+E |- 1+E |- 1+E+E |- 1+1+E |- 1+1+1
                        |- 1+E+1 |- 1+1+1         même arbre pour les trois
        |- E+E+E |- 1+E+E |- 1+1+E |- 1+1+1

E |- E+E |- E+1 |- E+E+1 |- E+1+1 |- 1+1+1        arbre différent

2) Proposez une grammaire non ambigue :
E -> E+1 | 1
E -> E+1 |- E+1+1 |- 1+1+1

Exercice 2:
1) feuille

2)  B -> B ou C|C
    C -> C et D|D
    D -> id|E
    E -> vrai|faux

Exercice 3:
