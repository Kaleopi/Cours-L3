import org.json.*;
import java.util.Date;
import java.util.Scanner;
import java.text.SimpleDateFormat;
import java.sql.Timestamp;
import java.util.ArrayList;

public class Activite {
    protected String idSportif;
    protected String heureDeb;
    protected String heureFin;
    protected String sport;
    protected ArrayList<GPS> coords;


    public Activite() {
        this.idSportif = "NaN";
        this.heureDeb = "NaN";
        this.heureFin = "NaN";
        this.sport = "NaN";
        this.coords = new ArrayList<GPS>();
    }

    // public Activite(String idSportif, String heureDeb, String heureFin, String sport, ArrayList<GPS> coords) {
    //     this.idSportif = idSportif;
    //     this.heureDeb = heureDeb;
    //     this.heureFin = heureFin;
    //     this.sport = sport;
    //     this.coords = coords;
    // }

    public String getIdSportif() {
        return this.idSportif;
    }

    public void setIdSportif(String idSportif) {
        this.idSportif = idSportif;
    }

    public String getHeureDeb() {
        return this.heureDeb;
    }

    public void setHeureDeb(String heureDeb) {
        this.heureDeb = heureDeb;
    }

    public String getHeureFin() {
        return this.heureFin;
    }

    public void setHeureFin(String heureFin) {
        this.heureFin = heureFin;
    }

    public String getSport() {
        return this.sport;
    }

    public void setSport(String sport) {
        this.sport = sport;
    }

    public ArrayList<GPS> getCoords() {
        return this.coords;
    }

    public void setCoords(ArrayList<GPS> coords) {
        this.coords = coords;
    }

    @Override
    public String toString() {
        return "{" +
            " idSportif='" + getIdSportif() + "'" +
            ", heureDeb='" + getHeureDeb() + "'" +
            ", heureFin='" + getHeureFin() + "'" +
            ", sport='" + getSport() + "'" +
            ", coords='" + getCoords() + "'" +
            "}";
    }
    
    public JSONObject toJSON() {
        JSONObject j = new JSONObject(this);
        return j;
    }

    public void addCoord(GPS obj){
        this.coords.add(obj);
    }

    public void startActivity(){
        Scanner clavier = new Scanner(System.in);
        int choix = 0;
        do{
            System.out.println("Quelle activite souhaitez vous demarrer ?\n"+
            "1) Marche a pied\n"+
            "2) Course a pied\n"+
            "3) Natation\n"+
            "4) Autre\n"+
            "5) Quitter\n"+
            "Votre choix ? ");
            choix = clavier.nextInt();
            if(choix<1 || choix >5 ){
                System.out.println("Veuillez entrer un chiffre parmi la liste precedente");
            }
        }while(choix < 1 || choix > 5);
        switch(choix){
            case 1:
                this.sport = "Marche a pied";
            break;
            case 2:
                this.sport = "Course a pied";
            break;
            case 3:
                this.sport = "Natation";
            break;
            case 4:
                this.sport = "Autre";
            break;
            default:
                System.exit(0);
        }
        Timestamp time = new Timestamp(System.currentTimeMillis());
        String timestamp = new SimpleDateFormat("dd-MM-yyyy hh:mm:ss").format(time);
        this.heureDeb = timestamp;
        System.out.println("Activite demarree !");
        // System.out.println(this);
    }

    public void stopActivity(){
        Timestamp time = new Timestamp(System.currentTimeMillis());
        String timestamp = new SimpleDateFormat("dd-MM-yyyy hh:mm:ss").format(time);
        this.heureFin = timestamp;
        System.out.println("Fin de l'activite");
    }
}