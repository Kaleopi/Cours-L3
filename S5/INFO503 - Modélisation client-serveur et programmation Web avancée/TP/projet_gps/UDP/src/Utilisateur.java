import org.json.*;

public class Utilisateur{
    protected int idUtilisateur;
    protected String login;
    protected String mdp;
    

    public Utilisateur() {
    }

    public Utilisateur(int idUtilisateur, String login, String mdp) {
        this.idUtilisateur = idUtilisateur;
        this.login = login;
        this.mdp = mdp;
    }

    public int getIdUtilisateur() {
        return this.idUtilisateur;
    }

    public void setIdUtilisateur(int idUtilisateur) {
        this.idUtilisateur = idUtilisateur;
    }

    public String getLogin() {
        return this.login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getMdp() {
        return this.mdp;
    }

    public void setMdp(String mdp) {
        this.mdp = mdp;
    }


    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Utilisateur)) {
            return false;
        }
        Utilisateur utilisateur = (Utilisateur) o;
        return idUtilisateur == utilisateur.idUtilisateur && Objects.equals(login, utilisateur.login) && Objects.equals(mdp, utilisateur.mdp);
    }

    @Override
    public int hashCode() {
        return Objects.hash(idUtilisateur, login, mdp);
    }

    @Override
    public String toString() {
        return "{" +
            " idUtilisateur='" + getIdUtilisateur() + "'" +
            ", login='" + getLogin() + "'" +
            ", mdp='" + getMdp() + "'" +
            "}";
    }

}