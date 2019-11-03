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
import org.json.*;

/**
 * Classe correspondant à un client Http.
 * L'utilisateur doit saisir des données à envoyer puis celles-ci sont envoyées au serveur Http.
 * La réponse du serveur est ensuite affichée.
 * @author Cyril Rabat
 * @version 2019/10/11
 */
public class Client{

    public static void main(String[] args) {
        Scanner clavier = new Scanner(System.in);
        String listeDonnees = "", titre, donnees, login, mdp, mode="";
        int choix;

        // Menu pour saisir les données à envoyer en POST
        do {
            System.out.println("1) Se connecter");
            System.out.println("2) S'inscrire");
            System.out.println("3) Quitter");
            System.out.print("Votre choix : ");
            choix = clavier.nextInt();clavier.nextLine();

            if(choix == 1) {
                mode = "connexion";
                System.out.print("Login : ");
                login = clavier.nextLine();
                System.out.print("Mot de passe : ");
                mdp = clavier.nextLine();
                if(listeDonnees != ""){
                    listeDonnees += "&";
                }
                
                Utilisateur user = new Utilisateur(login,mdp);
                JSONObject json = user.toJSON();
                
                // Encodage des données
                try {
                    listeDonnees = URLEncoder.encode(""+json, "UTF-8") + "&mode="+URLEncoder.encode(""+mode, "UTF-8");
                    
                } catch(UnsupportedEncodingException e) {
                    System.err.println("Erreur lors de l'encodage : " + e);
                    System.exit(-1);
                }
            }
            if(choix == 2){
                mode = "inscription";
                System.out.print("Login : ");
                login = clavier.nextLine();
                System.out.print("Mot de passe : ");
                mdp = clavier.nextLine();
                if (listeDonnees != "") {
                    listeDonnees += "&";
                }

                Utilisateur user = new Utilisateur(login, mdp);
                JSONObject json = user.toJSON();

                // Encodage des données
                try {
                    listeDonnees = URLEncoder.encode("" + json, "UTF-8") + "&mode="
                            + URLEncoder.encode("" + mode, "UTF-8");

                } catch (UnsupportedEncodingException e) {
                    System.err.println("Erreur lors de l'encodage : " + e);
                    System.exit(-1);
                }
            }
        }while(choix != 3);
            
            // Mise en forme de l'URL
            URL url = null;
            try {
                url = new URL("http://localhost:80/index.php");
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
                writer.write("donnees="+listeDonnees);
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
    }
}
