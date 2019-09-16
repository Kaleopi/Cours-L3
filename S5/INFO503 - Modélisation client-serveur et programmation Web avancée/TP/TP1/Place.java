class Place{
  //static
  static int cpt = 0;
  static char rangee='A'
  //Attributs
  protected int num;
  protected char rangee;
  protected boolean estVide;

  //Constructeur
  Place(){
    this.num = ++cpt;
    if(cpt>150){
      rangee++;
      cpt = 0;
    }
  }
}
