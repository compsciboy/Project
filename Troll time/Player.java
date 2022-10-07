 public class Player extends GamePiece {
	  
   public Player() {
       super();
   } 
   public Player(int initPoints) {
    
     super(initPoints);
   } 
   
   public String getType(){
      return "Player";
   } 
   
   public String show(){
	 return "P";
   } 
}