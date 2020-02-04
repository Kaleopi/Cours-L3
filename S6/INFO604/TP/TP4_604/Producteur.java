import java.lang.Exception;
import java.lang.Thread;

public class Producteur implements Runnable{
    protected String[] tabMsg = new String[10];
    protected BoiteMsg boite;

    public Producteur(BoiteMsg boite){
        this.boite = boite;
        for(int i=0 ; i<tabMsg.length ; i++){
            tabMsg[i] = "message"+i;
        }
    }

    public synchronized void run(){
        int i = 0;
        while(i<tabMsg.length){
            if(boite.getVide()){
                deposer(boite, tabMsg[i]);
                i++;
            }
            try {
                Thread.sleep(4000);
            } catch(InterruptedException ex) {
                System.out.println("Thread interrompu.");
                Thread.currentThread().interrupt();
            }
        }
        
        while(boite.getVide()){
            deposer(boite, "termine");
            try{
                Thread.sleep(4000);
            } catch(InterruptedException ex) {
                System.out.println("Thread interrompu.");
                Thread.currentThread().interrupt();
            }            
        }
    }

    public synchronized void deposer(BoiteMsg boite, String msg){
        boite.deposer(msg);
    }
}