// javac -d .\classes\ -sourcepath .\src\ -cp .\lib\json-20190722.jar .\src\*.java
// java -cp ".\classes\;.\lib\json-20190722.jar" file

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
import java.util.Scanner;
import org.json.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;

/**
 * Classe correspondant à un serveur UDP. La chaine de caractères "Bonjour" est
 * envoyée au serveur.
 * 
 * @author Cyril Rabat
 * @version 20/10/2019
 */
public class ServeurUDP {
    /**
    *Création d'un fichier
    de configuration
    par défaut.**
    @author
    Cyril Rabat*
    @version 20/10/2019
     * @param nomFichier le
    nom du fichier*@return
    la configuration*/

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
        Scanner clavier = new Scanner(System.in);
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

        // Création de la socket
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket(portEcoute);
        } catch (SocketException e) {
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
            JSONObject json = new JSONObject(texte);
            String nom = json.getString("idSportif");

            File fs = new File("./activites/"+nom+"Activite.json");
            FileWriter fr = null;
            try {
                fr = new FileWriter(fs);
                fr.write(texte);
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {
                    fr.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } catch (IOException e) {
            System.err.println("Erreur lors de la réception du message : " + e);
            System.exit(-1);
        }

        // Fermeture de la socket
        socket.close();
    }

}
