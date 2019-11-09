import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;

import java.net.Socket;
import java.net.UnknownHostException;

/**
 * Classe correspondant à un client TCP.
 * Le client envoie la chaine 'Bonjour' et lit une réponse de la part du serveur.
 * Le client envoie ensuite la chaine 'Au revoir' et lit une réponse.
 * Le port d'écoute du serveur est spécifié par l'attribut portEcoute.
  * @author Cyril Rabat
 * @version 21/10/2019
 */
public class ClientTCP {

    public static final int portEcoute = 5001;

    public static void main(String[] args) {
        // Création de la socket
        Socket socket = null;
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
        BufferedReader input = null;
        PrintWriter output = null;
        try {
            input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            output = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
        } catch(IOException e) {
            System.err.println("Association des flux impossible : " + e);
            System.exit(-1);
        }
    
        // Envoi de 'Bonjour'
        String message = "Bonjour";
        System.out.println("Envoi: " + message);
        output.println(message);

        // Lecture de 'Bonjour'
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