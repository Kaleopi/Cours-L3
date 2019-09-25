class commande{
  //attributs
  protected Voiture voiture;
  protected Date dateAchat;
  //constructeur
  commande(Voiture voiture){
    dateAchat=date("Y-m-d H:i:s");
    this.voiture=voiture
  }

}
