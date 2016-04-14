/**
 * Asteroids class
 * An extension of the Game class that makes this game 
 * function similar to the classic Asteroids game
 * 
 */
import java.awt.*;				// for Graphics, etc
import java.awt.geom.*;			// for Polygon
import java.util.Random;      // for random number

class Asteroids extends Game {

   // constants
   public static final boolean DEBUG = true;	// debugging flag to print debugging messages
 
   // fields (variables)
   Ship myShip;								                           // the ship
	Asteroid_thing[] thing1 = new Asteroid_thing[3];					// an array of small stuff- asteroids1
   Asteroid_thing2[]	thing2 = new Asteroid_thing2[3];             // an array of big stuff- asteroids2                    
   Bullet[] bullet = new Bullet[3];                       // a Bullet;
   Star[] star = new Star[20];
   Firework[] firework = new Firework[6];
   Firework2[] firework2 = new Firework2[3];
   public int bcount = 0;
   public boolean space = false;
   public boolean fire = false;
   public boolean back = false;
   /////////////////
	// Constructor //
	/////////////////
   public Asteroids(int newWidth, int newHeight)  {
      super("Asteroids!",newWidth,newHeight);  // call the Game class's constructor      
      //Array 
      //star set up 
      for(int i=0; i< 20; i++){
         star[i] = new Star(newWidth, newHeight);
      }
      //firework
      for(int i=0; i< 6; i++){
         firework[i] = new Firework(newWidth, newHeight);
      }
      //firework2
      for(int i=0; i< 3; i++){
         firework2[i] = new Firework2(newWidth, newHeight);
      }
	   // set up the ship
		myShip = new Ship(newWidth, newHeight);
		// set up the asteroids
      for(int i=0; i< 3; i++){
         thing1[i] = new Asteroid_thing(newWidth, newHeight);
      }
      for(int i=0; i< 3; i++){
         thing2[i] = new Asteroid_thing2(newWidth, newHeight);
      }
      
      
      // set up the bullet
      for(int i=0; i< 3; i++){
         bullet[i] = new Bullet(newWidth, newHeight);
         
      }
   
   }
  
  
   //////////////////////
	// Instance Methods //
	//////////////////////
	
	/**
	 * PAINT
	 * Draw everything in the game, every 10th of a second (automatically called by the Game class)
	 * --> This is the method that really MAKES THE GAME GO, moving the objects, drawing them, 
	 * --> checking for collisons, etc.  You can almost think of this method as working like the equivalent 
	 * --> of the "main" function in the C language.
	 */
   public void paint(Graphics brush) {
 	
	   Graphics2D g2d = (Graphics2D)brush;  		// cast the brush to a Graphics2D style so we can rotate it
		
	   // paint the background
      g2d.setColor(Color.black);
      g2d.fillRect(0,0,width,height);
						
	   // move and paint the ship
	   
      myShip.paint(brush);
	   myShip.move();
      // move and paint the asteroids
      //Asteroids 1
      for(int i=0; i< 3; i++){
          if(thing1[i].getAlive()){
            thing1[i].paint(brush);
            thing1[i].move();
          } 
      }
      //Asteroids 2
      for(int i=0; i< 3; i++){
          if(thing2[i].getAlive()){ 
            thing2[i].paint(brush);
            thing2[i].move();
          }   
      }
      
      //star
      for(int i=0; i< 20; i++){
         star[i].paint(brush);
      }
      
      //firework
      if(fire==true){
         for(int i=0; i< 6; i++){
         firework[i].move();
         firework[i].paint(brush);
         }
         for(int i=0; i< 3; i++){
         firework2[i].move();
         firework2[i].paint(brush);
         }
      }
      //bullet
      for(int i=0; i< 3; i++){
         if(space ==true){
            pointbullet();  //pointing bullet based on ship info.
            space =false;
         }
         // else if(back == true){
//             backfire();
//          }
         bullet[i].move();
         bullet[i].paint(brush);
         
      }
       
      
      //check for collision ship w/ thing
      for(int i=0; i< 3; i++){ 
         if(myShip.collidesWith(thing1[i])){
            on = false;
            //set on = false to pause the game without shutting down
            System.out.println("Game over!");
        
         }
         if(myShip.collidesWith(thing2[i])){
          on = false;
          //set on = false to pause the game without shutting down
          System.out.println("Game over!");
        
         }
         //check for collision bullet w/ thing
         for(int j=0;j<3;j++){
            if(bullet[j].collidesWith(thing1[i])&&thing1[i].getAlive()){
               thing1[i].setAlive(false);
            }
            if(bullet[j].collidesWith(thing2[i])&&thing2[i].getAlive()){
               thing2[i].setAlive(false);
               startfire(thing2[i].getx(),thing2[i].gety());
               
            }
         } 
      
      }
      
   }
	
	
	/**
	 * HANDLEKEYPRESS
	 * React to the user's input by changing the position of the ship on the screen
	 * This is called every tenth of a second.
	 */
	public void handleKeyPress() {
		// if they pressed the up key (38), speed up, and we can only fire forward (no retrorockets)
		if (lastKeyPressed == 38)
		{  
         myShip.fireEngines();    
         //write a method in ship call fire rocket
		}
		// if they pressed the left key (37), rotate left
		else if (lastKeyPressed == 37)
		{  
         myShip.leftturn();		
		}
		// if they pressed the right key (39), rotate right
		else if (lastKeyPressed == 39)
		{  
         myShip.rightturn();
		}
		// if they press the space bar (32), fire a missile
		else if (lastKeyPressed == 32)
		{
         space = true;
		}
      else if(lastKeyPressed == 40)
      {
         back = true;
      }
		// if they press q or Q (81), quit!
		else if (lastKeyPressed == 81)
		{   System.exit(0);
		}
	}
   
   public void startfire(int x, int y){
      fire = true;
      for(int i=0; i<6;i++){
         firework[i].setx(x);
         firework[i].sety(y);
      }
      for(int i=0; i<3;i++){
         firework2[i].setx(x);
         firework2[i].sety(y);
      }
   }  
	public void pointbullet(){
      bullet[bcount].setx(myShip.getx());
      bullet[bcount].sety(myShip.gety());
      bullet[bcount].setOrientation(myShip.getOrientation());
      bullet[bcount].setxvel(myShip.getxvel());
      bullet[bcount].setyvel(myShip.getyvel());
      bullet[bcount].vel();
      bullet[bcount].move();
      bcount++;
      if(bcount==3) {
         bcount =0;
      }
   }
   // public void backfire(){
//       bullet[bcount].setx(myShip.getx());
//       bullet[bcount].sety(myShip.gety());
//       bullet[bcount].setOrientation(myShip.getOrientation());
//       bullet[bcount].setxvel(myShip.getxvel());
//       bullet[bcount].setyvel(myShip.getyvel());
//       bullet[bcount].vel();
//       bullet[bcount].move();
//       bcount++;
//       if(bcount==3) {
//          bcount =0;
//       }
//   }  
   //////////
	// main //
	//////////
	public static void main (String[] args) {
	   // determine size of screen, will make window nearly full screen
      // determine the screen size of this computer 
      // (see: http://www.roseindia.net/java/java-get-example/screen-dimensions.shtml)
      Toolkit toolkit = Toolkit.getDefaultToolkit (); 
      Dimension dim = toolkit.getScreenSize();

	   // create a new game, and start playing it right away
      Asteroids asteroid = new Asteroids(dim.width, dim.height-200);
		asteroid.play();
   }
}