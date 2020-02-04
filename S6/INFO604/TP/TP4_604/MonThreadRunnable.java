import java.lang.Runnable;
import java.lang.Thread;

public class MonThreadRunnable implements Runnable{
    int id;

    public MonThreadRunnable(int id){
        this.id = id;
    }

    /*
    méthode exécutée lors de l'appel de la méthode start()
    */
    public void run(){
        System.out.println("*** Info MonThreadRunnable "+id+" ***\n\tThread ID : "+Thread.currentThread().getId()+"\n\tThread name : "+Thread.currentThread().getName()+"\n");
    }
}