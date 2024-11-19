#include <iostream>
#include <vector>

using namespace std;

vector<int> board(10, 2); // Initialize board with 2 (empty spaces)
int magic_square[10] = {0, 8, 3, 4, 1, 5, 9, 6, 7, 2};
int turn = 1;
int player_symbol;
int comp_symbol;

int Make2()
{
  if (board[5] == 2)
    return 5;
  return (board[2] == 2) ? 2 : ((board[4] == 2) ? 4 : ((board[6] == 2) ? 6 : 8));
}

void Go(int n)
{
  board[n] = (turn % 2 != 0) ? player_symbol : comp_symbol;
  turn++;
}

int Posswin(int p)
{
  for (int i = 1; i <= 9; i++)
  {
    if (board[i] == p)
    {
      for (int j = i + 1; j <= 9; j++)
      {
        if (board[j] == p)
        {
          int third_pos = 15 - (magic_square[i] + magic_square[j]);
          for (int k = 1; k <= 9; k++)
          {
            if (magic_square[k] == third_pos && board[k] == 2)
            {
              return k;
            }
          }
        }
      }
    }
  }
  return 0;
}

void printBoard()
{
  for (int i = 1; i <= 9; i++)
  {
    if (board[i] == 2)
      cout << "- ";
    else if (board[i] == 3)
      cout << "X ";
    else
      cout << "O ";
    if (i % 3 == 0)
      cout << endl;
  }
}

void compmoves()
{
  if (turn == 1)
  {
    Go(1);
  }
  else if (turn == 2)
  {
    if (board[5] == 2)
      Go(5);
    else
      Go(1);
  }
  else if (turn == 3)
  {
    if (board[9] == 2)
      Go(9);
    else
      Go(3);
  }
  else
  {
    int winMove = Posswin(comp_symbol);
    if (winMove != 0)
      Go(winMove);
    else
    {
      int blockMove = Posswin(player_symbol);
      if (blockMove != 0)
        Go(blockMove);
      else
        Go(Make2());
    }
  }
}

bool checking_for_winner(int symbol)
{
  vector<vector<int>> lines = {
      {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};

  for (auto line : lines)
  {
    if (board[line[0]] == symbol && board[line[1]] == symbol && board[line[2]] == symbol)
    {
      return true;
    }
  }

  return false;
}

bool filled_board()
{
  for (int i = 1; i <= 9; i++)
  {
    if (board[i] == 2)
      return false;
  }
  return true;
}

void PlayGame()
{
  char choice;
  do
  {
    cout << "Do you want to be X or O? Enter X or O: ";
    cin >> choice;
  } while (choice != 'X' && choice != 'x' && choice != 'O' && choice != 'o');

  player_symbol = (choice == 'O' || choice == 'o') ? 5 : 3;
  comp_symbol = (player_symbol == 3) ? 5 : 3;

  while (true)
  {
    printBoard();
    if (turn % 2 != 0)
    {
      int move;
      cout << "Your turn (enter a number 1-9): ";
      cin >> move;
      if (move < 1 || move > 9 || board[move] != 2)
      {
        cout << "Invalid move, please try again." << endl;
        continue;
      }
      Go(move);
    }
    else
    {
      cout << "Comp's turn..." << endl;
      compmoves();
    }

    if (checking_for_winner(player_symbol))
    {
      printBoard();
      cout << "Congratulations! You won!" << endl;
      break;
    }
    else if (checking_for_winner(comp_symbol))
    {
      printBoard();
      cout << "Computer won! Better luck next time!" << endl;
      break;
    }

    if (filled_board())
    {
      printBoard();
      cout << "It's a draw!" << endl;
      break;
    }
  }
}

int main()
{
  PlayGame();
  return 0;
}
