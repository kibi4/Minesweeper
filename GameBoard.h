/*
Author: [Kibi Paskaran]
Date: [Feb 6 2025]
Description: This is the header file for the Game Board Class. Defines the Gameboard class.
Use game logic, places mines, track cells.
*/
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

//vector library
#include <vector>

//handles game logic
class GameBoard {
public:
    //Constructor creates board with the given values
    GameBoard(int width, int height, int mineCount);
    //Destructor for clean up
    ~GameBoard();

    //check for mine
    bool isMine(int row, int col) const;
    //number of adjacent mines
    int adjacentMines(int row, int col) const;
    // if game has been won
    bool checkWin() const;
    //Reveals the given cell
    void revealCell(int row, int col);
    //Resets the game board
    void resetBoard();

private:
    //dimensions and mine count
    int width, height, mineCount;
    // 2D vector with mine locations
    std::vector<std::vector<bool>> mines;
    // 2D vector looking at revealed cells
    std::vector<std::vector<bool>> revealed;

    // Function to randomly place mines
    void placeMines();
};

#endif
