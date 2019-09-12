public class Media{
  //Déclarations
  Static String _nom;
  private String titre;
  private StringBuffer cote;
  private int note;

  //Constructeurs
  public Media(){
    titre = "default";
    cote = "";
    note = 0;
  }

  public Media(String titre, StringBuffer cote, int note){
    this.titre = titre;
    this.cote = cote.clone();
    this.note = note;
  }

  public Media(Media m){
    this.titre = m.titre;
    this.cote = m.cote.clone();
    this.note = m.note;
  }

  //Getters
  public String getTitre(){
    return this.titre;
  }
  public StringBuffer getCote(){
    return this.cote;
  }
  public int getNote(){
    return this.note;
  }

  //Setters
  public void setTitre(String titre){
    this.titre = titre;
  }
  public void setCote(StringBuffer cote){
    this.cote = cote.clone();
  }
  public void setNote(int note){
    this.note = note;
  }

  //toString
  @Override public String toString(){
    return
    "titre : " + this.titre +
    ", cote : " + this.cote +
    ", note : " + this.note;
  }

  @Override public Media clone(){
    return new Media(this);
  }

  @Override public boolean equals(Objet obj){
    Media other = new (Media)obj;
    boolean toR = false;
    if(obj==null){
      return res;
    }
    if(cote==null){
      if(other.cote!=null){
        res = false;
      }
    else
      if(cote.equals(other.cote)){
        res = false;
      }
    }
    if(note!=other.note){
      res = false;
    }
    if(titre==null){
      if(other.titre!=null){
        res = false;
      }
    }
    else
      if(!titre.equals(other.titre)){
        res = false;
      }
    return res;
  }
}

public class Livre extends Media{
  private String auteur;
  private String ISBN;
}

//Question 4
public static void main(String[] args){
  Livre livre = new Livre("Titre","cote",5,"Auteur","ISBN");
  Livre livre2 = new Livre(livre);
  livre2.setTitre("Autre");
  System.out.println(livre1.equals(livre2));

  //Question 5
  Media m1 = new Media();
  Livre l = new Livre();
  Livre l2 = new Media(); //FAUX
  Media m2 = new Livre();
}

//Question 8
Public class Film extends Media{


  public String getRealisateur(){
    return this.realisateur;
  }
  public int getAnnee(){
    return this.annee;
  }

  public void setRealisateur(String real){
    this.realisateur = real;
  }
  public void setAnnee(int annee){
    this.annee = annee;
  }

  public Film(int annee, String realisateur, String titre, StringBuffer cote, int note){
    super(titre,cote,note);
    this.realisateur = realisateur;
    this.annee = annee;
  }

  public Film(){
    super();
    this.annee = this.realisateur = null;
  }

  public Film(Film f){
    super(Media f);
    this.annee = f.annee;
    this.realisateur = f.realisateur;
  }
}
