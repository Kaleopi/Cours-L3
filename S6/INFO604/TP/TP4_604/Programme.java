import java.lang.Thread;

public class Programme{
    public static void main(String[] args){
        MonThread helloWorld = new MonThread(0);
        MonThread helloWorld2 = new MonThread(1);

        Thread hwRunnable = new Thread(new MonThreadRunnable(0));
        Thread hwRunnable2 = new Thread(new MonThreadRunnable(1));
        helloWorld.start();
        helloWorld2.start();
        hwRunnable.start();
        hwRunnable2.start();
    }
}