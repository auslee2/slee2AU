/* Nov 19, 2015
 * Samuel Lee
 * Asteroid_thing
 */
 
   import java.awt.*;				// for Graphics, etc 
   import java.awt.geom.*;			// for Polygon
   import java.util.Random;      // for random number
 
 public class Firework2 extends Sprite {
 
      //constructor
      
      public Firework2(int new_xdim, int new_ydim){
         super(new_xdim, new_ydim);
         // generate random number
         Random randomGen = new Random();
         int randomIntW = randomGen.nextInt(new_xdim);
         int randomIntH = randomGen.nextInt(new_ydim);
         int randomIntxvel = randomGen.nextInt(10);
         int randomIntyvel = randomGen.nextInt(10);
         int randomInt1 = randomGen.nextInt(3);
         if (randomInt1 == 1){
            xvel = randomIntxvel; 
         }
         else{
            xvel = -randomIntxvel;
         }
         int randomInt2 = randomGen.nextInt(3);
         if (randomInt2 == 1){
            yvel = randomIntyvel; 
         }
         else{
            yvel = -randomIntyvel;
         }
         // assign values
         x = randomIntW;
         y = randomIntH;
         xdim = new_xdim;
         ydim = new_ydim;
         shape = new Polygon();
         //adding points
         shape.addPoint(-11,0); 
         shape.addPoint(-5,-5);
         shape.addPoint(-3,-9);
         shape.addPoint(0,-12);
         shape.addPoint(2,-6); 
         shape.addPoint(5,-5);
         shape.addPoint(9,0);
         shape.addPoint(5,4);
         shape.addPoint(4,9);
         shape.addPoint(0,9);
         shape.addPoint(-4,8);
     
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
      brush.setColor(Color.red);
      brush.drawPolygon(shape);
      g2d.rotate(-1/2*Math.PI);
      g2d.translate(-x,-y);
    }
   
 
 
 }
 
 