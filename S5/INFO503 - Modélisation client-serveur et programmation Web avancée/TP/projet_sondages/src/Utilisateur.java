import org.json.*;

public class Utilisateur{
  protected String login;
  protected String password;
  protected static int id = 0;

  public Utilisateur(String login, String password){
    this.login = login;
    this.password = password;
    ++Utilisateur.id;
  }

  public int getId(){
    return Utilisateur.id;
  }
  public String getLogin(){
    return this.login;
  }
  public String getPassword(){
    return this.password;
  }

  public String toString(){
    return login+" , "+password+" , "+Utilisateur.id;
  }

  public JSONObject toJSON(){
    JSONObject j = new JSONObject(this);
    return j;
  }
}
