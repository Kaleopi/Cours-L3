// javac -d .\classes\ -sourcepath .\src\ -cp .\lib\json-20190722.jar .\src\Test.java
// java -cp ".\classes\;.\lib\json-20190722.jar" Test

class Test{
	public static void main(String [] args){
    GestionnaireUtilisateurs users = new GestionnaireUtilisateurs("./src/logins.json");
  }
}
