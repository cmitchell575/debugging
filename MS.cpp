#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    const int BOARD_SIZE = 3; // 3x3 board
    const int NUM_BOMBS = 2;  // Number of bombs

    char board[BOARD_SIZE][BOARD_SIZE]; // To display the board
    bool isBomb[BOARD_SIZE][BOARD_SIZE]; // To track bomb locations
    bool isRevealed[BOARD_SIZE][BOARD_SIZE]; // To track revealed spaces
    bool isFlagged[BOARD_SIZE][BOARD_SIZE]; // To track flagged spaces
    int adjacentBombs[BOARD_SIZE][BOARD_SIZE]; // To track adjacent bomb counts

    // Initialize the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 'X'; // Hidden cell
            isBomb[i][j] = false; // No bomb initially
            isRevealed[i][j] = false; // Not revealed
            isFlagged[i][j] = false; // Not flagged
            adjacentBombs[i][j] = 0; // No adjacent bombs initially
        }
    }

    // Place bombs randomly
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < NUM_BOMBS; ) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (!isBomb[x][y]) {
            isBomb[x][y] = true;
            i++;
        }
    }

    // Calculate adjacent bombs
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (isBomb[i][j]) continue;
            int count = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue; // Skip the cell itself
                    int newX = i + dx;
                    int newY = j + dy;
                    if (newX >= 0 && newX < BOARD_SIZE && newY >= 0 && newY < BOARD_SIZE) {
                        if (isBomb[newX][newY]) count++;
                    }
                }
            }
            adjacentBombs[i][j] = count;
        }
    }

    // Game loop
    while (true) {
        // Display the board
        cout << "Current Board:\n";
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (isRevealed[i][j]) {
                    if (isBomb[i][j]) {
                        cout << "* "; // Display bomb
                    } else {
                        cout << adjacentBombs[i][j] << " "; // Display adjacent bomb count
                    }
                } else if (isFlagged[i][j]) {
                    cout << "F "; // Display flag
                } else {
                    cout << "X "; // Hidden cell
                }
            }
            cout << endl;
        }

        // Get user input
        cout << "Enter your move (row and column to reveal, or 'f' to flag): ";
        string command;
        cin >> command;

        if (command == "f") {
            int x, y;
            cin >> x >> y;
            if (!isRevealed[x][y]) {
                isFlagged[x][y] = !isFlagged[x][y]; // Toggle flag
            }
        } else {
            int x = stoi(command);
            int y;
            cin >> y;
            if (!isRevealed[x][y]) {
                isRevealed[x][y] = true; // Reveal the cell
                if (isBomb[x][y]) {
                    cout << "Game Over! You hit a bomb!" << endl;
                    break; // End the game
                }
            }
        }

        // Check win condition
        bool won = true;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (!isBomb[i][j] && !isRevealed[i][j]) {
                    won = false; // There are still non-bomb spaces to reveal
                }
            }
        }
        if (won) {
            cout << "Congratulations! You've revealed all non-bomb spaces!" << endl;
            break; // End the game
        }
    }

    return 0;
}
