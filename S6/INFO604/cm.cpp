Exercice 1:
1)  a) Porportion des données restantes après compression
    b) facteur par lequel la taille de données à été compressée
    c) pourcentage de place gagnée par la compression

2)  a) Sc/Si = 98304 / 131072 = 0.75
    b) Si/Sc = 131072 / 98304 = 1.3
    c) Si-Sc/Si = 32768/131072 = 25%

4) Si = Sc / t 
      = 145260 / 0.1 = 1452 000 octets
5) p = Si-Sc / Si <=> Sc = (1-p)Si 
                      Si = Sc/(1-p)
        Si = 145250/1-0.1 = 161400 octets 

Exercice 2: 
Si<Sc 
1) T > 1
2) f<1
3) p<0

Exercice 3: 
1) #Bp = 2^8p
2) #B<=p = 2^8 + 2^2.8 + ... + 2^(p-1)8

Exercice 4: 
1) Etre sur des multiples du sizeof pour l'adresse des types élémentaireS et du max élémenatires pour les types composés.alignas
2) Un processeur 32/64 buts est optimisé pour manipuler des données de 32/64 bits. L'utilisation de mots plus courts ne sont pas passible : la vectorisation (-> manuellement).alignas

