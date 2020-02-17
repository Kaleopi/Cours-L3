import java.lang.Thread;


public class MonThread extends Thread{
    int id;

    public MonThread(int id){
        this.id = id;
    }

    /*
    méthode exécutée lors de l'appel de la méthode start()
    */
    public void run(){
        System.out.println("*** Info MonThread "+id+" ***\n\tThread ID : "+this.getId()+"\n\tThread name : "+this.getName()+"\n");
    }
}