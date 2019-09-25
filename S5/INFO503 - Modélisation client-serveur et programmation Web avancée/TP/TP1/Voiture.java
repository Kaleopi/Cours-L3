import java.util.Date;

class Voiture{
  //Attributs
  static int staticid = "1AA1";

  protected String id;
  protected Modele modele;
  protected Moteur moteur;
  protected Date dateFab;
  protected Couleur couleur;
  protected Options option;

  //Constucteur
  Voiture(){
    this.id=staticid;
    staticid+=1;
    this.modele=new Modele();
    this.moteur=new Moteur();
    this.dateFab=null;
    this.couleur=Couleur[0];
    this.option=new Options();
    Place place=new Place();
    Stock(id,place.getRangee,place.GetNumPlace);
  }
  Voiture(Modele modele,Moteur moteur, Date dateFab,Couleur couleur,Options option){
    this.id=staticid;
    staticid+=1;
    this.modele=modele;
    this.moteur=moteur;
    this.dateFab=dateFab;
    this.couleur=couleur;
    this.options=options;
    Place place new Place();
    Stock(id,place.getRangee,place.GetNumPlace);
  }
  Voiture(Modele modele,Moteur moteur, Date dateFab,Couleur couleur,Options option,Place place){
    this.id=staticid;
    staticid+=1;
    this.modele=modele;
    this.moteur=moteur;
    this.dateFab=dateFab;
    this.couleur=couleur;
    this.options=options;
    Stock(id,place.getRangee,place.GetNumPlace);
  }
}
