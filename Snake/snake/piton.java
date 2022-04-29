
package snake;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.Random;
import javax.swing.JLabel;
import javax.swing.*;

/**
 *
 * @author ereni
 */
public class piton extends JLabel {
    public rodent head = new rodent();
    public food yem= new food();
    public Random rastgele=null;
    public Timer time= null;
    public ArrayList <rodent> tails = new ArrayList<rodent>();
    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2 = (Graphics2D)g;
        Rectangle2D dikdortgen = new Rectangle2D.Double(5,5,getWidth()-10,getHeight()-10);
        g2.setColor(Color.LIGHT_GRAY);
        g2.setStroke(new BasicStroke(10));
        g2.draw(dikdortgen);
        
    }
    piton(){
        rastgele= new Random(System.currentTimeMillis());
        addKeyListener(new moving()); //bunu ekleyince hareket ettirme aktiflesiyo
        setFocusable(true);//odağı buraya alıp hareketi sağlanıyo
        time = new Timer(30,new timercontrol());
        time.start();
        tails.add(head);
        for (int i=1;i<10;i++) {
            addtail();
        }
        add(yem);
        add(head);
    }
    public void addtail() {
        rodent K = tails.get(tails.size()-1).newtail();
        tails.add(K);
        add(K);
    }
    public void newfood(){
        int Width = getWidth() - 30 - yem.mgenislik;
        int Height = getHeight() -30 -yem.mgenislik;
        int posX = Math.abs(rastgele.nextInt())%Width;
        int posY = Math.abs(rastgele.nextInt())%Height;
        posX = posX -(posX%20)+20;
        posY = posY -(posY%20)+20;
        
        for(int i=0;i<tails.size();i++){
            if(posX == tails.get(i).getX() && posY == tails.get(i).getY()){
                newfood();
                return;
            }
        }
        yem.setPosition(posX, posY);
    }
    public void completeMovement() {
        for (int i=tails.size()-1;i>0;i--) {
            rodent onceki = tails.get(i-1);
            rodent sonraki= tails.get(i);
            tails.get(i).hareket();
            sonraki.yon=onceki.yon;
        }
        head.hareket();
    }
    class moving implements KeyListener{ //hareket ettirme metodları


        @Override
        public void keyPressed(KeyEvent e) {
            if(e.getKeyCode()== KeyEvent.VK_RIGHT) {
                if(head.yon != directions.sol)
                    head.yon=1;
            }
            if(e.getKeyCode()== KeyEvent.VK_LEFT) {
                if(head.yon != directions.sag)    
                    head.yon=-1;
            } 
            if(e.getKeyCode()== KeyEvent.VK_UP) {
                if(head.yon != directions.asagi)
                    head.yon=2;
            }
            if(e.getKeyCode()== KeyEvent.VK_DOWN) {
                if(head.yon != directions.yukari)
                    head.yon=-2;
            }
                            
        }

        @Override
        public void keyTyped(KeyEvent e) {
            }

        @Override
        public void keyReleased(KeyEvent e) {
            }
    }
    public boolean crashtest(){
        int cap = 12;
        int width =getWidth();
        int height= getHeight();
        if (head.getX()<=cap)
            return true;
        if (head.getX()>=width-cap*2)
            return true;
        if (head.getY()<=cap)
            return true;
        if (head.getY()>=height-2*cap)
            return true;
        for (int i=1;i<tails.size();i++) {
            int x = tails.get(i).getX();
            int y = tails.get(i).getY();
            if (x == head.getX() && y==head.getY())
                return true;
        }
        
        if(yem.getX() == head.getX() && yem.getY() == head.getY()){
            addtail();
            newfood();
            return false;
        }
        return false;
    }
    
    class timercontrol implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            completeMovement();
            if (crashtest())
                time.stop();
            
        }
        
    }    
}
