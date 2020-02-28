#include "fonctionsControleur.h"

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
 * créer la file de message si elle n'existe pas
 * @param cle_msg
 * @return identifiant de la file de messages associée à la clé cle_msg.
 */
int creer_file(key_t cle_msg){
    int msqid;
    if((msqid = msgget(cle_msg, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL)) == -1) {
        if(errno == EEXIST)
            fprintf(stderr, "Erreur : file (cle=%d) existante\n", cle_msg);
        else if(errno == EACCES)
            fprintf(stderr, "Erreur : accès interdit à la file (cle=%d)",cle_msg);
        else if(errno == ENOENT)
            fprintf(stderr, "Erreur : pas de file associée à la clé (cle=%d)", cle_msg);
        else if(errno == ENOSPC)
            fprintf(stderr, "Erreur : nombre de files (cle=%d) maximum atteinte",cle_msg);
        else
           perror("Erreur inconnue lors de la creation de la file ");
    exit(EXIT_FAILURE);
  }
  return msqid;
}

/**
 *  affiche un message d'erreur pour mauvaise utilisation de la commande ./controleur
 */
void error_args(){
    printf("[ERROR ARGS]\n\t./controleur nomFichier.bin nbVoitureMax KEY_MSG KEY_SHM KEY_SEM\n\t\tnomFichier.bin : nom du fichier contenant les informations de la carte\n\t\tnbVoitureMax : nombre maximum de voitures\n\t\tKEY_MSG : clé de la file de messages\n\t\tKEY_SHM : clé de la mémoire partagée\n\t\tKEY_SEM : clé du tableau de sémaphores\n\nExemple d'utilisation : \n\t./controleur reims.bin 10 1056 2056 3056\n");
}
