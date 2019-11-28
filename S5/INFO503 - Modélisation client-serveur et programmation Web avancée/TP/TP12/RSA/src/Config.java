import java.util.Scanner;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import org.json.*;

// javac -d .\classes\ -sourcepath .\src\ -cp .\lib\json-20190722.jar .\src\Test.java
// java -cp ".\classes\;.\lib\json-20190722.jar" Test

/**
 * Classe permettant de cr�er/g�rer un fichier de configuration.
 * @author Cyril Rabat
 * @date 20/10/2018
 */
public class Config {

    private String nomFichier;      // Nom du fichier de configuration
    private JSONObject config;      // La configuration

    /**
     * Ouverture d'un fichier de configuration.
     * @param nomFichier le nom du fichier de configuration
     */
    public Config(String nomFichier) {
        this.nomFichier = nomFichier;
        charger();
    }

    /**
     * Ouverture/cr�ation d'un fichier de configuration.
     * @param nomFichier le nom du fichier de configuration
     * @param creation si 'true', cr�e un nouveau fichier vide
     */
    public Config(String nomFichier, boolean creation) {
        if(!creation) {
            this.nomFichier = nomFichier;
            charger();
        }
        else {
            this.nomFichier = nomFichier;
            config = new JSONObject();
        }
    }

    /**
     * Indique si un fichier existe.
     * @param nomFichier le nom du fichier
     * @return 'true' s'il existe
     */
    public static boolean fichierExiste(String nomFichier) {
        File f = new File(nomFichier);

        return f.exists();
    }

    /**
     * Retourne la valeur associ�e � une clef.
     * @param clef le nom de la clef
     * @return la valeur de la clef
     */
    public String getString(String clef) {
        /**
         * #TODO#
         * R�cup�re la donn�e dont la clef est sp�cifi�e dans l'objet
         * JSON (attribut 'config').
         */
         return this.config.getString(clef);
    }

    /**
     * Retourne la valeur associ�e � une clef.
     * @param clef le nom de la clef
     * @return la valeur de la clef
     */
    public int getInt(String clef) {
        /**
         * #TODO#
         * R�cup�re la donn�e dont la clef est sp�cifi�e dans l'objet
         * JSON (attribut 'config').
         */
         return this.config.getInt(clef);
    }

    /**
     * Ajoute une valeur de type entier dans la configuration.
     * @param clef le nom de la clef
     * @param valeur la valeur de la clef
     */
    public void ajouterValeur(String clef, int valeur) {
        /**
         * #TODO#
         * Ajouter les donn�es dans l'objet JSON (attribut 'config')
         */
         this.config.put(clef,valeur);

    }

    /**
     * Ajoute une valeur de type cha�ne de caract�res dans la configuration.
     * @param clef le nom de la clef
     * @param valeur la valeur de la clef
     */
    public void ajouterValeur(String clef, String valeur) {
        /**
         * #TODO#
         * Ajouter les donn�es dans l'objet JSON (attribut 'config')
         */
         this.config.put(clef,valeur);
    }

    /**
     * Charge un fichier de configuration en m�moire.
     */
    private void charger() {

      /**
      * #TODO#
      * Charger le fichier JSON dont le nom correspond � l'attribut
      * 'nomFichier' dans l'attribut 'config' (un objet JSONObject).
      */
        // Ouverture du fichier
        //Ouverture du fichier
        FileInputStream fs=null;
        try{
          fs = new FileInputStream(this.nomFichier);
        }
        catch(FileNotFoundException e){
          System.err.println("Fichier"+ this.nomFichier + " introuvable !");
          System.exit(-1);
        }
        // Récupération de la chaîne JSON depuis le fichier
        String json = new String();
        Scanner s = new Scanner(fs);
        while(s.hasNext()){
          json+=s.nextLine();
        }
        s.close();
        json = json.replaceAll("[\t ]","");

        //Fermeture du fichier
        try{
          fs.close();
        }
        catch(IOException e){
          System.err.println("Erreur lors de la fermeture du fichier !");
          System.err.println(e);
          System.exit(-1);
        }

        //Création d'un objet JSON
        this.config = new JSONObject(json);
        // System.out.println("Contenu JSON : ");
        // System.out.println(json);
    }

    /**
     * Sauvegarde la configuration dans le fichier.
     */
    public void sauvegarder() {
        // Cr�ation du fichier de sortie

        /**
         * #TODO#
         * Sauvegarder le fichier JSON dans le fichier dont le nom
         * correspond � l'attribut 'nomFichier'.
         */
         File fs=null;
         fs = new File(this.nomFichier);
         FileWriter fr = null;
         try{
           fr = new FileWriter(fs);
           fr.write(this.config.toString());
         }
         catch(IOException e){
           e.printStackTrace();
         }
         finally{
           try{
             fr.close();
           }
           catch(IOException e){
             e.printStackTrace();
           }
         }
    }

}
