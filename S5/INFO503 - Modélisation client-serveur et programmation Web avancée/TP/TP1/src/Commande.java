import java.util.Date;
class Commande{
  //attributs
  protected Voiture voiture;
  protected Date dateAchat;
  //constructeur
  public Commande(Voiture voiture){
    dateAchat=Date("Y-m-d H:i:s");
    this.voiture=voiture;
  }

}
