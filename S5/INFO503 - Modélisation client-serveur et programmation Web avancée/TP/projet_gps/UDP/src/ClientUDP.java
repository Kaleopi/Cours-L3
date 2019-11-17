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

    public static DatagramSocket createSocket(){
        // Création de la socket
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket();
        } catch (SocketException e) {
            System.err.println("Erreur lors de la création de la socket : " + e);
            System.exit(-1);
        }
        return socket;
    }

    public static DatagramPacket createMsg(String donnee){
        // Création du message
        DatagramPacket msg = null;
        try {
            InetAddress adresse = InetAddress.getByName(null);
            String message = donnee;
            byte[] tampon = message.getBytes();
            msg = new DatagramPacket(tampon, tampon.length, adresse, portEcoute);

        } catch (UnknownHostException e) {
            System.err.println("Erreur lors de la création du message : " + e);
            System.exit(-1);
        }
        return msg;
    }

    public static void envoiMsg(DatagramSocket socket, DatagramPacket msg){
        // Envoi du message
        try {
            socket.send(msg);
        } catch (IOException e) {
            System.err.println("Erreur lors de l'envoi du message : " + e);
            System.exit(-1);
        }
        System.out.println("Message envoyé au serveur.");
    }

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
                Activite act = new Activite();
                // gest.addUser("thomas","gigout");
                boolean trouve = gest.search(user.getLogin(),user.getPassword());
                int choixx = 0;
                if(trouve){
                    System.out.println("Bienvenue "+user.getLogin()+" !");
                    do{
                        System.out.println("1) Commencer l'activite\n2) Quitter");
                        choixx = clavier.nextInt();clavier.nextLine();
                        if(choixx==1){
                            act.setIdSportif(user.getLogin());
                            act.startActivity();
                            String longitude="", latitude="";
                            int ok=0;
                            do{
                                System.out.println("1) Nouvelle coordonnee\n2) Envoyer et quitter\n3) Annuler et quitter");
                                ok = clavier.nextInt();clavier.nextLine();
                                if(ok==1){
                                    GPS coord = new GPS();
                                    System.out.println("Saisie nouvelle coordonnee \nLongitude : ");
                                    longitude = clavier.nextLine();
                                    System.out.println("Latitude : ");
                                    latitude = clavier.nextLine();
                                    coord.setLongitude(longitude);
                                    coord.setLatitude(latitude);
                                    Timestamp time = new Timestamp(System.currentTimeMillis());
                                    String timestamp = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss").format(time);
                                    coord.setLongitude(longitude);
                                    coord.setLatitude(latitude);
                                    coord.setTimestamp(timestamp);
                                    act.addCoord(coord);
                                }
                                else if(ok==2){
                                    act.stopActivity();
                                    System.out.println("Envoi des donnees de l'activite...");
                                    DatagramSocket socket = createSocket();
                                    DatagramPacket msg = createMsg(act.toJSON().toString());
                                    envoiMsg(socket, msg);
                                    socket.close();
                                    // System.exit(0);
                                }
                                else if(ok==3){
                                    System.out.println("Envoi des donnees annule");
                                    System.exit(0);
                                }
                                else{
                                    System.out.println("Veuillez entrer un chiffre parmi la liste"); 
                                }
                            }while(ok==1);
                        }
                        else if(choixx==2){
                            System.out.println("Creation activite annulee");
                            System.exit(0);
                        }
                        else{
                            System.out.println("Veuillez entrer un chiffre parmi la liste");
                        }
                    }while(choixx<1 || choixx>2);
                    choix = 2;
                }
                else{
                    System.out.println("Desole, vous n'etes pas inscrit.");
                }
            }
            else if(choix == 2){
                System.out.println("Connexion annulee");
                System.exit(0);
            }
            else{
                System.out.println("Veuillez entrer un chiffre parmi la liste.");
            }
            choix = 1;
        }while(choix!=2);

        DatagramSocket socketrecu = null;
        try {
            socketrecu = new DatagramSocket(2000);
        } catch (SocketException e) {
            System.err.println("Erreur lors de la création de la socket : " + e);
            System.exit(-1);
        }
1
        // Création du message
        byte[] tampon = new byte[1024];
        DatagramPacket msg = new DatagramPacket(tampon, tampon.length);

        // Lecture du message du client
        try {
            socketrecu.receive(msg);
            String texte = new String(msg.getData(), 0, msg.getLength());
            System.out.println("Lu: " + texte);
        }catch(IOException e){
            System.err.println("Erreur lors de la réception du message : " + e);
            System.exit(-1);
        }
        socketrecu.close();
    }
}
