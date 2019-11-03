import java.io.*;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.Headers;
import java.net.URI;
import java.net.URLDecoder;
import java.util.HashMap;
import java.util.Scanner;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONString;

class GestionnaireUtilisateurs{
  HashMap<String, JSONObject> users;
  String path = "";
  public GestionnaireUtilisateurs(String nomFichier){
    this.path = nomFichier;
    //Ouverture du fichier
    FileInputStream fs=null;
    try{
      fs = new FileInputStream(this.path);
    }
    catch(FileNotFoundException e){
      System.err.println("Fichier "+ this.path + " introuvable !");
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

    this.users = new HashMap<String, JSONObject>();
    JSONObject object = new JSONObject(json);
    JSONArray tab = object.getJSONArray("Utilisateurs");
    for(int i=0 ; i<tab.length() ; i++){
      JSONObject element = tab.getJSONObject(i);
      this.users.put(element.getString("login"),element);
    }
  }

  public HashMap<String, JSONObject> getUsers(){
    return this.users;
  }

  public boolean search(String login, String mdp){
    JSONObject user = this.users.get(login);
    System.out.println("Searching...");
    if(user!=null && login.equals(user.getString("login")) && mdp.equals(user.getString("password"))){
      return true;
    }
    else{return false;}
  }

  public boolean addUser(String login, String password){
    try {
      RandomAccessFile access = new RandomAccessFile(new File(this.path), "rw");
      access.seek(access.length() - 3);
      if (this.users.get(login) == null) {
        Utilisateur u = new Utilisateur(login,password);
        JSONObject obj = new JSONObject(u);
        obj.put("id", u.getId());
        obj.put("login", u.getLogin());
        obj.put("password", u.getPassword());
        access.writeBytes("\n");
        access.writeBytes(obj.toString());
        access.writeBytes(",\n]}");
        return true;
      } else {
        return false;
      }
    } catch (Exception e) {
      System.err.println("Erreur ouverture fichier GestionnaireUtilisateurs:addUser");
      System.err.println(e);
      System.exit(-1);
      return false;
    }
  }
}
