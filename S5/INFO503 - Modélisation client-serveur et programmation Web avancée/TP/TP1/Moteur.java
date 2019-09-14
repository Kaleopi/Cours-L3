class Moteur{
  //Constantes
  static final int PUISSDEF = 110;

  //Attributs
  static int id = 0;

  protected String carburation;
  protected int puissance;

  //Constucteur
  Moteur(){
    id++;
    this.id = id;
    carburation = CARBURATION.Diesel;
    puissance = PUISSDEF;
  }

  Moteur(CARBURATION carbu, int puissance){
    id++;
    this.id = id;
    carburation = carbu;

    if(puissance<1){
      this.puissance = PUISSDEF;
    }
    else{
      this.puissance = puissance;
    }
  }

  Moteur(Moteur m){
    Moteur(m.carbu,m.puissance);
  }
}
