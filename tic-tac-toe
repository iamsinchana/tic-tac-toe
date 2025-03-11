#include <iostream>
#include <limits> 
#include <string> 
using namespace std;

unsigned input(const string& prompt) {
    unsigned value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 1 || value > 9) {
            cout << "Invalid input. Please enter a number between 1 and 9!" << endl;
            cin.clear(); // Clear flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else {
            return value; 
        }
    }
}
char board[3][3]; 
char currentPlayer = 'X';
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '1' + (3 * i + j);
        }
    }
}
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}
bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return true;
        }
    }
    // diagonals condition
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }
    return false;
}

//draw
bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') 
            return false;
        }
    }
    return true;
}

bool makeMove(unsigned cell) {
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentPlayer;
        return true;
    }
    return false;
}


void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    initializeBoard();
    cout << "Tic Tac Toe!\n";
    displayBoard();

    while (true) {
        unsigned cell = input("Player " + string(1, currentPlayer) + ", enter your move (1-9): ");

        if (!makeMove(cell)) {
            cout << "Invalid move! Cell already taken. Try again.\n";
            continue;
        }
        displayBoard();
        if (checkWin()) {
            cout << "Player " << currentPlayer << " wins! Congratulations!\n";
            break;
        }
        if (checkDraw()) {
            cout << "It's a draw! Well played both.\n";
            break;
        }
        switchPlayer();
    }

    return 0;
}
