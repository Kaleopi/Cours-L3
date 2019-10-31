import java.lang.invoke.MethodHandles;

/**
 * Classe d'exemple illustrant l'utilisation de la classe Config.
 * @author Cyril Rabat
 * @version 20/10/2019
 */
public class Exemple {

    /**
     * Création d'un fichier de configuration par défaut.
     * @param nomFichier le nom du fichier
     * @return la configuration
     */
    public static Config creerFichierConfiguation(String nomFichier) {
        Config config = new Config(nomFichier, true);

        /**
         * #TODO#
         * À l'aide des méthodes ajouterValeur, ajouter les valeurs par défaut
         */
         config.ajouterValeur("adresse","127.0.0.1");
         config.ajouterValeur("port",1056);

        // Sauvegarde du fichier de configuration
        config.sauvegarder();

        return config;
    }


    public class ServeurUDP {

        // Le port d'écoute du serveur
        public static int portEcoute = 2025;

        public static void main(String[] args) {
            // Création de la socket
            DatagramSocket socket = null;
            try {
                socket = new DatagramSocket(portEcoute);
            } catch(SocketException e) {
                System.err.println("Erreur lors de la création de la socket : " + e);
                System.exit(-1);
            }

            // Création du message
            byte[] tampon = new byte[1024];
            DatagramPacket msg = new DatagramPacket(tampon, tampon.length);

            // Lecture du message du client
            System.out.println("En attente d'un message sur le port " + portEcoute);
            try {
                socket.receive(msg);
                String texte = new String(msg.getData(), 0, msg.getLength());
                System.out.println("Lu: " + texte);
            } catch(IOException e) {
                System.err.println("Erreur lors de la réception du message : " + e);
                System.exit(-1);
            }

            // Fermeture de la socket
            socket.close();
        }

    }


    /**
     * Fonction principale
     * @param args vide ou contient le nom du fichier de config
     */
    public static void main(String[] args) {
        // Vérification des arguments
        Config config;
        if(args.length == 0) {
            // Pas d'argument : on ouvre le fichier json par défaut (nom de la classe)

            String className = MethodHandles.lookup().lookupClass().getSimpleName() + ".json";
            if(Config.fichierExiste(className))
                config = new Config(className);
            else
                config = creerFichierConfiguation(className);
        }
        else {
            // Un argument : c'est le nom du fichier JSON de config à ouvrir/créer

            if(Config.fichierExiste(args[0]))
                config = new Config(args[0]);
            else
                config = creerFichierConfiguation(args[0]);
        }

        // Vérification des données dans le fichier de configuration

        /**
         * #TODO#
         * Utilisez les méthodes getString/getInt pour récupérer les données
         * et vérifier le bon fonctionnement de l'ensemble...
         */
         System.out.println("Fichier de config :\n\tadresse : "+config.getString("adresse")+"\n\tport : "+config.getInt("port"));
    }

}
