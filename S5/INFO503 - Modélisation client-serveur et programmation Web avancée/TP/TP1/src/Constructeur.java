class Constructeur{
  //Attributs
  protected String nom;

  //Constucteur
  Constructeur(){
    this.nom = "DefaultMotors";
  }

  Constructeur(String nom){
    this.nom = nom;
  }

  public String getNom(){
    return this.nom;
  }
}
