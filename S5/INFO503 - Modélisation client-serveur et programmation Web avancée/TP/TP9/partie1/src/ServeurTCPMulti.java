import java.io.IOException;
import java.lang.invoke.MethodHandles;
import java.net.ServerSocket;
import java.net.Socket;
import org.json.*;

/**
 * Classe correspondant à un serveur TCP multithreadé.
 * Le client envoie la chaine 'Bonjour' et lit une réponse de la part du serveur.
 * Le client envoie ensuite la chaine 'Au revoir' et lit une réponse.
 * Le numéro de port d'écoute est spécifié par l'attribut portEcoute.
 * @author Cyril Rabat
 * @version 21/10/2019
 */

    public class ServeurTCPMulti {
        public static Config creerFichierConfiguration(String nomFichier) {
            Config config = new Config(nomFichier, true);

            /**
             * #todo# À l'aide des méthodes ajouterValeur, ajouter les valeurs par défaut
             */
            config.ajouterValeur("adresse", "127.0.0.1");
            config.ajouterValeur("port", 5001);

            // Sauvegarde du fichier de configuration
            config.sauvegarder();

            return config;
        }
        public static Config config;
        public static int portEcoute;

        public static void main(String[] args) {
            // Vérification des arguments
            Config config;
            if (args.length == 0) {
                // Pas d'argument : on ouvre le fichier json par défaut (nom de la classe)

                String className = MethodHandles.lookup().lookupClass().getSimpleName() + ".json";
                if (Config.fichierExiste(className))
                    config = new Config(className);
                else
                    config = creerFichierConfiguration(className);
            } else {
                // Un argument : c'est le nom du fichier JSON de config à ouvrir/créer

                if (Config.fichierExiste(args[0]))
                    config = new Config(args[0]);
                else
                    config = creerFichierConfiguration(args[0]);
            }
            portEcoute = config.getInt("port");
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
