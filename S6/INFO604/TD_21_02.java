//PRODUCTEURS / CONSOMMATEURS

import java.lang.InterruptedException;
import java.lang.invoke.ConstantCallSite;
public class BoiteMsg{
    private String message;
    private boolean vide = true;


    //synchronized au niveau de la signature : bloque toute la méthode.
    //synchronized dans la fonction : bloque juste une partie synchronized{bla bla bla}
    public synchronized String recuperer(){
        while(vide){
            try{
                wait();
            }
            catch(InterruptedException e){
                /*blablabla*/
            }
        }
        vide = true;
        notifyAll();
        return message;
    }

    public synchronized void deposer(String message){
        while(!vide){
            try{
                wait();
            }
            catch(InterruptedException e){
                /*blabla*/
            }
        }
        vide = false;
        this.message = message;
        notifyAll();
    }
}

public class Producteur implements Runnable{
    private BoiteMsg boiteMsg;

    public Producteur(BoiteMsg boiteMsg){
        this.boiteMsg = boiteMsg;
    }

    public void run(){
        String[] messages = {"vive","info604","et le professeur"};
        for(int i=0 ; i<messages.length ; i++){
            boiteMsg.deposer(messages[i]);
            try{
                Thread.sleep(5000);
            }
            catch(InterruptedException e){/*blabla*/}
        }
        boiteMsg.deposer("termine");
    }
}

public class Consommateur implements Runnable{
    private BoiteMsg boiteMsg;

    public Consommateur(BoiteMsg boiteMsg){
        this.boiteMsg = boiteMsg;
    }
    
    public void run(){
        boolean termine = false;
        String message;
        while(!termine){
            message=boiteMsg.recuperer();
            System.out.println("Message reçu : "+message);
            if(message.equals("termine")){
                termine = true;
            }
            try{
                Thread.sleep(5000);
            }
            catch(InterruptedException e){
                /*blabla*/
            }
        }
    }
}

public class Main{
    public static void main(String[] args){
        BoiteMsg boiteMsg = new BoiteMsg();
        (new Thread(new Producteur(boiteMsg))).start();
        (new Thread(new Consommateur(boiteMsg))).start();
    }
}   
