/* Nov 19, 2015
 * Samuel Lee
 * Bullet
 */
 
   import java.awt.*;				// for Graphics, etc 
   import java.awt.geom.*;			// for Polygon

   
 public class Bullet extends Sprite {
      public double acceleration;
      //constructor
      public Bullet(int new_xdim, int new_ydim){
         super(new_xdim, new_ydim);
         x = new_xdim/2;
         y = new_ydim/2;
         xdim = new_xdim;
         ydim = new_ydim;
         xvel = 0;
         yvel = 0;
         acceleration = 14;
         shape = new Polygon();
         shape.addPoint(1,2); //x
         shape.addPoint(-1,2);
         shape.addPoint(-1,-1); //-y
         shape.addPoint(1,-1); //-x
         
      
     
      }
 
    public void move(){
      x = (xdim+(x + (int)xvel*2)) % xdim;
      y = (ydim+(y + (int)yvel*2)) % ydim; 
    }
    //velocity method, getting ship's velocity and shoot out
    public void vel(){
      xvel -= acceleration * Math.sin(orientation);  // x = x(initial) + vxt (our velocity per unit time * 1 unit)
      yvel += acceleration * Math.cos(orientation);
    }
    //paint method
    public void paint(Graphics brush){
      Graphics2D g2d = (Graphics2D)brush; 
      g2d.translate(x,y);
      g2d.rotate(1/2*Math.PI);
      brush.setColor(Color.white);
      brush.drawPolygon(shape);
      g2d.rotate(-1/2*Math.PI);
      g2d.translate(-x,-y);
    }
   
 
 
 }
 
 