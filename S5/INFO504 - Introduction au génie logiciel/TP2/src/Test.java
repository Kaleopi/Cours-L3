import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class Test
{
  public static void main(String[] args){
    MonCodeur mc = new MonCodeur();
    Codeur c = new Codeur();
    Adaptateur a = new Adaptateur();
    String s = "bibou";
    /*try{
      s=mc.encode(s);
      s=c.encode(s);

      System.out.println(s);

      s=c.decode(s);
      System.out.println(s);
      s=mc.decode(s);

      System.out.println(s);
    }
    catch(Exception e){
      System.out.println(e);
    }*/
    File f = new File("C:/Users/Thoma/Pictures/checked.png");
    String sImg = a.encodeImage(f);
  }
}
