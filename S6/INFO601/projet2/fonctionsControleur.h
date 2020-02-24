void charger_carte(char *nom_fichier, WINDOW * fen_sim){

    int i = 0, fd, j = 0, v = 0;
    size_t taille;

    char nom_decor[21];

    /* Ouverture du fichier */
    if((fd = open(nom_fichier, O_RDONLY)) == -1){
        printf("Erreur lors de l'ouverture du fichier \"%s\"", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Taille nom décor */
    if((v = read(fd, &taille, sizeof(size_t))) == -1){
        /* Gestion d'erreur */
        printf("Erreur lors de la lecture du fichier \"%s\"", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Nom décor */
    if((v = read(fd, nom_decor, taille*sizeof(char))) == -1){
        /* Gestion d'erreur */
        printf("Erreur lors de la lecture du fichier \"%s\"", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Matrice */
    if ((v = read(fd, grille, COL*LINE*sizeof(char)+30)) == -1){
        /* Gestion d'erreur */
        printf("Erreur lors de la lecture du fichier \"%s\"", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* Affichage matrice */
    for(i = 0; i < LINE; i++){
        for(j = 0; j<COL; j++){
            if(((int)grille[i][j]) == 1){
                wattron(fen_sim, COLOR_PAIR(2));
                mvwprintw(fen_sim, i+1, j, " ");
                wattroff(fen_sim, COLOR_PAIR(2));
            }
            else if(((int)grille[i][j]) == 0){
                wattron(fen_sim, COLOR_PAIR(0));
                mvwprintw(fen_sim, i+1, j, " ");
                wattroff(fen_sim, COLOR_PAIR(0));
            }
        }
    }
    wrefresh(fen_sim);
}