import java.util.ArrayList;
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
public class Client {

    public static void main(String[] args) {
        Scanner clavier = new Scanner(System.in);
        String listeDonnees = "", donnees = "", login, mdp, mode = "", reponse = "";
        int choix;

        // Menu pour saisir les données à envoyer en POST
        do {
            System.out.println("1) Se connecter");
            System.out.println("2) S'inscrire");
            System.out.println("3) Quitter");
            System.out.print("Votre choix : ");
            choix = clavier.nextInt();
            clavier.nextLine();

            if (choix == 1) {
                mode = "connexion";
                System.out.print("Login : ");
                login = clavier.nextLine();
                System.out.print("Mot de passe : ");
                mdp = clavier.nextLine();
                if (listeDonnees != "") {
                    listeDonnees += "&";
                }
                Utilisateur user = new Utilisateur(login, mdp);
                JSONObject json = user.toJSON();

                try {
                    listeDonnees = URLEncoder.encode("" + json, "UTF-8") + "&mode=" +
                        URLEncoder.encode("" + mode, "UTF-8");

                } catch (UnsupportedEncodingException e) {
                    System.err.println("Erreur lors de l'encodage : " + e);
                    System.exit(-1);
                }

                reponse = envoiDonnees("http://localhost:80/index.php", listeDonnees);

                if (reponse.equals("OKconnexion")) {
                    System.out.println("\nConnexion...");
                    System.out.println("Connecte !\n");
                    System.out.println("Menu sondages : ");
                    System.out.println("\t1) Creer un sondage");
                    System.out.println("\t2) Recuperer la liste des sondages");
                    System.out.println("\t3) Recuperer un sondage");
                    System.out.println("\t4) Repondre a un sondage");
                    System.out.println("\t5) Quitter");
                    choix = clavier.nextInt();
                    clavier.nextLine();
                    switch (choix) {
                        case 1:
                            if (donnees != "") {
                                donnees += "&";
                            }
                            System.out.println("Titre du sondage : ");
                            String titre = clavier.nextLine();
                            System.out.println("Nombre de questions dans votre sondage : ");
                            int nbQuestions = clavier.nextInt();
                            clavier.nextLine();
                            ArrayList<String> questions = new ArrayList<String>();
                            ArrayList<ArrayList<String>> choicestab = new ArrayList<ArrayList<String>>();
                            String temp = "";
                            String question = "";
                            for (int i = 1; i <= nbQuestions ; i++) {
                                System.out.println("Question "+i+") : ");
                                questions.add(clavier.nextLine());
                                System.out.println("Combien de réponse pour la question "+i+" : ");
                                int nbChoix = clavier.nextInt();clavier.nextLine();
                                ArrayList<String> choices = new ArrayList<String>();
                                for(int j=1 ; j<=nbChoix ; j++){
                                    System.out.println("Choix "+j+") : ");
                                    choices.add(clavier.nextLine());
                                }
                                choicestab.add(choices);
                                // choices.clear();
                            }        
                            JSONArray questionsjarray = new JSONArray(questions);
                            JSONArray choicejarray = new JSONArray(choicestab); 
                            // System.out.println("Questions\n\t" + questions+"\n\nchoix\n\t"+choicestab);
                            try {
                                donnees = URLEncoder.encode("createSondage", "UTF-8") +
                                    "&responsable=" + URLEncoder.encode(""+login,"UTF-8")+
                                    "&titre=" + URLEncoder.encode("" + titre, "UTF-8") +
                                    "&questions=" + URLEncoder.encode("" + questionsjarray, "UTF-8")+
                                    "&choix="+ URLEncoder.encode(""+choicejarray,"UTF-8");
                            } catch (UnsupportedEncodingException e) {
                                System.err.println("Erreur lors de l'encodage : " + e);
                                System.exit(-1);
                            }
                            reponse = envoiDonnees("http://localhost:80/SondageIndex.php", donnees);
                            System.out.println(reponse);
                            break;
                        case 2:
                            if (donnees != "") {
                                donnees += "&";
                            }
                            reponse = envoiDonnees("http://localhost:80/SondageIndex.php", "getListSondage");
                            break;
                        case 3:
                            if (donnees != "") {
                                donnees += "&";
                            }
                            reponse = envoiDonnees("http://localhost:80/SondageIndex.php", "getSondage");
                            break;
                        case 4:
                            if (donnees != "") {
                                donnees += "&";
                            }
                            reponse = envoiDonnees("http://localhost:80/SondageIndex.php", "answerSondage");
                            break;
                        default:
                            return;
                    }
                } else {
                    System.out.println(reponse);
                }
            }
            if (choix == 2) {
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

                try {
                    listeDonnees = URLEncoder.encode("" + json, "UTF-8") + "&mode=" +
                        URLEncoder.encode("" + mode, "UTF-8");

                } catch (UnsupportedEncodingException e) {
                    System.err.println("Erreur lors de l'encodage : " + e);
                    System.exit(-1);
                }

                reponse = envoiDonnees("http://localhost:80/index.php", listeDonnees);
                // System.out.println(reponse);
                if (reponse.equals("OKinscription")) {
                    System.out.println("\nVous etes bien inscrit !\n");
                }
            }
        }
        while (choix != 3);

        // // Affichage des données reçues
        // System.out.println("Réponse du serveur : ");
        // System.out.println(donnees);
        clavier.close();
    }

    public static String encoderDonneesJSON(String listeDonnees, JSONObject json, String mode) {
        try {
            listeDonnees = URLEncoder.encode("" + json, "UTF-8") + "&mode=" + URLEncoder.encode("" + mode, "UTF-8");

        } catch (UnsupportedEncodingException e) {
            System.err.println("Erreur lors de l'encodage : " + e);
            System.exit(-1);
        }
        return listeDonnees;
    }

    public static String encoderDonnees(String listeDonnees, String mode) {
        try {
            listeDonnees = URLEncoder.encode("" + mode, "UTF-8");

        } catch (UnsupportedEncodingException e) {
            System.err.println("Erreur lors de l'encodage : " + e);
            System.exit(-1);
        }
        return listeDonnees;
    }

    public static String envoiDonnees(String uri, String listeDonnees) {
        // Mise en forme de l'URL
        String donnees = "";
        URL url = null;
        try {
            url = new URL(uri);
        } catch (MalformedURLException e) {
            System.err.println("URL incorrect : " + e);
            System.exit(-1);
        }

        // Etablissement de la connexion
        URLConnection connexion = null;
        try {
            connexion = url.openConnection();
            connexion.setDoOutput(true);
        } catch (IOException e) {
            System.err.println("Connexion impossible : " + e);
            System.exit(-1);
        }

        // Envoi de la requête
        try {
            OutputStreamWriter writer = new OutputStreamWriter(connexion.getOutputStream());
            writer.write("donnees=" + listeDonnees);
            writer.flush();
            writer.close();
        } catch (IOException e) {
            System.err.println("Erreur lors de l'envoi de la requete : " + e);
            System.exit(-1);
        }

        // Réception des données depuis le serveur
        donnees = "";
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(connexion.getInputStream()));
            String tmp;
            while ((tmp = reader.readLine()) != null)
                donnees += tmp;
            reader.close();
        } catch (Exception e) {
            System.err.println("Erreur lors de la lecture de la réponse : " + e);
            System.exit(-1);
        }
        return donnees;
    }

}
