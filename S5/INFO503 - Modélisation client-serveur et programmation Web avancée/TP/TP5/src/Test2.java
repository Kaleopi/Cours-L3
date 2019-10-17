import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;
import mediatheque2.*;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.json.JSONString;


class Test2{
	public static void main(String [] args){
		if(args.length!=1){
			System.err.println("Erreur : vous devez spécifier le nom du fichier JSON.\n\nUsage : java LecteurJSON fichier.json\n\toù 'fichier.json' est le nom du fichier à ouvrir");
			System.exit(-1);
		}

		//Ouverture du fichier
		FileInputStream fs=null;
		try{
			fs = new FileInputStream(args[0]);
		}
		catch(FileNotFoundException e){
			System.err.println("Fichier"+ args[0] + " introuvable !");
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
		JSONObject objet = new JSONObject(json);
		System.out.println("Contenu JSON : ");
		System.out.println(json);

		//Affichage à l'écran
		JSONArray tableau = objet.getJSONArray("contacts");
		System.out.println("Liste des personnes : ");
		for(int i=0 ; i<tableau.length() ; i++){
			JSONObject element = tableau.getJSONObject(i);
			System.out.print("nom="+element.getString("nom"));
			System.out.print(", prenom="+element.getString("prenom"));
			System.out.print(", age="+element.getInt("age"));
		}
	}
}



// javac -d .\classes\ -sourcepath .\src\ -cp .\lib\json-20190722.jar .\src\Test.java
// java -cp ".\classes\;.\lib\json-20190722.jar" Test



/* TEST DE VERIFICATION DE SERIALISATION

Personne a = new Personne("erf","1/1/00");
	Document d =new Livre("cheh",a);
	Document f=new Film("kek",a,12.5);
	Mediatheque m=new Mediatheque();
	m.ajouterDocument(d);
	m.ajouterDocument(f);
	JSONObject j1=a.toJSON();
	JSONObject j2=d.toJSON();
	JSONObject j3=m.toJSON();
	JSONObject j4=f.toJSON();
	System.out.println("Auteur :");
	System.out.println(j1);
	System.out.println("\nDocument :");
	System.out.println(j2);
	System.out.println("\nFilm :");
	System.out.println(j4);
	System.out.println("\nMediat :");
	System.out.println(j3);
	System.out.println("-----------------------------------\n");
	Document T[]={f,d};
	System.out.println(T[0]);

	JSONObject tab= new JSONObject(T);
	System.out.println(tab);
*/