#include "fonctionsControleur.h"

/**
 * Ouvre la carte passée en paramètres pour l'appliquer au ncurses
 * @param nom_fichier nom du fichier .bin qui contient les infos de la carte
 * @param bordure WINDOW ncurses de la bordure (pour le titre)
 * @param sim WINDOW ncurses pour la fenêtre en elle même
 * @param carte carte du segment partagé à remplir avec les infos du fichier
 * @return void
 */
void charger_carte(char *nom_fichier, WINDOW * bordure, WINDOW * sim, carte_t *carte){
    int i = 0, fd, j = 0, v = 0;
    size_t taille;

    char *nom_decor;


    /* ouverture du fichier */
    if((fd = open(nom_fichier, O_RDONLY)) == -1){
        printf("Erreur lors de l'ouverture du fichier \"%s\"\n", strerror(errno));
        delwin(sim);
        delwin(bordure);
        ncurses_stopper();
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

/**
 * affiche la carte du segment partagé
 * @param carte carte_t du segment partagé
 * @return affichage
 */
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

/**
 * 
 * @param cle_msg
 * @return identifiant de la file de messages associée à la clé cle_msg.
 */
int creer_file(key_t cle_msg){
    int msqid;
    if((msqid = msgget(cle_msg, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
        if(errno == EEXIST)
            fprintf(stderr, "Erreur : file (cle=%d) existante\n", cle_msg);
        else
           perror("Erreur lors de la creation de la file ");
    exit(EXIT_FAILURE);
  }
  return msqid;
}

void error_args(){
    printf("[ERROR ARGS]\n\t./controleur nomFichier.bin nbVoitureMax KEY_MSG KEY_SHM KEY_SEM\n\t\tnomFichier.bin : nom du fichier contenant les informations de la carte\n\t\tnbVoitureMax : nombre maximum de voitures\n\t\tKEY_MSG : clé de la file de messages\n\t\tKEY_SHM : clé de la mémoire partagée\n\t\tKEY_SEM : clé du tableau de sémaphores\n\nExemple d'utilisation : \n\t./controleur reims.bin 10 1056 2056 3056\n");
}