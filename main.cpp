//
//  main.cpp
//  BattleShip
//
//  Created by Tyler LeFevre on 1/21/24.
//

#include <iostream>
#include <thread> // For the timer.
#include <array>
using namespace std;


// Function prototype
void passToOtherPlayer();
void printShips(const array<array<char, 10>, 10>& board);
void addShips(array<array<char, 10>, 10>& board, string player);
void attackOppnentShip(array<array<char, 10>, 10>& board, string player);
bool areShipsRemaining(const array<array<char, 10>, 10>& board);
void gameLoop();

int main(int argc, const char * argv[]) {


   
   gameLoop();
   
   return 0;
}


// Pass To other player
void passToOtherPlayer()
{

   
   // A bunch of empty lines so players dont see previous players board
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   cout << endl;
   
   
   // Countdown and pass
   cout << "pass" << endl;
    
   for (int i = 5; i > 0; --i)
   {
      cout << i << " ";
      // Sleep for 1 second (optional, for better visualization)
      this_thread::sleep_for(chrono::seconds(1));
   }
   cout << endl;
}

// Function to print the game board
void printShips(const array<array<char, 10>, 10>& board)
{
    // Print column numbers at the top
    cout << "  ";
    for (int i = 0; i < 10; ++i)
    {
        cout << i << ' ';
    }
    cout << endl;

    char rowLabel = 'A';

    for (const auto& row : board)
    {
        // Print row label on the left
        cout << rowLabel++ << ' ';

        for (const char& cell : row)
        {
           if (cell == 'S'){
              cout << cell << ' ';
           }
           else
           {
              cout << "  ";
           }
           
        }

        cout << endl;
    }
}

void printHits(const array<array<char, 10>, 10>& board)
{
    // Print column numbers at the top
    cout << "  ";
    for (int i = 0; i < 10; ++i)
    {
        cout << i << ' ';
    }
    cout << endl;

    char rowLabel = 'A';

    for (const auto& row : board)
    {
        // Print row label on the left
        cout << rowLabel++ << ' ';

        for (const char& cell : row)
        {
            if (cell == 'H' or cell == 'M')
            {
               cout << cell << ' ';
            }
            else
            {
               cout << "  ";
            }
        }

        cout << endl;
    }
}

// Function to add ships to the board
void addShips(array<array<char, 10>, 10>& board, string player)
{
   // Define ship sizes and their corresponding symbols
   array<int, 5> shipSizes = {5, 4, 3, 3, 2};
   array<char, 5> shipSymbols = {'S', 'S', 'S', 'S', 'S'};

   for (int i = 0; i < shipSizes.size(); ++i)
   {
      int shipSize = shipSizes[i];
      char shipSymbol = shipSymbols[i];
       
      // Print the board
      printShips(board);

      // Prompt user for ship placement
      cout << "Player " << player << ", enter the starting position (e.g., A1): ";
      string startPosition;
      cin >> startPosition;

      // Convert the input to board coordinates
      int row = toupper(startPosition[0]) - 'A';
      int col = startPosition[1] - '0';
        

      // Prompt user for ship orientation
      cout << "Enter ship orientation (H for horizontal, V for vertical): ";
      char orientation;
      cin >> orientation;

      // Check for boundaries and overlapping
      bool validPlacement = true;
      if (orientation == 'H')
      {
         if (col + shipSize > 10)
         {
               validPlacement = false;
         }
         else
         {
               for (int c = col; c < col + shipSize; ++c)
               {
                  if (board[row][c] != ' ')
                  {
                     validPlacement = false;
                     break;
                  }
               }
         }
      }
      else if (orientation == 'V')
      {
         if (row + shipSize > 10)
         {
               validPlacement = false;
         }
         else
         {
               for (int r = row; r < row + shipSize; ++r)
               {
                  if (board[r][col] != ' ')
                  {
                     validPlacement = false;
                     break;
                  }
               }
         }
      }
      else
      {
         validPlacement = false;
      }

      // Update the board if placement is valid
      if (validPlacement)
      {
         if (orientation == 'H')
         {
               for (int c = col; c < col + shipSize; ++c)
               {
                  board[row][c] = shipSymbol;
               }
         }
         else if (orientation == 'V')
         {
               for (int r = row; r < row + shipSize; ++r)
               {
                  board[r][col] = shipSymbol;
               }
         }
      }
      else
      {
         cout << "Invalid placement. Try again." << endl;
         --i; // Decrement i to try placing the same size ship again
      }


   }
}

void attackOpponentShip(array<array<char, 10>, 10>& board, string player)
{
    // Print the opponent's board with hits and misses
    printHits(board);

    // Prompt the player for the attack position
    cout << "Player " << player << ", enter the attack position (e.g., A1): ";
    string attackPosition;
    cin >> attackPosition;

    // Convert the input to board coordinates
    int row = toupper(attackPosition[0]) - 'A';
    int col = attackPosition[1] - '0';

    // Check if the attack position is within the board boundaries
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
    {
       cout << "Invalid attack position. Try again." << endl;
       
       // Prompt the player for the attack position
       cout << "Player " << player << ", enter the attack position (e.g., A1): ";
       cin >> attackPosition;

       // Convert the input to board coordinates
       row = toupper(attackPosition[0]) - 'A';
       col = attackPosition[1] - '1';
   
    }

    // Check the cell on the opponent's board
    char& targetCell = board[row][col];

    // Check if the cell has already been attacked
    if (targetCell == 'H' || targetCell == 'M')
    {
       cout << "You've already attacked this position. Try again." << endl;
       attackOpponentShip(board, player); // Recursive call to try again
       return;
    }

    // Process the attack
    if (targetCell == 'S')
    {
        cout << "Hit!" << endl;
        targetCell = 'H'; // Mark as hit
    }
    else
    {
        cout << "Miss!" << endl;
        targetCell = 'M'; // Mark as miss
    }
}

bool areShipsRemaining(const array<array<char, 10>, 10>& board)
{
    for (const auto& row : board)
    {
        for (const char& cell : row)
        {
            if (cell == 'S')
            {
                // At least one ship is remaining
                return true;
            }
        }
    }

    // No ships remaining
    return false;
}
void gameLoop()
{
   // Initialize player 1 and 2s boards
   array<std::array<char, 10>, 10> playerOneBoard;
   array<std::array<char, 10>, 10> playerTwoBoard;
   
   for (auto& row : playerOneBoard) {
      for (char& cell : row) {
         cell = ' ';
      }
   }
   
   for (auto& row : playerTwoBoard) {
      for (char& cell : row) {
         cell = ' ';
      }
   }
   
   
   // Add ships for player 1
   addShips(playerOneBoard, "1");
   
   // Pass
   passToOtherPlayer();
   
   // Add ships for player 2
   addShips(playerTwoBoard, "2");
   
   passToOtherPlayer();
   // Player identifiers
   string player1 = "1";
   string player2 = "2";
   
   while (areShipsRemaining(playerOneBoard) && areShipsRemaining(playerTwoBoard))
   {
      // Player 1's turn
      cout << "Player 1's turn:" << endl;
      attackOpponentShip(playerTwoBoard, player1);
      
      // Check if Player 2 has lost
      if (!areShipsRemaining(playerTwoBoard))
      {
         cout << "Player 1 wins!" << endl;
         break;
      }
      
      // Pass to Player 2
      passToOtherPlayer();
      
      // Player 2's turn
      cout << "Player 2's turn:" << endl;
      attackOpponentShip(playerOneBoard, player2);
      
      // Check if Player 1 has lost
      if (!areShipsRemaining(playerOneBoard))
      {
         cout << "Player 2 wins!" << endl;
         break;
      }
      
      // Pass to Player 1
      passToOtherPlayer();
   }
}

