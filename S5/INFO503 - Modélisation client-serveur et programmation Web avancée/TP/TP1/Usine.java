Class Usine{
  //attributs
  protected String nomUsine;
  protected Parking parking;
  //constructeur
  Usine(){
    nomUsine="defUsine";
    Parking=null;
  }
  Usine(String nomUsine,Parking parking){
    this.nomUsine=nomUsine;
    this.parking=parking;
  }
  //getter
public String getNomUsine(){
  return this.nomUsine;
  }
public Parking getParking(){
  return this.Parking
}
void setNomUsine(String nomUsine){
  this.nomUsine=nomUsine;
}

}
