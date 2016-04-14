/* Nov 19, 2015
 * Samuel Lee
 * Asteroid_thing
 */
 
   import java.awt.*;				// for Graphics, etc 
   import java.awt.geom.*;			// for Polygon
   import java.util.Random;      // for random number
 
 public class Asteroid_thing2 extends Sprite {
 
    //constructor
      public Asteroid_thing2(int new_xdim, int new_ydim){
      super(new_xdim, new_ydim);
      // generate random number
      Random randomGen = new Random();
      int randomIntW = randomGen.nextInt(new_xdim);
      int randomIntH = randomGen.nextInt(new_ydim);
      int randomIntxvel = randomGen.nextInt(10);
      int randomIntyvel = randomGen.nextInt(10);
      
      // generate negative value with random number
      int randomInt1 = randomGen.nextInt(3);
      int randomInt2 = randomGen.nextInt(3);
      // determine if its negative or positive
      if (randomInt1 == 1){
         xvel = randomIntxvel; 
      }
      else{
         xvel = -randomIntxvel;
      }
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
      xvel = randomIntxvel;
      yvel = randomIntyvel;
      shape = new Polygon();
      
      // adding points to polygon
      
      shape.addPoint(-22,0); 
      shape.addPoint(-10,-10);
      shape.addPoint(-6,-18);
      shape.addPoint(0,-24);
      shape.addPoint(4,-12); 
      shape.addPoint(10,-10);
      shape.addPoint(18,0);
      shape.addPoint(10,8);
      shape.addPoint(8,18);
      shape.addPoint(0,18);
      shape.addPoint(-8,16);
     
    }
    
    // move method
    public void move(){
      y = (ydim+(y + (int)xvel)) % ydim;  // make it stay in the y dimension
      x = (xdim+(x + (int)yvel)) %xdim;    // make it stay in the x dimension
    }
    // pain method
    public void paint(Graphics brush){   
      Graphics2D g2d = (Graphics2D)brush; 
      g2d.rotate(1/2*Math.PI);
      g2d.translate(x,y);
      brush.setColor(Color.blue);
      brush.drawPolygon(shape);
      g2d.rotate(-1/2*Math.PI);
      g2d.translate(-x,-y);
    }
   
 
 
 }
 
 