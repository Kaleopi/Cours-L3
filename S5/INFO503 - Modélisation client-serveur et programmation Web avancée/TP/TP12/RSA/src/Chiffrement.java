import java.security.PublicKey;
import java.security.PrivateKey;
import java.security.spec.RSAPrivateKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.InvalidKeyException;

import java.security.NoSuchProviderException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.Cipher;

import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.IOException;

/**
 * Classe permettant de chiffrer un message à l'aide d'une clé publique.
 * Le message chiffré est placé dans un fichier.
 * @author Cyril Rabat
 * @version 05/11/2019
 */
public class Chiffrement {
    public static void dechiffrement(String nomFichierPrivee, String nomFichierInput){
        // Récupération de la clé privée
        PrivateKey clePrivee = GestionClesRSA.lectureClePrivee(nomFichierPrivee);

        // Chargement du message chiffré
        byte[] messageCode = null;
        try {
            FileInputStream fichier = new FileInputStream(nomFichierInput);
            messageCode = new byte[fichier.available()];
            fichier.read(messageCode);
            fichier.close();
        } catch (IOException e) {
            System.err.println("Erreur lors de la lecture du message : " + e);
            System.exit(0);
        }

        // Déchiffrement du message
        byte[] bytes = null;
        try {
            Cipher dechiffreur = Cipher.getInstance("RSA");
            dechiffreur.init(Cipher.DECRYPT_MODE, clePrivee);
            bytes = dechiffreur.doFinal(messageCode);
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        } catch (NoSuchPaddingException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        } catch (InvalidKeyException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        } catch (IllegalBlockSizeException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        } catch (BadPaddingException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        }

        // Affichage du message
        String message = new String(bytes);
        System.out.println("Message : " + message);
    }
    public static void chiffrement(String nomFichierPublique, String msg, String fichierSave){    
        // Recuperation de la cle publique
        PublicKey clePublique = GestionClesRSA.lectureClePublique(nomFichierPublique);

        // Chiffrement du message
        byte[] bytes = null;
        try {
            Cipher chiffreur = Cipher.getInstance("RSA");
            chiffreur.init(Cipher.ENCRYPT_MODE, clePublique);
            bytes = chiffreur.doFinal(msg.getBytes());
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        } catch (NoSuchPaddingException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        } catch (InvalidKeyException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        } catch (IllegalBlockSizeException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        } catch (BadPaddingException e) {
            System.err.println("Erreur lors du chiffrement : " + e);
            System.exit(0);
        }

        // Sauvegarde du message chiffré
        try {
            FileOutputStream fichier = new FileOutputStream(fichierSave);
            fichier.write(bytes);
            fichier.close();
        } catch (IOException e) {
            System.err.println("Erreur lors de la sauvegarde du message chiffré : " + e);
            System.exit(0);
        }
        System.out.println("Message code enregistré dans '" + fichierSave + "'");
    }
}