import java.util.Scanner;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.URLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.net.MalformedURLException;
import java.io.File;
import java.lang.invoke.MethodHandles;

/**
 * Classe correspondant à un client Http.
 * L'utilisateur doit saisir des données à envoyer puis celles-ci sont envoyées au serveur Http.
 * La réponse du serveur est ensuite affichée.
 * @author Cyril Rabat
 * @version 2019/10/11
 */
public class ClientHttp {
    public static Config creerFichierConfiguration(String nomFichier) {
        Config config = new Config(nomFichier, true);

        /**
         * #todo# À l'aide des méthodes ajouterValeur, ajouter les valeurs par défaut
         */
        config.ajouterValeur("URLserveur", "http://localhost:8080/index.html");
        config.ajouterValeur("Chiffrement","RSA");
        config.ajouterValeur("cleprivee", "privee.bin");
        config.ajouterValeur("clepublique","publique.bin");

        // Sauvegarde du fichier de configuration
        config.sauvegarder();

        return config;
    }

    public static Config config;
    public static String urlserveur;
    public static String chiffrement;
    public static void main(String[] args) {
        Scanner clavier = new Scanner(System.in);
        // Vérification des arguments
        if (args.length == 0) {
            // Pas d'argument : on ouvre le fichier json par défaut (nom de la classe)

            String className = MethodHandles.lookup().lookupClass().getSimpleName() + "Config.json";
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
        urlserveur = config.getString("URLserveur");
        chiffrement = config.getString("Chiffrement");
        String priveeClient = "./CleClient/"+config.getString("cleprivee"), publiqueClient = "./CleClient/" +config.getString("clepublique"), priveeServeur = "./CleServeur/" +config.getString("cleprivee"), publiqueServeur = "./CleServeur/" + config.getString("clepublique");
        String[] filesClient = {priveeClient,publiqueClient}, filesServeur = {priveeServeur,publiqueServeur};
        File fpriveeClient = new File(priveeClient), fpubliqueClient = new File(publiqueClient), fpriveeServeur = new File(priveeServeur), fpubliqueServeur = new File(publiqueServeur);
        if(fpriveeClient.exists() && fpubliqueClient.exists()){
            System.out.println("Les fichiers de cle client existent.");
        }else{
            GenerationClesRSA.main(filesClient);
        }
        if (fpriveeServeur.exists() && fpubliqueServeur.exists()) {
            System.out.println("Les fichiers de cle serveur existent.");
        } else {
            GenerationClesRSA.main(filesServeur);
        }
        

        String listeDonnees = "", titre, donnees;
        int choix;
        
        // Menu pour saisir les données à envoyer en POST
        do {
            System.out.println("1) Pour ajouter des données en POST");
            System.out.println("2) Pour envoyer la requête");
            System.out.print("Votre choix : ");
            choix = clavier.nextInt();clavier.nextLine();
            
            if(choix == 1) {
                System.out.print("Nom du champ : ");
                titre = clavier.nextLine();
                System.out.print("Données      : ");
                donnees = clavier.nextLine();
                if(listeDonnees != "")
                    listeDonnees += "&";
                
                // Encodage des données
                try {
                    listeDonnees += URLEncoder.encode(titre, "UTF-8") + "=" + URLEncoder.encode(donnees, "UTF-8");
                } catch(UnsupportedEncodingException e) {
                    System.err.println("Erreur lors de l'encodage : " + e);
                    System.exit(-1);                    
                }
            }            
        } while(choix != 2);
        
        // Mise en forme de l'URL
        URL url = null;
        try { 
            url = new URL("http://localhost:8080/index.html"); 
        } catch(MalformedURLException e) { 
            System.err.println("URL incorrect : " + e);
            System.exit(-1);
        }
        
        // Etablissement de la connexion
        URLConnection connexion = null; 
        try { 
            connexion = url.openConnection(); 
            connexion.setDoOutput(true);
        } catch(IOException e) { 
            System.err.println("Connexion impossible : " + e);
            System.exit(-1);
        } 
        
        // Envoi de la requête
        try {
            OutputStreamWriter writer = new OutputStreamWriter(connexion.getOutputStream());
            writer.write(listeDonnees);
            writer.flush();
            writer.close();
        } catch(IOException e) {
            System.err.println("Erreur lors de l'envoi de la requete : " + e);
            System.exit(-1);            
        }        
        
        // Réception des données depuis le serveur
        donnees = ""; 
        try { 
            BufferedReader reader = new BufferedReader(new InputStreamReader( connexion.getInputStream())); 
            String tmp; 
            while((tmp = reader.readLine()) != null) 
                donnees += tmp; 
            reader.close(); 
        } catch(Exception e) { 
            System.err.println("Erreur lors de la lecture de la réponse : " + e);
            System.exit(-1);
        }
        
        // Affichage des données reçues
        System.out.println("Réponse du serveur : ");
        System.out.println(donnees);
        clavier.close();
    }
   
}