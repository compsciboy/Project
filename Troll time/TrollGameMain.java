import java.util.Scanner;

public class TrollGameMain {
  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    String inputStr = " ";
    boolean keepPlaying = true;
    boolean gameOver = false;
    int numGamesPlayed = 0;
    int playerWinCount = 0;
    int playerTotalScore = 0;
    TrollGame game = new TrollGame(123);
    System.out.println("Welcome to the Troll Game.");
    System.out.println(game.getGameStr());
	 while(keepPlaying){
      if(gameOver) {
         System.out.println("Enter Y to play again, X to quit.");
         inputStr = scan.nextLine();
         if(inputStr.equalsIgnoreCase("X"))
	         break;
         else if(inputStr.equalsIgnoreCase("Y")){
            game.resetGame();
            gameOver = false;
            System.out.println(game.getGameStr());
         }
      }
      else if(!gameOver) {
          System.out.println("Enter your move: u, d, r, l.");
          inputStr = scan.nextLine();
          game.movePlayer(inputStr);
          System.out.println(game.getGameStr());
          if(game.playerLoses()){
             System.out.println("Player loses!");
             numGamesPlayed++;
             gameOver = true;
             showGameSummary(numGamesPlayed, playerWinCount, playerTotalScore);
          }
          else if(game.playerWins()){
             System.out.println("Player wins!");
             playerWinCount++;
             numGamesPlayed++;
             playerTotalScore+=game.getTreasurePoints();
             gameOver = true;
             showGameSummary(numGamesPlayed, playerWinCount, playerTotalScore);
          }
          else {
             System.out.println("continue...");
          }
      } 
    }
    System.out.println("Thanks for playing!");
   }
  
   public static void showGameSummary(int numGamesPlayed, int playerWinCount, int playerTotalScore){
      System.out.println("Total games played: "+numGamesPlayed + ", player wins: "+playerWinCount+ " player points: "+playerTotalScore);
   }
}