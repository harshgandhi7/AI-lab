#include <iostream>
using namespace std;

void displayBoard(int gameBoard[])
{
  cout << endl;
  for (int i = 0; i < 9; ++i)
  {
    if (gameBoard[i] == 2)
      cout << ".";
    else if (gameBoard[i] == 1)
      cout << "X";
    else
      cout << "O";
    if ((i + 1) % 3 == 0)
      cout << endl;
    else
      cout << " ";
  }
  cout << endl;
}

void placeMark(int gameBoard[], int position)
{
  if (position >= 0 && position < 9 && gameBoard[position] == 2)
    gameBoard[position] = 0;
}

int possibleWin(int gameBoard[], char currentPlayer)
{
  int mark = (currentPlayer == 'X') ? 1 : 0;
  int winningPatterns[8][3] = {
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

  for (int i = 0; i < 8; ++i)
  {
    int x = winningPatterns[i][0];
    int y = winningPatterns[i][1];
    int z = winningPatterns[i][2];

    if (gameBoard[x] == mark && gameBoard[y] == mark && gameBoard[z] == 2)
      return z;
    if (gameBoard[x] == mark && gameBoard[y] == 2 && gameBoard[z] == mark)
      return y;
    if (gameBoard[x] == 2 && gameBoard[y] == mark && gameBoard[z] == mark)
      return x;
  }
  return -1;
}

void makeCenterOrCorners(int gameBoard[])
{
  if (gameBoard[4] == 2)
    placeMark(gameBoard, 4);
  else if (gameBoard[0] == 2)
    placeMark(gameBoard, 0);
  else if (gameBoard[2] == 2)
    placeMark(gameBoard, 2);
  else if (gameBoard[6] == 2)
    placeMark(gameBoard, 6);
  else if (gameBoard[8] == 2)
    placeMark(gameBoard, 8);
}

void makeAnyMove(int gameBoard[])
{
  for (int i = 0; i < 9; ++i)
  {
    if (gameBoard[i] == 2)
    {
      placeMark(gameBoard, i);
      break;
    }
  }
}

void computerMove(int gameBoard[], int turnNumber)
{
  if (turnNumber == 1)
    placeMark(gameBoard, 0);
  else if (turnNumber == 2)
  {
    if (gameBoard[4] == 2)
      placeMark(gameBoard, 4);
    else
      placeMark(gameBoard, 0);
  }
  else if (turnNumber == 3)
  {
    if (gameBoard[8] == 2)
      placeMark(gameBoard, 8);
    else
      placeMark(gameBoard, 2);
  }
  else if (turnNumber == 4)
  {
    if (possibleWin(gameBoard, 'X') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'X'));
    else
      makeCenterOrCorners(gameBoard);
  }
  else if (turnNumber == 5)
  {
    if (possibleWin(gameBoard, 'X') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'X'));
    else if (possibleWin(gameBoard, 'O') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'O'));
    else if (gameBoard[6] == 2)
      placeMark(gameBoard, 6);
    else
      placeMark(gameBoard, 2);
  }
  else if (turnNumber == 6)
  {
    if (possibleWin(gameBoard, 'O') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'O'));
    else if (possibleWin(gameBoard, 'X') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'X'));
    else
      makeCenterOrCorners(gameBoard);
  }
  else if (turnNumber == 7 || turnNumber == 9)
  {
    if (possibleWin(gameBoard, 'X') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'X'));
    else if (possibleWin(gameBoard, 'O') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'O'));
    else
      makeAnyMove(gameBoard);
  }
  else if (turnNumber == 8)
  {
    if (possibleWin(gameBoard, 'O') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'O'));
    else if (possibleWin(gameBoard, 'X') != -1)
      placeMark(gameBoard, possibleWin(gameBoard, 'X'));
    else
      makeAnyMove(gameBoard);
  }
}

bool checkForWinner(int gameBoard[], char currentPlayer)
{
  int mark = (currentPlayer == 'X') ? 1 : 0;
  int winningPatterns[8][3] = {
      {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

  for (int i = 0; i < 8; ++i)
  {
    int x = winningPatterns[i][0];
    int y = winningPatterns[i][1];
    int z = winningPatterns[i][2];

    if (gameBoard[x] == mark && gameBoard[y] == mark && gameBoard[z] == mark)
      return true;
  }
  return false;
}

void playComputerTurn(int gameBoard[], int turnNumber)
{
  computerMove(gameBoard, turnNumber);
  cout << "Computer's Move:" << endl;
  displayBoard(gameBoard);
}

void playUserTurn(int gameBoard[], int turnNumber)
{
  cout << "Enter your move (1-9): ";
  int userPosition;
  cin >> userPosition;
  --userPosition;

  while (userPosition < 0 || userPosition > 8 || gameBoard[userPosition] != 2)
  {
    cout << "Invalid move. Enter another position: ";
    cin >> userPosition;
    --userPosition;
  }

  gameBoard[userPosition] = 1;
  displayBoard(gameBoard);
}

int main()
{
  int playAgain = -1;
  do
  {
    int gameBoard[9];
    fill(begin(gameBoard), end(gameBoard), 2);
    int turnNumber = 1;

    while (turnNumber <= 9)
    {
      playComputerTurn(gameBoard, turnNumber);
      if (checkForWinner(gameBoard, 'O'))
      {
        cout << "Computer wins!" << endl;
        break;
      }

      if (++turnNumber > 9)
        break;

      playUserTurn(gameBoard, turnNumber);
      if (checkForWinner(gameBoard, 'X'))
      {
        cout << "You win!" << endl;
        break;
      }

      ++turnNumber;
    }

    if (turnNumber == 10)
      cout << "It's a draw!" << endl;

    cout << "Play again? Enter a non-zero integer to continue or 0 to quit: ";
    cin >> playAgain;
  } while (playAgain != 0);
}