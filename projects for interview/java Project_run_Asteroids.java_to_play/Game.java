/**
 * Game class
 * A window containing a painted canvas, which is drawn on by a sub-class, such as Asteroids
 */
 
import java.awt.*;				// for Canvas, etc
import java.awt.event.*;		// for KeyListener

abstract class Game extends Canvas implements KeyListener {
  
   // constants
   protected final static int NOKEY = -1;			// if no key is currently being pressed

   // fields (variables)
   protected boolean on = true;						// if the game is on, let's play!
   protected int width, height;						// size of the screen
   protected Image buffer;								// graphics buffer for drawing
	protected int lastKeyPressed;						// the key that the user pressed
  
  
   /////////////////
	// Constructor //
	/////////////////
	
   /**
	 * GAME
    * The constructor.
	 * Arguments:  name (displayed in the title bar), newWidth and 
	 * newHeight (width and height of the window)
	 */
	public Game(String name, int newWidth, int newHeight) {
	   width = newWidth;
	   height = newHeight;
	  
	   // Set up the window
		Frame frame = new Frame(name);
      frame.add(this);
      frame.setSize(width,height);
      frame.setVisible(true);
      frame.setResizable(false);
      frame.addWindowListener(new WindowAdapter() { 
         public void windowClosing(WindowEvent e) {System.exit(0);} 
      });
		
		// make this frame the listener for key presses
		frame.addKeyListener(this);
		lastKeyPressed = NOKEY;			// initialize the keypress to be NOKEY
  
      // create the image buffer used for drawing
      buffer = createImage(width, height);
	}
	
	//////////////////////
	// Instance Methods //
	//////////////////////
	
   /**
	 * PLAY
	 * The method that plays the game, continously looping to look for key presses,
	 * and redrawing the screen.
    */
   public void play()
   {  // loop until the game ends
      while (on)
      {  // time delay to make it run at a reasonable speed, sleep for 100 milliseconds
         sleep(100);
	   	// see if a key has been pressed
         handleKeyPress();
			// redraw the screen.
			// NOTE:  repaint() calls the update() method automatically, which in turn calls paint()
	   	repaint();
      }
   }


  /**
	 * UPDATE
	 * paints to a buffer then to the screen. This is done
    * to avoid a choppy painting experience if repainted in pieces.
	 */
   public void update(Graphics brush) {
      paint(buffer.getGraphics());
		brush.drawImage(buffer,0,0,this);
   }

  
   /**
	 * PAINT
	 * An abstract method (so must be implemented by the subclass)
	 * used to draw the screen.  This method is called by the update method,
	 * which is in turn called by the play method.
	 */
   abstract public void paint(Graphics brush);
	
	
	/**
	 * HANDLEKEYPRESS
	 * An abstract method (so must be implemented by the subclass)
	 * Called by the plan() method to handle user input --> the key
	 * to be processed is stored in lastKeyPressed (a variable of this class)
	 */
   abstract public void handleKeyPress();
  
   
   /**
	 * SLEEP
	 * A helper function used in 'update'.
	 */
   private void sleep(int time) {
      try {Thread.sleep(time);} catch(Exception exc){};
   }
	
	
   //////////////////////////
	// Key Listener Methods // Required to be implemented due to the KeyListener interface
   //////////////////////////
	
   public void keyPressed(KeyEvent e)
   {
      lastKeyPressed = e.getKeyCode();  	// get the code for the last key pressed
   }
  
   public void keyReleased(KeyEvent e)
   {
      lastKeyPressed = NOKEY;        		// reset the last key pressed to NOKEY
   }
  
   public void keyTyped(KeyEvent e)
   {
      //ignored
   }

} // end Class Game