//EXERCICE 2 QUESTION 4
#include <string.h>

#define BOOLEEN int
#define VRAI 0
#define FAUX 1

BOOLEEN automate(char *chaine){
  int pos=0, etat=0, resultat=VRAI;
  while((resultat==VRAI)&&(pos<strlen(chaine))){
    switch(etat){
      case 0:
        if(chaine[pos]=='a'){
          etat=1;
        }
        else if{
          chaine[pos]!='b');
          resultat=FAUX;
        }
      break;
      case 1:
        if(chaine[pos]=='b'){
          etat=0;
        }
        else{
          resultat=FAUX;
      }
      break;
    }
    pos++;
  }
  if(etat==0){
    resultat=FAUX;
  }
  return resultat;
}

int main(int argc, char *argv[]){
  //VERIF PARAMETRES
  if(automate(argv[1])==VRAI){
    printf("%s accepté\n",argv[1]);
  }
  else{
    printf("%s non accepté\n",argv[1]);
  }
  return EXIT_SUCCESS;
}
