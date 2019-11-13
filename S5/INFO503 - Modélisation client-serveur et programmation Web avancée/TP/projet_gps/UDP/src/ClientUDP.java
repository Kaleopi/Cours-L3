import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketException;
import java.net.InetAddress;
import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.lang.invoke.MethodHandles;
import java.net.UnknownHostException;
import java.sql.Timestamp;
import java.util.Scanner;
import org.json.*;
import java.util.Date;
import java.text.SimpleDateFormat;


public class ClientUDP {
    /**
     * Création d'un fichier de configuration par défaut.
     * 
     * @author Cyril Rabat
     * @version 20/10/2019
     * @param nomFichier le nom du fichier
     * @return la configuration
     */
    public static Config creerFichierConfiguration(String nomFichier) {
        Config config = new Config(nomFichier, true);
        /**
         * #TODO# À l'aide des méthodes ajouterValeur, ajouter les valeurs par défaut
         */
        config.ajouterValeur("adresse", "127.0.0.1");
        config.ajouterValeur("port", 2025);
        // Sauvegarde du fichier de configuration
        config.sauvegarder();
        return config;
    }

    // Le port d'écoute du serveur
    public static int portEcoute;
    public static String adresse;
    public static Config config;

    public static void main(String[] args) {
        int choix = 0;
        String login="",password="";
        Scanner clavier = new Scanner(System.in);

        // Vérification des arguments
        if (args.length == 0) {
            // Pas d'argument : on ouvre le fichier json par défaut (nom de la classe)

            // String className = MethodHandles.lookup().lookupClass().getSimpleName() + ".json";
            String className = "config.json";
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
        adresse = config.getString("adresse");


        do{
            System.out.println("Bienvenue sur SportGPS\n"+
            "1) Se connecter\n"+
            "2) Quitter\n"+
            "Votre choix ? ");
            choix = clavier.nextInt();clavier.nextLine();

            if(choix==1){
                System.out.println("Login ? : ");
                login = clavier.nextLine();
                System.out.println("Password ? : ");
                password = clavier.nextLine();
                Utilisateur user = new Utilisateur(login,password);
                GestionnaireUtilisateurs gest = new GestionnaireUtilisateurs("users.json");
                // gest.addUser("thomas","gigout");
                boolean trouve = gest.search(user.getLogin(),user.getPassword());
                if(trouve){
                    System.out.println("Bienvenue "+user.getLogin()+" !\n");
                    Activite act = new Activite();
                    act.setIdSportif(user.getLogin());
                    act.startActivity();
                    choix = 2;
                }
            }
            else if(choix == 2){
                System.exit(0);;
            }
            else{
                System.out.println("Veuillez entrer un chiffre parmi la liste.");
            }
        }while(choix!=2);
        

        
        DatagramSocket socket = null;
        // Création de la socket
        try {
            socket = new DatagramSocket();
        } catch (SocketException e) {
            System.err.println("Erreur lors de la création de la socket : " + e);
            System.exit(-1);
        }

        // Création du message
        DatagramPacket msg = null;
        try {
            InetAddress adresse = InetAddress.getByName(null);
            String message = "Bonjour";
            byte[] tampon = message.getBytes();
            msg = new DatagramPacket(tampon, tampon.length, adresse, portEcoute);

        } catch (UnknownHostException e) {
            System.err.println("Erreur lors de la création du message : " + e);
            System.exit(-1);
        }

        // Envoi du message
        try {
            socket.send(msg);
        } catch (IOException e) {
            System.err.println("Erreur lors de l'envoi du message : " + e);
            System.exit(-1);
        }
        System.out.println("Message envoyé au serveur.");

        // Fermeture de la socket
        socket.close();
    }

}
