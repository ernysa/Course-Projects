package snake;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;
import javax.swing.JLabel;

/**
 *
 * @author ereni
 */
public class food extends JLabel{
    food() {
        setPosition(150,150);
    }
    public int mgenislik= 20;
    @Override
    public void paint(Graphics g) {
        super.paint(g); 
        Graphics2D g2 = (Graphics2D)g;
        Ellipse2D elps = new Ellipse2D.Double(1,1,mgenislik-10,mgenislik-10);
        g2.setColor(Color.BLACK);
        g2.setStroke(new BasicStroke(2));
        g2.draw(elps);
        g2.fill(elps);
    }
    public void setPosition(int posX, int posY){
        setBounds(posX, posY, mgenislik, mgenislik);
    }
    
}
