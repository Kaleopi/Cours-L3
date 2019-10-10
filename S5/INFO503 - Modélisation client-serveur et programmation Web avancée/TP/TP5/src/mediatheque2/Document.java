package mediatheque2;
import org.json.JSONObject;

/**
 * Classe représentant un document de médiathèque.
 * @author Cyril Rabat
 * @version 05/10/2019
 */
public abstract class Document {
    
    private String titre;
    
    /**
     * Crée un document.
     * @param titre le titre
     */
    public Document(String titre) {
        this.titre = titre;
    }
    
    /**
     * Retourne le titre.
     * @return le titre
     */
    public String getTitre() {
        return titre;
    }

    /**
     * Convertit le document en chaîne de caractères.
     * @return une chaîne de caractères
     */
    public String toString() {
        return titre;
    }
        public JSONObject toJSON(){
        JSONObject j=new JSONObject(this);
        return j;
    }
}