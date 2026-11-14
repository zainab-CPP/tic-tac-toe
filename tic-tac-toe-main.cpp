#include <iostream>
#include <limits>

using namespace std;

// Returns true if the selected player has won.
bool checkWinner(const char board[3][3], char player)
{
    // Check rows and columns.
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return true;
        }

        if (board[0][i] == player &&
            board[1][i] == player &&
            board[2][i] == player)
        {
            return true;
        }
    }

    // Check diagonals.
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return true;
    }

    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return true;
    }

    return false;
}

// Displays the current game board.
void displayBoard(const char board[3][3])
{
    cout << "\n";

    for (int row = 0; row < 3; row++)
    {
        cout << " " << board[row][0]
             << " | " << board[row][1]
             << " | " << board[row][2] << "\n";

        if (row < 2)
        {
            cout << "---+---+---\n";
        }
    }

    cout << "\n";
}

int main()
{
    char board[3][3] =
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char currentPlayer = 'X';
    int position;
    int validTurns = 0;
    bool gameOver = false;

    cout << "===== TIC TAC TOE =====\n";
    cout << "Player X and Player O take turns.\n";
    cout << "Choose a position from 1 to 9.\n";

    displayBoard(board);

    while (validTurns < 9 && !gameOver)
    {
        cout << "Player " << currentPlayer
             << ", enter a position (1-9): ";

        if (!(cin >> position))
        {
            if (cin.eof())
            {
                cout << "\nInput ended. Game stopped.\n";
                return 0;
            }

            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Check whether the position is within the board.
        if (position < 1 || position > 9)
        {
            cout << "Invalid position. Choose a number from 1 to 9.\n";
            continue;
        }

        // Convert the position (1-9) into row and column indexes (0-2).
        int index = position - 1;
        int row = index / 3;
        int col = index % 3;

        // Do not allow a player to choose an occupied cell.
        if (board[row][col] == 'X' || board[row][col] == 'O')
        {
            cout << "That cell is already occupied. Try again.\n";
            continue;
        }

        board[row][col] = currentPlayer;
        validTurns++;

        // Show the updated board, including the final winning move.
        displayBoard(board);

        if (checkWinner(board, currentPlayer))
        {
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
        }
        else if (validTurns == 9)
        {
            cout << "It's a draw!\n";
            gameOver = true;
        }
        else
        {
            // Switch to the other player.
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    cout << "Thanks for playing!\n";
    return 0;
}
