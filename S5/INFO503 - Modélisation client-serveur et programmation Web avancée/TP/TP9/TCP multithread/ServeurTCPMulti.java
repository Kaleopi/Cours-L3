import java.io.IOException;

import java.net.ServerSocket;
import java.net.Socket;

/**
 * Classe correspondant à un serveur TCP multithreadé.
 * Le client envoie la chaine 'Bonjour' et lit une réponse de la part du serveur.
 * Le client envoie ensuite la chaine 'Au revoir' et lit une réponse.
 * Le numéro de port d'écoute est spécifié par l'attribut portEcoute.
 * @author Cyril Rabat
 * @version 21/10/2019
 */
public class ServeurTCPMulti {

    public static final int portEcoute = 5001;

    public static void main(String[] args) {
        // Création de la socket serveur
        ServerSocket socketServeur = null;
        try {    
            socketServeur = new ServerSocket(portEcoute);
        } catch(IOException e) {
            System.err.println("Création de la socket impossible : " + e);
            System.exit(-1);
        }

        // Attente des connexions des clients
        try {
            Socket socketClient;
            while(true) {
                System.out.println("En attente d'une connexion...");
                socketClient = socketServeur.accept();
                ThreadConnexion t = new ThreadConnexion(socketClient);
                t.start();
            }
        } catch(IOException e) {
            System.err.println("Erreur lors de l'attente d'une connexion : " + e);
            System.exit(-1);
        }
    
        // Fermeture de la socket
        // Le code suivant n'est pas exécuté à cause de la boucle infinie
        try {
            socketServeur.close();
        } catch(IOException e) {
            System.err.println("Erreur lors de la fermeture de la socket : " + e);
            System.exit(-1);
        }
    }

}