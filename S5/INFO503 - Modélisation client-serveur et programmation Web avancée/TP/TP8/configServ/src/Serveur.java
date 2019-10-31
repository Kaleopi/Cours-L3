import java.io.IOException;

import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.SocketException;
import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 * Classe correspondant à un serveur UDP.
 * La chaine de caractères "Bonjour" est envoyée au serveur.
 * @author Cyril Rabat
 * @version 20/10/2019
 */
public class ServeurUDP {

    // Le port d'écoute du serveur
    public static int portEcoute = 2025;

    public static void main(String[] args) {
        // Création de la socket
        DatagramSocket socket = null;
        try {
            socket = new DatagramSocket(portEcoute);
        } catch(SocketException e) {
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
        } catch(IOException e) {
            System.err.println("Erreur lors de la réception du message : " + e);
            System.exit(-1);
        }

        // Fermeture de la socket
        socket.close();
    }

}
