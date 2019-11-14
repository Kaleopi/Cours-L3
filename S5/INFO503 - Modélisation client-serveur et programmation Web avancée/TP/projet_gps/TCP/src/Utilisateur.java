import org.json.*;

public class Utilisateur{
    protected static int idUtilisateur = 0;
    protected String login;
    protected String password;
    

    public Utilisateur(String login, String password) {
        this.login = login;
        this.password = password;
    }

    public int getId(){
        return Utilisateur.idUtilisateur;
    }
    public String getLogin() {
        return this.login;
    }
    public String getPassword() {
        return this.password;
    }

    public void setLogin(String login) {
        this.login = login;
    }
    public void setMdp(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "{" +
            " id='"+ getId() +"'"+
            " login='" + getLogin() + "'" +
            ", password='" + getPassword() + "'" +
            "}";
    }

    public JSONObject toJSON() {
        JSONObject j = new JSONObject(this);
        return j;
    }
}