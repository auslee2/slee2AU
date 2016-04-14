/* Nov 19, 2015
 * Samuel Lee
 * ship
 */
 
   import java.awt.*;				// for Graphics, etc 
   import java.awt.geom.*;			// for Polygon

 
 public class Ship extends Sprite {
      private double acceleration;
    //constructor
      public Ship(int new_xdim, int new_ydim){
      super(new_xdim, new_ydim);
      x = new_xdim/2;
      y = new_ydim/2;
      xdim = new_xdim;
      ydim = new_ydim;
      xvel = 0;
      yvel = 0;
      acceleration = 2;
      shape = new Polygon();
      //shape.addPoint(0,0); // center
      shape.addPoint(5,-10); //x
      shape.addPoint(0,10); //-y
      shape.addPoint(-5,-10); //-x
      shape.addPoint(0,-7);
      
    
    }
    
    public void move(){
      x = (xdim+(x + (int)xvel)) % xdim;
      y = (ydim+(y + (int)yvel)) % ydim; 
     
    }
    
    public void leftturn(){
      orientation += Math.PI/7;
    }
    public void rightturn(){
      orientation -= Math.PI/7;
    }
    
    public void fireEngines(){
      xvel -= acceleration * Math.sin(orientation);  // x = x(initial) + vxt (our velocity per unit time * 1 unit)
      yvel += acceleration * Math.cos(orientation);
    }
    
     public void paint(Graphics brush){
      Graphics2D g2d = (Graphics2D)brush; 
      g2d.translate(x,y);
      g2d.rotate(orientation);
      brush.setColor(Color.orange);
      brush.drawPolygon(shape);
      g2d.rotate(-orientation);
      g2d.translate(-x,-y);
    }
 
 
 }