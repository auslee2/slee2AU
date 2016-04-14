/* Nov 10, 2015
 * Samuel Lee
 * lab #11
 * Due:  At the end of day today, through Canvas.
 * Objective: create a Java class to represent a Sprite:  an object that could be drawn on a screen, in an Asteroids game
 */
 
  
   import java.awt.*;				// for Graphics, etc 
   import java.awt.geom.*;			// for Polygon
 
public class Sprite {
   protected int x;                //the current x position, an integer
   protected int y;                //the current y position, an integer
   protected int xdim;             //the width of the screen, in the x dimension, an integer
   protected int ydim;             //the height of the screen, in the y dimension, an integer
   protected double xvel;       //the current velocity in the x direction, a double
   protected double yvel;       //the current velocity in the y direction, a double
   protected Polygon shape;
   protected double orientation;
   protected boolean alive;   
     
  //////////////////
  // Constructors //
  //////////////////
  
  /** 
   * Construct a new Sprite given its data
   * @param new_x the current x position of the Sprite
	* @param new_y the current y position of the Sprite
	* @param the width of the screen, in the x dimension, an integer
   * @param the width of the screen, in the y dimension, an integer
   * @param the current velocity in the x direction, a double
	* @param the current velocity in the y direction, a double
   * @param boolean alive to see if obj is alive in game
   */
   
public Sprite(int new_xdim, int new_ydim) {
    xdim = new_xdim;
    ydim = new_ydim;
    x = 0;
    y = 0;
    xvel = 0.0;
    xvel = 0.0;
    orientation = Math.PI;
    alive = true;
  }   
  
  /////////////
  // Getters //
  /////////////
   

  public boolean getAlive(){
      return alive;
  }

  /**
   * Accessor for the current x position
   * @return the current x position of the Sprite
   */
   
  public int getx() {
    return x;
  }

  /**
   * Accessor for the current y position
   * @return the current y position of the Sprite
   */
  public int gety() {
    return y;
  }
    /**
   * Accessor for the current x direction
   * @return the current x direction of the Sprite
   */
  public double getxvel() {
    return xvel;
  }
   
   /**
   * Accessor for the first name
   * @return the current y direction of the Sprite
   */
  public double getyvel() {
    return yvel;
  }
  
  public double getOrientation(){
    return orientation;
  }
  
  /////////////
  // Setters //
  /////////////

  /**
   * Setter for current x position
   * @param newx the revised the current x position of the Sprite
   */
  public void setx(int newx) {
    x = newx;
  }
   /**
   * Setter for current y position
   * @param newy the revised the current y position of the Sprite
   */
  public void sety(int newy) {
    y = newy;
  }
   /**
   * Setter for current x direction
   * @param newxdirect the revised the current x direction of the Sprite
   */
  public void setxvel(double newxvel) {
    xvel = newxvel;
  }
   /**
   * Setter for current y direction
   * @param newydirect the revised the current y direction of the Sprite
   */
  public void setyvel(double newyvel) {
    yvel = newyvel;
  }
  
  public void setOrientation(double newOrientation){
   orientation = newOrientation;
  }
  public void setAlive(boolean update){
     alive = update;
  }
  
  //Collision handler
  public boolean collidesWith(Sprite otherSprite){
      Rectangle2D myBounds = shape.getBounds();  // your variable names may differ
      myBounds.setRect(x, y, myBounds.getWidth(), myBounds.getHeight());
      Rectangle2D otherBounds = otherSprite.shape.getBounds();
      otherBounds.setRect(otherSprite.getx(), otherSprite.gety(),otherBounds.getWidth(), otherBounds.getHeight());
      return myBounds.intersects(otherBounds); 
  }
    
  ///////////////////////////////
  // main() method for testing //
  ///////////////////////////////
  
  public static void main(String[] args) {
     // create objects to represent 3 people
     Sprite mySprite = new Sprite(300, 400);

	  // use Class method to get current position
	  System.out.println("Current position: x_" + mySprite.getx()+" y_ " + mySprite.gety());
	  
	  // use Instance method to get current direction
	  System.out.println("Current velocity: x_ " + mySprite.getxvel()+ " y_" + mySprite.getyvel());
	  
     // manually get x,y,xdirect,ydirect
     mySprite.setx(10);
     mySprite.sety(100);
     mySprite.setxvel(13);
     mySprite.setyvel(15);
     
     // use Class method to get updated position
	  System.out.println("Current position: x_" + mySprite.getx()+" y_ " + mySprite.gety());
	  
	  // use Instance method to get updated direction
	  System.out.println("Current velocity: x_ " + mySprite.getxvel()+ " y_" + mySprite.getyvel());
	}
    


} // Class Sprite