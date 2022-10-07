 public class Treasure extends GamePiece {
	  
   public Treasure() {
       super();
   } 
    public Treasure(int initPoints) {
    
     super(initPoints);
   } 
   
   public String getType(){
      return "Treasure";
   } 
   
   public String show(){
	 return "$";
   } 
}