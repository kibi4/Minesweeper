/*
Author: [Kibi Paskaran]
Date: [Feb 6 2025]
Description: Header for the mainwindow class. Manages game UI. User Interaction, updates display and does game logic.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//All Includes that is needed
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QPixmap>
#include <QEvent>
#include <QMessageBox>
//Header for GameBoard
#include "GameBoard.h"

//Main class inherits QMainWindow
class MainWindow : public QMainWindow {
    Q_OBJECT

//Constructor for the mainwindow
public:
    explicit MainWindow(QWidget *parent = nullptr);
    //Destructor for cleanup
    ~MainWindow();


private:

    //Main widget for game
    QWidget *centralWidget;
    //grid layout
    QGridLayout *gridLayout;
    //2d array for storing buttons
    QVector<QVector<QPushButton*>> buttons;
    //pointer to game
    GameBoard *gameBoard;

    //game icons
    QPixmap flagIcon;
    QPixmap mineIcon;
    QPixmap questionIcon;

    //check if game ended
    bool gameOver;

    // Load icons
    void loadIcons();

    // Initialize board
    void setupBoard();

    // Update button
    void updateButtonUI(int row, int col);

    // Reveal all mines when loss
    void revealAllMines();

    // Reset game board
    void resetGame();

private slots:
    //mouse left clicks
    void handleLeftClick();
    //right click on mouse
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
