class commande{
  //attributs
  protected Modele modele;
  protected COULEUR couleur;
  protected Moteur moteur;
  protected Options Option;
  protected Date date;
  //constructeur
  commande(){
    this.modele=Modele();
    this.couleur=Couleur();
    this.moteur=Moteur();
    this.options=Options();
    this.date=null;
  }
  commande(){
    
  }
}
