class Modele{
  //attributs
  protected String modele;
  //constructeur
  Modele(){
    modele=null;
  }
  Modele(String modele){
    this.modele=modele;
  }
  //méthodes
  public String getModele(){
    return this.modele;
  }
  public setModele(String modele){
    this.modele=modele;
  }
}
