
package snake;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import javax.swing.JLabel;

/**
 *
 * @author ereni
 */
public class rodent extends JLabel{
    public int cap = 10;
    public int yon= directions.sag;
    rodent() {
        setBounds(100,100,cap,cap);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g); 
        Graphics2D g2 = (Graphics2D)g;
        Rectangle2D dikdortgen = new Rectangle2D.Double(1,1,getWidth()-2,getHeight()-2);
        g2.setColor(Color.darkGray);
        g2.setStroke(new BasicStroke(4));
        g2.draw(dikdortgen);
    }
    public void toLeft(){
        int posX = getX();
        int posY = getY();
        posX -= cap;
        setBounds(posX, posY, cap, cap);
    }
    public void toRight(){
        int posX = getX();
        int posY = getY();
        posX += cap;
        setBounds(posX, posY, cap, cap);
    }
    public void toUp(){
        int posX = getX();
        int posY = getY();
        posY -= cap;
        setBounds(posX, posY, cap, cap);
    }
    public void toDown(){
        int posX = getX();
        int posY = getY();
        posY += cap;
        setBounds(posX, posY, cap, cap);
    }
    public rodent newtail() {
        rodent A = new rodent();
        int posX = getX();
        int posY = getY();
        A.setBounds(posX, posY, cap, cap);
        A.yon = -yon;
        A.hareket();
        A.yon = yon;
        return A;
    }
    public void hareket() {
        if(yon==directions.sag) {
            toRight();
        }
        if(yon==directions.sol) {
            toLeft();
        }
        if(yon==directions.asagi) {
            toDown();
        }
        if(yon==directions.yukari) {
            toUp();
        }
    }
    
}
