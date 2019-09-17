class Stock{
  //Attributs
  protected String id;
  protected char rangee;
  protected int numPlace;
  //constructeur
  Stock(String id,char rangee,int numPlace){
    this.id=id;
    this.rangee=rangee;
    this.numPlace=numPlace;
  }
  Stock(Voiture v,Place p){
    this.id=v.id;
    this.numPlace=p.numPlace;
    this.rangee=p.rangee;
  }
  //methodes
  public String getID(){
    return this.id;
  }
  public char getRangee(){
    return this.rangee;
  public int GetNumPlace(){
    return this.numPlace;
  }
  void setID(String id){
    this.id=id;
  }
  void setRangee(char rangee){
    this.rangee=rangee;
  }
  void setNumPlace(int numPlace){
    this.numPlace=numPlace;
  }
}
