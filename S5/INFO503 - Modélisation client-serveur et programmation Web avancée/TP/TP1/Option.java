Class Options{
  //attributs
  protected boolean GPS;
  protected boolean Vitre;
  protected boolean Clim;
  //Constructeur
  Options(){
    GPS=false;
    Vitre=false;
    clim=false;
  }
  Options(Boolean GPS,boolean Vitre,boolean Clim){
    this.GPS=GPS;
    this.Vitre=Vitre;
    this.clim=clim;
  }
  Options(Options op){
    this.GPS=op.GPS;
    this.Vitre=op.Vitre;
    this.clim=op.clim;
  }
  //getter
  public boolean getGPS(){
    return GPS;
  }
  public boolean getVitre(){
    return Vitre;
  }
  public boolean getClim(){
    return clim;
  }
  //setter
  void setGPS(bool b){
    this.GPS=b;
  }
  void setVitre(bool b){
    this.Vitre=b;
  }
  void setClim(bool b){
    this.clim=b;
  }
}
