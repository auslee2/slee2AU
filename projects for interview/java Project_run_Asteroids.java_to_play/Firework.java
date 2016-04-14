/* Nov 19, 2015
 * Samuel Lee
 * Asteroid_thing
 */
 
   import java.awt.*;				// for Graphics, etc 
   import java.awt.geom.*;			// for Polygon
   import java.util.Random;      // for random number
 
 public class Firework extends Sprite {
 
      //constructor
      
      public Firework(int new_xdim, int new_ydim){
         super(new_xdim, new_ydim);
         // generate random number
         Random randomGen = new Random();
         int randomIntW = randomGen.nextInt(new_xdim);
         int randomIntH = randomGen.nextInt(new_ydim);
         //assign values
         x = randomIntW;
         y = randomIntH;
         xdim = new_xdim;
         ydim = new_ydim;
         xvel = randomIntW;
         yvel = randomIntH;
         shape = new Polygon();
         //adding points
         shape.addPoint(2,0); 
         shape.addPoint(1,1);
         shape.addPoint(0,2);
         shape.addPoint(-1,1);
         shape.addPoint(-2,0); 
         shape.addPoint(-1,-1);
         shape.addPoint(0,-2);
         shape.addPoint(1,-1);
     
    }
    public void move(){
      x = (xdim+(x + (int)xvel)) % xdim;
      y = (ydim+(y + (int)yvel)) % ydim; 
    }
    // paint method
    public void paint(Graphics brush){
      Graphics2D g2d = (Graphics2D)brush; 
      g2d.rotate(1/2*Math.PI);
      g2d.translate(x,y);
      brush.setColor(Color.pink);
      brush.drawPolygon(shape);
      g2d.rotate(-1/2*Math.PI);
      g2d.translate(-x,-y);
    }
   
 
 
 }
 
 