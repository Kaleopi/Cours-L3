public class Serveur{
  private static final int port = 3120;
  public static void main(String[] args){
    ServerSocket serveur = null;
    Socket client = null;  //rajouter exception
    serveur = new ServeurSocket(port);
    while(true){
      client = server.accept();
      ThreadClient c = new ThreadClient(client); //rajouter exception
      c.start(); //rajouter exception
    }
    server.close();
  }
}

public class Client{
  private String idUtilisateur;
  private int port;

  //Constructeurs et getters
  public void main(String[] args){
    Client c = null;
    Socket socket = null;
    Scanner clavier = null;
    Message m = null;
    c = new Client("jop",3210);
    socket = new Socket("localhost", c.getPort());

    BufferedReader entree = null;
    ObjectOutputStream sortie = null;
    entree = new BufferedReader(new InputStreamReader(socket.getInputStream()));
    sortie = new ObjectOutputStream(socket.getOutputStream(socket, String retour_message=entree.readline();));
    getOutputStream();
    sortie.writeObject(m);
  }
}

public class ThreadClient implements Thread{
  private ObjectInputStream entree;
  private PrintWriter sortie;
  private Socket client;

  public void run(){
  Message m = (Message)(entree.readObject());
    sortie.println("Lu");
  }
}

public class Message{
  private short kind;
  private int type;
  private long cpt;
  private byte[] ip_src;
  private byte[] ip_dest;
  private String message;

  public Message(Message m){
    this.kind = m.kind;
   //etc pour tous les attributs
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

//QUESTION 6

public class ServeurUDP{
  public static void main(String[] args){
    while(1){
      Byte[] recvBuffer = new Byte[128];
      DatagrammPacket p = new DatagrammPacket(recvBuffer, recvBuffer.length());
      DatagrammSocket ds = new DatagrammSocket(3210); //exception
      while(1){
        ds.receive(p); //exception
        int retour = gestionMessage(p);
      }
    }

    public int gestionMessage(DatagrammPacket pac, DatagrammSocket ds){
      int ToR = -1;
      Message m = new Message(pac); //exception
      switch(m.getType()){
        case 1:
          Message envoi = new Message();
          envoi.setMessageEnvoi(pac);
          ToR = 1;
          ds.send(envoi);
        break;

        case 2:
          Message suppression = readMessage();
          suppression.setMessage(pac);
          ToR=1;
        break;

        case 3:
          Message archivage = new Message();
          archivage.setMessageArchi(pac);
          cls send(archivage);
        break;

        case 4:
          Message reception = new Message();
          reception.setMessageReception(pac)
          ds.send(reception);
        break;

        default:

        break;

      }
      return ToR;
    }
  }
}

//Envoyer
public class ClientEmission{
  static int port = 2248;
  static String adresse = "192.0.0.1";

  public static void main(String[] args){
    Message msg = new Message();
    DatagrammSocket s = new DatagrammSocket();
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    ObjectOutputStream oos= new ObjectOutputStream(baos);
    oos.write(m);
    oss.flush();
    byte[] buffer = new byte[120];
    remplirBuffer(buffer, msg);
    DatagrammPacket p = new DatagrammPacket(buffer, buffer.length(), InetAdress.getByName(adresse), port) ;
  }
}

//Réception
public class ClientReception{
  private int port = 3210;
  private byte[] tampon = new byte[1024];

  public static void main(String[] args){
    DatagrammSocket ds = new DatagrammSocket();
    DatagrammPacket dp = new DatagrammPacket(tampon, tampon.length());
    ByteArrayInputStream bais = new ByteArrayInputStream();
    ObjectInputStream ois= new ObjectInputStream(bis);
    ois.read(m);
    ois.flush();
    ds.receive(dp);
    String msg = new String(dp.getData(),0, dp.getLength());
    ds.close();
  }
}
