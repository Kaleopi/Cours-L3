package mediatheque2;
import org.json.JSONObject;
/**
 * Classe représentant un livre.
 * @author Cyril Rabat
 * @version 05/10/2019
 */
public class Livre extends Document {
    
    private Personne auteur;
    
    /**
     * Crée un livre.
     * @param titre le titre
     * @param auteur l'auteur
     */
    public Livre(String titre, Personne auteur) {
        super(titre);
        this.auteur = auteur;
    }

    /**
     * Retourne l'auteur.
     * @return l'auteur
     */
    public Personne getAuteur() {
        return auteur;
    }
    
    /**
     * Convertit le livre en chaîne de caractères.
     * @return une chaîne de caractères
     */
    public String toString() {
        return super.toString() + " (" + auteur + ")";
    }
        public JSONObject toJSON(){
        JSONObject j=new JSONObject(this);
        return j;
    }
    
}