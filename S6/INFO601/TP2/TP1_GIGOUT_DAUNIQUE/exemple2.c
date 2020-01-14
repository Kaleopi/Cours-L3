/**
 * Ce programme illustre le fonctionnement des infos ncurses.
 * Le programme cree une fenêtre, la colorie dans une couleur.
 * Pour quitter le programme, l'utilisateur doit cliquer dans la info.
 * @author Cyril Rabat
 * @version 18/01/2017
 **/

#include <stdlib.h>     /* Pour EXIT_FAILURE */
#include <ncurses.h>    /* Pour printw, attron, attroff, COLOR_PAIR, getch */
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h> 
#include <fcntl.h> 
#include "ncurses.h"

#define LARGEUR 17      /* Largeur de la fenêtre */
#define HAUTEUR 5      /* Hauteur de la fenêtre */
#define POSX    20      /* Position horizontale de la fenêtre */
#define POSY    5       /* Position verticale de la fenêtre */
#define LIGNE 30  /*ligne*/

void obstacles(WINDOW* w){
    /*int[15][30] tab = {0};*/
    for(int i =0 ;i<15;i++){
      for(int j =0 ;j<30;j++){
      int random=rand() % 5;
      if (random==1)
         wattron(w,COLOR_PAIR(2));
          mvwprintw(w,i,j," ");
         wattroff(w,COLOR_PAIR(2));
      
    }
    }
}

int nbflocondplus(int NBFLOCOND){
    NBFLOCOND++;
    return NBFLOCOND;
}

int exists(const char *fname)
{
  int i=0;
   int ret=0;
    int file;
    if ((file = open(fname,O_CREAT|O_RDONLY|O_WRONLY|O_APPEND,0777)))
    {
      off_t old=lseek(file,0,SEEK_CUR);
      off_t end=lseek(file,0,SEEK_END);

    while(old!=end){
        old =lseek(file,i,SEEK_SET);
        i++;
      }
        close(file);
        return i-1;
    }else{

      char res[100];
      printf ("entrez une val");
      int bouya=scanf("%s",res);
      if (bouya!=0){
        ret=write(file,res,sizeof(res));
      }
      
      return ret;
    }

    
}

int main() {
  char* kek="test";
  int taille=0;

    taille=exists(kek);
  
  int i;
  int NBFLOCOND=0;
  WINDOW* info;
  WINDOW* sous_info;
  WINDOW* simulation;
  WINDOW* sous_simulation;
    WINDOW* etat;
  WINDOW* sous_etat;
  int  cpt=0;

  /* Initialisation de ncurses */
  ncurses_initialiser();
  ncurses_souris();
  ncurses_couleurs(); 
  
  /* Vérification des dimensions du terminal */
  if((COLS < POSX + LIGNE) || (LINES < POSY + HAUTEUR)) {
      ncurses_stopper();
      fprintf(stderr, 
              "Les dimensions du terminal sont insufisantes : l=%d,h=%d au lieu de l=%d,h=%d\n", 
              COLS, LINES, POSX + LIGNE, POSY + HAUTEUR);
      exit(EXIT_FAILURE);
  }  
  
  /* Creation de la fenêtre */
  info = newwin(HAUTEUR, LIGNE+30, POSY, POSX);
  box(info, 0, 0);
  sous_info = subwin(info, HAUTEUR - 2, LIGNE +28, POSY + 1, POSX + 1);
  scrollok(sous_info, TRUE);
  /*Création simulation*/
  simulation = newwin(LARGEUR, LIGNE, POSY+5, POSX);
  box(simulation, 0, 0);
  sous_simulation = subwin(simulation,LARGEUR - 2, LIGNE - 2, POSY + 6, POSX + 1);
  obstacles(sous_simulation);
  scrollok(sous_simulation, TRUE);
    /*Création etat*/
  etat = newwin(LARGEUR-9, LIGNE, POSY+5, POSX+30);
  box(etat, 0, 0);
  sous_etat = subwin(etat,LARGEUR - 11, LIGNE - 2, POSY + 6, POSX + 30);

  mvwprintw(sous_etat,0,1,"taille fichier : %d ",taille);
  wattron(sous_etat,COLOR_PAIR(2));
  mvwprintw(sous_etat,2,1,"Flocons : %d ",NBFLOCOND);
  wattron(sous_etat,COLOR_PAIR(2));
  mvwprintw(sous_etat,3,1," ");
  wattroff(sous_etat,COLOR_PAIR(2));
  scrollok(sous_etat, TRUE);
  wattron(sous_etat,COLOR_PAIR(1));
  mvwprintw(sous_etat,5,1," ");
  wattroff(sous_etat,COLOR_PAIR(1));
  scrollok(sous_etat, TRUE);
  mvwprintw(sous_etat,3,2,"   Obstacle ");
    mvwprintw(sous_etat,5,2,"   Flocon ");
  /* Création d'un cadre */
  wrefresh(info);
  wrefresh(sous_info);
  /*cadre simulation*/
  wrefresh(simulation);
  wrefresh(sous_simulation);
    /*cadre etat*/
  wrefresh(etat);
  wrefresh(sous_etat);
  
  /* Attente d'un clic dans la fenêtre ou de F2 */
  printw("Cliquez dans la info ; pressez F2 pour quitter...");  
  while((i = getch()) != KEY_F(2)) {
         if(cpt != 1) 
                wprintw(sous_info, "\n");
                NBFLOCOND=nbflocondplus(NBFLOCOND);
                wprintw(sous_info, "Nouveau Flocon : colonne  %d", NBFLOCOND);
                wrefresh(sous_info);
                
            }

  /*comptage*/ 

  /* Suppression des fenêtres */
  delwin(sous_info);
  delwin(info);
delwin(sous_simulation);
  delwin(simulation);
  delwin(sous_etat);
  delwin(etat);
  /* Arrêt de ncurses */
  ncurses_stopper();

  return EXIT_FAILURE;
}