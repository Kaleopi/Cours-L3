import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;

/**
 * Client UDP permettant de tester l'envoi d'objets dans un segment UDP.
 * Le client crée un message contenant une personne et l'envoie au serveur.
 * Le numéro de port du serveur est spécifié par l'attribut portEcoute.
 * @author Cyril Rabat
 * @version 18/10/2017
 */
public class ClientUDPObjets {

    public static int portEcoute = 2025;

    public static void main(String[] args) {
        // Création de la socket
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket();
        } catch(SocketException e) {
            System.err.println("Erreur lors de la création du socket : " + e);
            System.exit(-1);
        }

        // Création de la personne
        Personne p = new Personne("Cyril", "Rabat");

        // Transformation en tableau d'octets
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        try {
            ObjectOutputStream oos = new ObjectOutputStream(baos);
            oos.writeObject(p);
        } catch(IOException e) {
            System.err.println("Erreur lors de la sérialisation : " + e);
            System.exit(-1);
        }

        // Création et envoi du segment UDP
        try {
            byte[] donnees = baos.toByteArray();
            InetAddress adresse = InetAddress.getByName("localhost");
            DatagramPacket msg = new DatagramPacket(donnees, donnees.length, 
                                                    adresse, portEcoute);
            socket.send(msg);
            System.out.println("Message envoyé.");
        } catch(UnknownHostException e) {
            System.err.println("Erreur lors de la création de l'adresse : " + e);
            System.exit(-1); 
        } catch(IOException e) {
            System.err.println("Erreur lors de l'envoi du message : " + e);
            System.exit(-1);
        }

        socket.close();
    }

}