/*
Author: [Kibi Paskaran]
Date: [Feb 6 2025]
Description: Uses game logic like mine placement and cell revealing for the game.
*/
#include "GameBoard.h"
#include <cstdlib>
#include <ctime>

// Constructor load board
GameBoard::GameBoard(int width, int height, int mineCount)
    : width(width), height(height), mineCount(mineCount) {

    // Resize vectors
    mines.resize(height, std::vector<bool>(width, false));
    revealed.resize(height, std::vector<bool>(width, false));

    // Place mines
    placeMines();
}

// Destructor
GameBoard::~GameBoard() {}

// Function place mines randomly
void GameBoard::placeMines() {
    // Clear old mines
    for (auto& row : mines) {
        std::fill(row.begin(), row.end(), false);
    }

    srand(time(nullptr));

    int placedMines = 0;
    while (placedMines < mineCount) {
        int row = rand() % height;
        int col = rand() % width;

        // Make sure no duplicates
        if (!mines[row][col]) {
            mines[row][col] = true;
            ++placedMines;
        }
    }
}
// Function to reset board
void GameBoard::resetBoard() {
    // Reset cells
    for (auto& row : revealed) {
        std::fill(row.begin(), row.end(), false);
    }

    //Place mines
    placeMines();
}

//if cell contains mines
bool GameBoard::isMine(int row, int col) const {
    return mines[row][col];
}

// number of adjacent mines
int GameBoard::adjacentMines(int row, int col) const {
    int count = 0;

    // Loop through 8 cells
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if ((i != 0 || j != 0) && newRow >= 0 && newRow < height && newCol >= 0 && newCol < width) {
                count += mines[newRow][newCol] ? 1 : 0;
            }
        }
    }

    return count;
}

// Check if player has won
bool GameBoard::checkWin() const {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (!mines[row][col] && !revealed[row][col]) {
                return false;
            }
        }
    }

    return true;
}

// Reveal a cell
void GameBoard::revealCell(int row, int col) {
    if (revealed[row][col]) return;

    revealed[row][col] = true;

    // Reveal surrounding cells recursively
    if (adjacentMines(row, col) == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = row + i;
                int newCol = col + j;

                if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width) {
                    if (!revealed[newRow][newCol]) {
                        revealCell(newRow, newCol);
                    }
                }
            }
        }
    }
}
