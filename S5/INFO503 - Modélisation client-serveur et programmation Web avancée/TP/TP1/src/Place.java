class Place{
  //static
  static int cpt = 0;
  static char rangee='A';
  //Attributs
  protected int num;
  protected boolean estVide;

  //Constructeur
  Place(){
    this.num = ++cpt;
    if(cpt>150){
      rangee++;
      cpt = 0;
    }
  }

  //Getters
  public char getRangee(){
    return this.rangee;
  }
  public int getNum(){
    return this.num;
  }
  public boolean estVide(){
    return this.estVide;
  }
}
