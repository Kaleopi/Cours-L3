import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;

import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Classe correspondant à un serveur TCP.
 * Le client envoie la chaine 'Bonjour' et lit une réponse de la part du serveur.
 * Le client envoie ensuite la chaine 'Au revoir' et lit une réponse.
 * Le numéro de port d'écoute est spécifié par l'attribut portEcoute.
 * @author Cyril Rabat
 * @version 21/10/2019
 */
public class ServeurTCP {

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

        // Attente d'une connexion d'un client
        Socket socketClient = null;
        try {
            System.out.println("En attente d'une connexion d'un client...");
            socketClient = socketServeur.accept();
        } catch(IOException e) {
            System.err.println("Erreur lors de l'attente d'une connexion : " + e);
            System.exit(-1);
        }
        System.out.println("Connexion établie");

        // Association d'un flux d'entrée et de sortie
        BufferedReader input = null;
        PrintWriter output = null;
        try {
            input = new BufferedReader(new InputStreamReader(socketClient.getInputStream()));
            output = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socketClient.getOutputStream())), true);
        } catch(IOException e) {
            System.err.println("Association des flux impossible : " + e);
            System.exit(-1);
        }

        // Lecture de 'Bonjour'
        String message = "";
        try {
            message = input.readLine();
        } catch(IOException e) {
            System.err.println("Erreur lors de la lecture : " + e);
            System.exit(-1);
        }
        System.out.println("Lu: " + message);

        // Envoi de 'Bonjour'
        message = "Bonjour";
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

        // Envoi de 'Au revoir'
        message = "Au revoir";
        System.out.println("Envoi: " + message);
        output.println(message);
        
        // Fermeture des flux et des sockets
        try {
            input.close();
            output.close();
            socketClient.close();
            socketServeur.close();
        } catch(IOException e) {
            System.err.println("Erreur lors de la fermeture des flux et des sockets : " + e);
            System.exit(-1);
        }
    }

}