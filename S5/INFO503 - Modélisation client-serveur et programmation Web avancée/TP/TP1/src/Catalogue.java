class Catalogue{
  protected Voiture[] voiture;
  static int i;
   public void ajouterVoiture(Voiture v){
     voiture[i]=v;
     i++;
   }
   public void commander(Voiture voiture){
     Commande commande=new Commande(voiture);
   }
}
