import mediatheque1.*;
import org.json.JSONObject;
class Test{
	public static void main(String [] args){
	Auteur a = new Auteur("erf","1/1/00");
	Livre L1= new Livre("kek",a);
	Mediatheque m=new Mediatheque();
	m.ajouterLivre(L1);
	JSONObject j1=a.toJSON();
	JSONObject j2=L1.toJSON();
	JSONObject j3=m.toJSON();
	System.out.println(m.getLivre(0));
	System.out.println("\nAuteur :");
	System.out.println(j1);
	System.out.println("\nLivre :");
	System.out.println(j2);
	System.out.println("\nMediat :");
	System.out.println(j3);
	}
}
// javac -d .\classes\ -sourcepath .\src\ -cp .\lib\json-20190722.jar .\src\Test.java
// java -cp ".\classes\;.\lib\json-20190722.jar" Test
