import mediatheque2.*;
import org.json.JSONObject;
class Test2{
	public static void main(String [] args){
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
	}
}
// javac -d .\classes\ -sourcepath .\src\ -cp .\lib\json-20190722.jar .\src\Test.java
// java -cp ".\classes\;.\lib\json-20190722.jar" Test