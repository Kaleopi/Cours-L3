import java.util.Date;

class Voiture{
  //Attributs
  static int staticid = "1AA1";

  protected String id;
  protected Modele modele;
  protected Moteur moteur;
  protected Date dateFab;
  protected COULEUR couleur;
  protected Options option;

  //Constucteur
  Voiture(){
    this.id=staticid;
    staticid+=1;
    this.modele=new Modele();
    this.moteur=new Moteur();
    this.dateFab=null;
    this.couleur=COULEUR[0];
    this.option=new Options();
    Place place=new Place();
    Stock(id,place.getRangee,place.GetNumPlace);
  }
  Voiture(Modele modele,Moteur moteur, Date dateFab,COULEUR couleur,Options option){
    this.id=staticid;
    staticid+=1;
    this.modele=modele;
    this.moteur=moteur;
    this.dateFab=dateFab;
    this.couleur=couleur;
    this.optios=option;
    Place place = new Place();
    Stock(id,place.getRangee(),place.getNumPlace());
  }
  Voiture(Modele modele,Moteur moteur, Date dateFab,COULEUR couleur,Options option,Place place){
    this.id=staticid;
    staticid+=1;
    this.modele=modele;
    this.moteur=moteur;
    this.dateFab=dateFab;
    this.couleur=couleur;
    this.option=option;
    Stock(id,place.getRangee(),place.getNumPlace());
  }
}
