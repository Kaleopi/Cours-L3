import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.lang.Math;
import org.json.*;
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
        String messageLu = "";
        try {
            messageLu = input.readLine();
        } catch(IOException e) {
            System.err.println("Erreur lors de la lecture : " + e);
            System.exit(-1);
        }
        System.out.println("Lu: " + messageLu);

        // Envoi de 'Bonjour'
        int rand = (int)(Math.random()*3)+1;
        String message = Integer.toString(rand);

        JSONObject json = message.toJSON();
        //Verification valeurs 1:Pierre 2:Feuille 3:Ciseaux
        switch(message){
            case "1":
                if(messageLu.equals("1")){
                    message += "\tegalite...";
                }
                else if(messageLu.equals("2")){
                    message += "\tt'as gagne!";
                }
                else if(messageLu.equals("3")){
                    message += "\tt'as perdu";
                }
                else{message+="\tErreur, chiffre faux";}
            break;
            case "2":
            if (messageLu.equals("2")) {
                message += "\tegalite...";
            } else if (messageLu.equals("1")) {
                message += "\tt'as perdu!";
            } else if (messageLu.equals("3")) {
                message += "\tt'as gagne";
            } else {
                message += "\tErreur, chiffre faux";
            }
            break;
            case "3":
            if (messageLu.equals("3")) {
                message += "\tegalite...";
            } else if (messageLu.equals("2")) {
                message += "\tt'as perdu!";
            } else if (messageLu.equals("1")) {
                message += "\tt'as gagne";
            } else {
                message += "\tErreur, chiffre faux";
            }
            break;
            default:
            break;
        }
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
