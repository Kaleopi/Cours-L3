#include "fonctionsControleur.h"

void charger_carte(char *nom_fichier, WINDOW * bordure, WINDOW * sim, carte_t *carte){
    int i = 0, fd, j = 0, v = 0;
    size_t taille;

    char *nom_decor;


    /* ouverture du fichier */
    if((fd = open(nom_fichier, O_RDONLY)) == -1){
        printw("Erreur lors de l'ouverture du fichier \"%s\"", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* taille nom décor */
    if((v = read(fd, &taille, sizeof(size_t))) == -1){
        /* Gestion d'erreur */
        printw("Erreur lors de la lecture du fichier \"%s\"", strerror(errno));
        exit(EXIT_FAILURE);
    }
    nom_decor = malloc(sizeof(char)*taille);

    /* nom décor */
    if((v = read(fd, nom_decor, taille*sizeof(char))) == -1){
        /* Gestion d'erreur */
        printw("Erreur lors de la lecture du fichier \"%s\"", strerror(errno));
        exit(EXIT_FAILURE);
    }
    mvwprintw(bordure,0,1, nom_decor);

    /* matrice */
    if ((v = read(fd, carte->carte, COL*LINE*sizeof(char)+30)) == -1){
        /* Gestion d'erreur */
        printw("Erreur lors de la lecture du fichier \"%s\"", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Affichage matrice */
    for(i = 0; i<LINE; i++){
        for(j = 0; j<COL; j++){
            if((carte->carte[i][j]) == 0){
                wattron(sim, COLOR_PAIR(0));
                mvwprintw(sim, i+1, j, " ");
                wattroff(sim, COLOR_PAIR(0));
            }
            else if((carte->carte[i][j]) == 1){
                wattron(sim, COLOR_PAIR(1));
                mvwprintw(sim, i+1, j, " ");
                wattroff(sim, COLOR_PAIR(1));
            }
            else{
                wattron(sim, COLOR_PAIR(2));
                mvwprintw(sim, i+1, j, " ");
                wattroff(sim, COLOR_PAIR(2));
            }
        }
    }
}

void afficher_carte(carte_t *carte){
    int i;
    int j;
    for(i=0 ; i<LINE ; i++){
        for(j=0 ; j<COL ; j++){
            printf("%d",(int)carte->carte[i][j]);
        }
        printf("\n");
    }
}

int creer_file(key_t cle_msg){
    int msqid;
    if((msqid = msgget(cle_msg, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
        if(errno == EEXIST)
            fprintf(stderr, "Erreur : file (cle=%d) existante\n", CLE_MSG);
        else
           perror("Erreur lors de la creation de la file ");
    exit(EXIT_FAILURE);
  }
  return msqid;
}