import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;

import java.net.Socket;

/**
 * Classe correspondant au thread associe à chaque connexion d'un client.
 * Le constructeur prend en paramètre la socket de communication avec le client.
 * @author Cyril Rabat
 * @version 21/10/2019
 */
public class ThreadConnexion extends Thread {

    private BufferedReader input;
    private PrintWriter output;
    private Socket socketClient;

    public ThreadConnexion(Socket socketClient) {
        this.socketClient = socketClient;

        // Association d'un flux d'entrée et de sortie
        try {
            input = new BufferedReader(new InputStreamReader(socketClient.getInputStream()));
            output = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socketClient.getOutputStream())), true);
        } catch(IOException e) {
            System.err.println("Association des flux impossible : " + e);
            System.exit(-1);
        }
    }

    @Override
    public void run() {
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
        message = "";
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
        } catch(IOException e) {
            System.err.println("Erreur lors de la fermeture des flux et des sockets : " + e);
            System.exit(-1);
        }
    }
    
}