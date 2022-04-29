
package snake;

import java.awt.Dimension;
import java.awt.Toolkit;
import javax.swing.JFrame;

/**
 *
 * @author ereni
 */
public class GameFrame extends JFrame{
    private int width = 600;
    private int height = 600;
    public GameFrame() {       
        Ortala(width, height);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setResizable(false);
        piton viper = new piton();
        add(viper);
    }
    public void Ortala(int genislik, int yukseklik){
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        int PosX=0;
        int PosY=0;
        if (width+100 >dim.width){
            
            width = dim.width-100;
        }
        if (height +100>dim.height) {
            height = dim.height;
        }
        PosX = (dim.width-width)/2;
        PosY = (dim.height-height)/2;
        setBounds(PosX,PosY,width,height);
    }
}
