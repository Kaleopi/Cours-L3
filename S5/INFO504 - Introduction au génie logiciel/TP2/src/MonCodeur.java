public class MonCodeur{
  public String encode(String msg){
    //  String initial = "A/B/C/D/E/F";
    //    StringBuffer sb = (new StringBuffer(initial)).reverse();
    String sb= (new StringBuffer(msg)).reverse().toString();
    sb+=msg;
    sb+=sb;
    return sb;
  }

  public String decode(String msg){
    int count = msg.length();
    count/=4;
    msg=msg.substring(count,count+count);
    return msg;
  }
}
