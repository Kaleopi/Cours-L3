import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.*;

public class Adaptateur{
  public String encodeImage(File f){
    try{
      FileInputStream fis = new FileInputStream(f);
      byte byteArray[] = new byte[(int)f.length()];
      fis.read(byteArray);
      String s = new String(fis.toString());
      return s;
    }
    catch(Exception e){
      return e.toString();
    }
  }

  // public File decodeImage(){
  //
  // }
}
