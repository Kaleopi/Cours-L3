import org.json.*;

public class Question{
    protected String intitule;
    protected String[] choix;

    public Question() {
        this.intitule = "Question par défaut";
        this.choix = new String[1];
        this.choix[0] = "Choix par défaut";
    }

    public JSONObject toJSON() {
        JSONObject j = new JSONObject(this);
        return j;
    }
}
