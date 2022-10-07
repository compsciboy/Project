import java.util.Random;

public class TrollGame {
   private static final int INIT_PLAYER_POINTS = 160;
   private static final int PLAYER_POINTS_DEC = -10;
   private static final int TREASURE_POINTS = 500;
   private static final int ROWS = 8;
   private static final int COLS = 10;
   private Random rand;
   private GamePiece[][] gameBoard;
     int[] array;
   private int curPlayerRow, curPlayerCol;
   private int curTrollRow, curTrollCol;
   private int point=INIT_PLAYER_POINTS;
   private boolean playerWins;
   private boolean playerLoses;

   public TrollGame () {
      rand = new Random();
      curPlayerRow=0;
      curPlayerCol=0;
      playerWins=false;
      playerLoses=false;
      initBoard(ROWS, COLS, rand);
   }

   public TrollGame (int seed){
      rand = new Random(seed);
      curPlayerRow=0;
      curPlayerCol=0;
      playerWins=false;
      playerLoses=false;
      initBoard(ROWS, COLS, rand);

   }

   public void movePlayer(String direction) {
  int[] array=new int[2];
   if((!playerWins())&&(!playerLoses())){
      if((direction.equals("u"))&&(curPlayerRow!=0)){
         overwritePosition(curPlayerRow, curPlayerCol, curPlayerRow-1, curPlayerCol);
         curPlayerRow-=1;
      }
      if((direction.equals("d"))&&(curPlayerRow!=7)){
         overwritePosition(curPlayerRow, curPlayerCol, curPlayerRow+1, curPlayerCol);
         curPlayerRow+=1;
      }
      if((direction.equals("r"))&&(curPlayerCol!=9)){
         overwritePosition(curPlayerRow, curPlayerCol, curPlayerRow, curPlayerCol+1);
         curPlayerCol+=1;
      }
      if((direction.equals("l"))&&(curPlayerCol!=0)){
         overwritePosition(curPlayerRow, curPlayerCol, curPlayerRow, curPlayerCol-1);
         curPlayerCol-=1;
      }          
           adjustPlayerLifeLevel(curPlayerRow, curPlayerCol);
           point =gameBoard[curPlayerRow][curPlayerCol].getLifePoints();
 
            }
           array=calcNewTrollCoordinates(curPlayerRow, curPlayerCol, curTrollRow, curTrollCol);
         overwritePosition(curTrollRow, curTrollCol, array[0], array[1]);
        curTrollRow=array[0];
       curTrollCol=array[1];
       if((((!playerAlive(curPlayerRow, curPlayerCol)))&&(curPlayerRow!=7))&&((curPlayerCol!=9))){
       overwritePosition(curPlayerRow, curPlayerCol, curTrollRow, curTrollCol);
       }
   }
   
   public boolean playerWins(){
   if(playerFoundTreasure(curPlayerRow, curPlayerCol)){
      return true;}
      else return false;
   }
   
   public boolean playerLoses(){
   if(!playerAlive(curPlayerRow, curPlayerCol))
      return true;
      else return false;
   }
   
   public int getTreasurePoints(){
      return TREASURE_POINTS;
   }

   public void resetGame(){
   curPlayerRow=0;
   curPlayerCol=0;
      gameBoard = new GamePiece[ROWS][COLS];
            curTrollRow=getRandTrollRow(rand, ROWS);
      curTrollCol=getRandTrollCol(rand, COLS);
      for(int i=0; i<ROWS; i++){
         for(int j=0; j<COLS; j++){
            gameBoard[i][j]=new EmptyPiece();}}
      gameBoard[curPlayerRow][curPlayerCol]= new Player();
      gameBoard[ROWS-1][COLS-1]= new Treasure();
      gameBoard[curTrollRow][curTrollCol]= new Troll();
   }
   
   public String getGameStr() {
      StringBuilder outStr = new StringBuilder();
      for(int i=0;i<ROWS;i++) {
         for(int j=0;j<COLS;j++) 
            outStr.append("|").append(gameBoard[i][j].show());
         outStr.append("|").append(System.getProperty("line.separator"));
      }
      return outStr.toString();
   }

   private GamePiece[][] initBoard(int rows, int cols, Random rand) {
     gameBoard = new GamePiece[rows][cols];
      curTrollRow=getRandTrollRow(rand, rows);
      curTrollCol=getRandTrollCol(rand, cols);
      for(int i=0; i<rows; i++){
         for(int j=0; j<cols; j++){
            gameBoard[i][j]=new EmptyPiece();}}
      gameBoard[curPlayerRow][curPlayerCol]= new Player(point);
      gameBoard[rows-1][cols-1]= new Treasure(TREASURE_POINTS);
      gameBoard[curTrollRow][curTrollCol]= new Troll();
      return gameBoard;
   }
   
   private boolean playerAlive(int curPlayerRow, int curPlayerCol){
   String a=gameBoard[curPlayerRow][curPlayerCol].getType();
      if((gameBoard[curPlayerRow][curPlayerCol].isAlive())&&(a.equals("Player"))){
         return true;}
      else 
         return false;
   }
   
   private void adjustPlayerLifeLevel(int curPlayerRow, int curPlayerCol){
      gameBoard[curPlayerRow][curPlayerCol].updateLifePoints(PLAYER_POINTS_DEC);
   }
   
   private boolean playerFoundTreasure(int playerRow, int playerCol){
   if((playerRow==(ROWS-1))&&(playerCol==(COLS-1)))
      return true;
      else return false;
   }
   
   private int getRandTrollRow(Random rand, int numRows){
      int a= rand.nextInt(numRows-1)+1;
      return a;
   }
   
   private int getRandTrollCol(Random rand, int numCols){
      int a= rand.nextInt(numCols-1)+1;
      return a;
   }

   private int[] calcNewTrollCoordinates(int playerRow, int playerCol, int trollRow, int trollCol){
int[] array= {trollRow, trollCol};
int row= trollRow-playerRow;
int col= trollCol-playerCol;
if((row>0)&&(col<=0)){
if(-col<row){
array[0]=trollRow-1;}
else if(-col>=row){
array[1]= trollCol+1;}}
if((row>=0)&&(col>0)){
if(col>=row){
array[1]= trollCol-1;}
else if(row>col){
array[0]= trollRow-1;}}
if((row<0)&&(col>=0)){
if(-row<=col){
array[1]=trollCol-1;}
else if(-row>col){
array[0]=trollRow+1;}}
if((row<=0)&&(col<0)){
if(-row>=-col){
array[0]=trollRow+1;}
else if(-row<=-col){
array[1]=trollCol+1;}}
   return array;
   }

   private void overwritePositionWithEmpty(int row, int col){
      gameBoard[row][col]= new EmptyPiece();
   }
   
   private void overwritePosition(int oldRow, int oldCol, int newRow, int newCol){
      String old= gameBoard[oldRow][oldCol].getType();
      String neww= gameBoard[newRow][newCol].getType();
if(old.equals("Player")){
if(neww.equals("Troll")){
overwritePositionWithEmpty(oldRow,oldCol);
gameBoard[newRow][newCol]=new Troll();
}
else{
gameBoard[newRow][newCol]=new Player(point);
overwritePositionWithEmpty(oldRow,oldCol);
}}
if(old.equals("Troll")){
overwritePositionWithEmpty(oldRow,oldCol);

gameBoard[newRow][newCol]=new Troll();
}
   }
      

   private void swapPosition(int curRow, int curCol, int newRow, int newCol){
   String neww = gameBoard[newRow][newCol].getType();
   if(neww.equals("Troll")){
   gameBoard[curRow][curCol]=gameBoard[newRow][newCol];
   gameBoard[newRow][newCol]=new Troll();
   }
   if(neww.equals("Player")){
   gameBoard[curRow][curCol]=gameBoard[newRow][newCol];
   gameBoard[newRow][newCol]=new Troll();
   }

 
      
   }}