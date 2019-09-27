import java.util.Random;
import java.util.*;

public class Personne{
  static int n = 0;
  private int id;

  public Personne(){
    id = n++;
  }

  public String toString(){
    return ""+id;
  }

  public static void main(String[] args){
    int taille = 100000;

    Vector<Personne> v = new Vector<Personne>(taille);
    Deque<Personne> d = new LinkedList<Personne>();
    for(int i=0 ; i<taille ; i++){
      Personne p = new Personne();
      v.add(p);
      d.add(p);
    }

    Iterator val = v.iterator();
    Iterator valq = d.iterator();

    long normalVec = System.currentTimeMillis();
    v.toString();
    System.out.println("\n"+(System.currentTimeMillis()-normalVec)+" millisecondes normal vec");

    long itVec = System.currentTimeMillis();
    while(val.hasNext() && val){
      val.next();
    }
    System.out.println("\n"+(System.currentTimeMillis()-itVec)+" millisecondes iterator vec");

    long normalQueue = System.currentTimeMillis();
    d.toString();
    System.out.println("\n"+(System.currentTimeMillis()-normalQueue)+" millisecondes normal queue");

    long itQueue = System.currentTimeMillis();
    while(valq.hasNext()){
      valq.next();
    }
    System.out.println("\n"+(System.currentTimeMillis()-itQueue)+" milliseceondes iterator queue");

  }

}
