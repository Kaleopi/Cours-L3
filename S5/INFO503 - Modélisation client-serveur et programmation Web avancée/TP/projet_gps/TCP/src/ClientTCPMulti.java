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

/**
 * Classe correspondant à un client TCP.
 * Le client envoie la chaine 'Bonjour' et lit une réponse de la part du serveur.
 * Le client envoie ensuite la chaine 'Au revoir' et lit une réponse.
 * Le port d'écoute du serveur est spécifié par l'attribut portEcoute.
 * @author Cyril Rabat
 * @version 21/10/2019
 */
public class ClientTCPMulti {

    public static Config creerFichierConfiguration(String nomFichier) {
        Config config = new Config(nomFichier, true);
        /**
         * #TODO# À l'aide des méthodes ajouterValeur, ajouter les valeurs par défaut
         */
        config.ajouterValeur("adresse", "127.0.0.1");
        config.ajouterValeur("port", 5001);
        // Sauvegarde du fichier de configuration
        config.sauvegarder();
        return config;
    }

    public static int portEcoute;
    public static String adresse;
    public static Config config;

    public static void main(String[] args) {
        int choix = 0;
        String login = "", password = "", message="";
        Scanner clavier = new Scanner(System.in);
        BufferedReader input = null;
        PrintWriter output = null;
        Socket socket = null;

        // Vérification des arguments
        if (args.length == 0) {
            // Pas d'argument : on ouvre le fichier json par défaut (nom de la classe)

            // String className = MethodHandles.lookup().lookupClass().getSimpleName() +
            // ".json";
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

        do {
            System.out.println("Bienvenue sur SportGPS\n" + "1) Se connecter\n" + "2) Quitter\n" + "Votre choix ? ");
            choix = clavier.nextInt();
            clavier.nextLine();

            if (choix == 1) {
                System.out.println("Login ? : ");
                login = clavier.nextLine();
                System.out.println("Password ? : ");
                password = clavier.nextLine();
                Utilisateur user = new Utilisateur(login, password);
                GestionnaireUtilisateurs gest = new GestionnaireUtilisateurs("users.json");
                Activite act = new Activite();
                // gest.addUser("thomas","gigout");
                boolean trouve = gest.search(user.getLogin(), user.getPassword());
                int choixx = 0;
                if (trouve) {
                    System.out.println("Bienvenue " + user.getLogin() + " !");
                    do {
                        System.out.println("1) Commencer l'activite\n2) Quitter");
                        choixx = clavier.nextInt();
                        clavier.nextLine();
                        if (choixx == 1) {
                            act.setIdSportif(user.getLogin());
                            act.startActivity();
                            String longitude = "", latitude = "";
                            int ok = 0;
                            do {
                                System.out.println(
                                        "1) Nouvelle coordonnee\n2) Envoyer et quitter\n3) Annuler et quitter");
                                ok = clavier.nextInt();
                                clavier.nextLine();
                                if (ok == 1) {
                                    GPS coord = new GPS();
                                    System.out.println("Saisie nouvelle coordonnee \nLongitude : ");
                                    longitude = clavier.nextLine();
                                    System.out.println("Latitude : ");
                                    latitude = clavier.nextLine();
                                    Timestamp time = new Timestamp(System.currentTimeMillis());
                                    String timestamp = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss").format(time);
                                    coord.setLongitude(longitude);
                                    coord.setLatitude(latitude);
                                    coord.setTimestamp(timestamp);
                                    act.addCoord(coord);
                                } else if (ok == 2) {
                                    act.stopActivity();
                                    System.out.println("Envoi des donnees de l'activite...");
                                    message = act.toJSON().toString();
                                    // System.exit(0);
                                } else if (ok == 3) {
                                    System.out.println("Envoi des donnees annule");
                                    System.exit(0);
                                } else {
                                    System.out.println("Veuillez entrer un chiffre parmi la liste");
                                }
                            } while (ok == 1);
                        } else if (choixx == 2) {
                            System.out.println("Creation activite annulee");
                            System.exit(0);
                        } else {
                            System.out.println("Veuillez entrer un chiffre parmi la liste");
                        }
                    } while (choixx < 1 || choixx > 2);
                    choix = 2;
                } else {
                    System.out.println("Desole, vous n'etes pas inscrit.");
                }
            } else if (choix == 2) {
                System.out.println("Connexion annulee");
                System.exit(0);
            } else {
                System.out.println("Veuillez entrer un chiffre parmi la liste.");
            }
            choix = 1;
            // Création de la socket

            try {
                socket = new Socket("localhost", portEcoute);
            } catch(UnknownHostException e) {
                System.err.println("Erreur sur l'hôte : " + e);
                System.exit(-1);
            } catch(IOException e) {
                System.err.println("Création de la socket impossible : " + e);
                System.exit(-1);
            }
    
            // Association d'un flux d'entrée et de sortie à la socket
            try {
                input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                output = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
            } catch(IOException e) {
                System.err.println("Association des flux impossible : " + e);
                System.exit(-1);
            }
    
            // Envoi des données
            System.out.println("Envoi: " + message);
            output.println(message);
    
            // Lecture des données
            try {
                message = input.readLine();
            } catch(IOException e) {
                System.err.println("Erreur lors de la lecture : " + e);
                System.exit(-1);
            }
            System.out.println("Lu: " + message);
    
            // Envoi de 'Au revoir'
            message = "Au revoir";
            System.out.println("Envoi: " + message);
            output.println(message);
    
            // Lecture de 'Au revoir'
            try {
                message = input.readLine();
            } catch(IOException e) {
                System.err.println("Erreur lors de la lecture : " + e);
                System.exit(-1);
            }
            System.out.println("Lu: " + message);
        } while (choix != 2);


        // Fermeture des flux et de la socket
        try {
            input.close();
            output.close();
            socket.close();
        } catch(IOException e) {
            System.err.println("Erreur lors de la fermeture des flux et de la socket : " + e);
            System.exit(-1);
        }
    }

}