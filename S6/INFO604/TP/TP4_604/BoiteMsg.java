import java.lang.Exception;

public class BoiteMsg{
    protected boolean vide;
    protected String msg;

    public BoiteMsg(){
        this.vide = true;
        this.msg = "";
    }

    public boolean getVide(){
        return vide;
    }

    public synchronized int deposer(String msg){
        if(vide){
            this.msg = msg;
            this.vide = false;
            System.out.println("Message déposé dans la boîte.");
            return 0;
        }
        else{
            System.out.println("Impossible, la boîte est pleine.");
            return -1;
        }
    }

    public synchronized String recuperer(){
        if(!vide){
            return msg;
        }
        else{
            return "Rien à récupérer, la boîte est vide.";
        }
    }
}