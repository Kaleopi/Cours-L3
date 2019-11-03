import org.json.*;
import java.util.*;

public class Sondage {
    protected String titre;
    protected Question[] questions;
    protected int nbQuestions;
    protected ArrayList reponses;

    public Sondage() {
        this.titre = "Sondage par défaut";
        this.questions = new Question[1];
        this.questions[0] = new Question();
        this.reponses = new ArrayList<Reponse>();
    }

    public Sondage(String titre, int nbQuestions){
        this.titre = titre;
        this.nbQuestions = nbQuestions;
        this.questions = new Question[this.nbQuestions];
        for(int i=0 ; i<nbQuestions ; i++){
            this.questions[i] = this.addQuestion();
        }
    }

    public Question addQuestion(){
        Question q = new Question();
        return q;
    }

    public JSONObject toJSON() {
        JSONObject j = new JSONObject(this);
        return j;
    }
}
