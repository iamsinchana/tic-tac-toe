#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int MOVE_BUTTON = 3;
int CONFIRM_BUTTON = 4;
char board[3][3];  
char currentPlayer = 'X';
int selectedRow = 0, selectedCol = 0;
int moveButtonLastState = HIGH;
int confirmButtonLastState = HIGH;
unsigned long lastDebounceTime = 0 , debounceDelay = 200;
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';  
        }
    }
}
void displayBoard() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(35, 0);
    display.println("Tic-Tac-Toe");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            display.setCursor(j * 30 + 20, i * 15 + 20);
            if (i == selectedRow && j == selectedCol) {
                display.print("[");
                display.print(board[i][j]);
                display.print("]");
            } else {
                display.print(" ");
                display.print(board[i][j]);
                display.print(" ");
            }

            if (j < 2) {
                display.setCursor(j * 30 + 45, i * 15 + 20);
                display.print("|");
            }
        }

        if (i < 2) {
            display.setCursor(20, i * 15 + 30);
            display.println("----|----|----");
        }
    }
    
    display.display();
}
bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')) {
            return true;
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
        return true;
    }
    return false;
}
bool checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') 
            return false;
        }
    }
    return true;
}

bool makeMove() {
    if (board[selectedRow][selectedCol] == ' ') {
        board[selectedRow][selectedCol] = currentPlayer;
        return true;
    }
    return false;
}
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}
void displayWinner(const char* message) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(25, 25);
    display.println(message);
    display.display();
    delay(2000);
}

void resetGame() {
    initializeBoard();
    currentPlayer = 'X';
    selectedRow = 0;
    selectedCol = 0;
    displayBoard();
}

void setup() {
    Serial.begin(9600);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    delay(2000);
    
    pinMode(MOVE_BUTTON, INPUT_PULLUP);
    pinMode(CONFIRM_BUTTON, INPUT_PULLUP);

    initializeBoard();
    displayBoard();
}

void loop() {
    unsigned long currentMillis = millis();
    int moveButtonState = digitalRead(MOVE_BUTTON);
    int confirmButtonState = digitalRead(CONFIRM_BUTTON);
    if (moveButtonLastState == HIGH && moveButtonState == LOW && (currentMillis - lastDebounceTime) > debounceDelay) {
        lastDebounceTime = currentMillis;

        // Move selection right, looping around
        selectedCol++;
        if (selectedCol > 2) {
            selectedCol = 0;
            selectedRow++;
            if (selectedRow > 2) {
                selectedRow = 0;
            }
        }

        displayBoard();
    }
    moveButtonLastState = moveButtonState;
    if (confirmButtonLastState == HIGH && confirmButtonState == LOW && (currentMillis - lastDebounceTime) > debounceDelay) {
        lastDebounceTime = currentMillis;

        if (makeMove()) {
            displayBoard();
                
            if (checkWin()) {
                displayWinner((String("Player ") + currentPlayer + " Wins!").c_str());
                resetGame();
                return;
            } 
            else if (checkDraw()) {
                displayWinner("It's a Draw!");
                resetGame();
                return;
            }

            switchPlayer();
        }
    }
    confirmButtonLastState = confirmButtonState;
}
