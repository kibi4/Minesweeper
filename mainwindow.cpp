/*
Author: [Kibi Paskaran]
Date: [Feb 6 2025]
Description: GUI for game. Manages game board and UI.
*/

// header file
#include "mainwindow.h"
#include "GameBoard.h"
// mouse use handling
#include <QMouseEvent>
// adding images to buttons
#include <QIcon>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

// Contructor for the Main Window
MainWindow::MainWindow(QWidget *parent)

    //Call the parents constructor
    : QMainWindow(parent), gameBoard(new GameBoard(30, 16, 99)){

    qDebug() << "Working Directory:" << QDir::currentPath();

    // central widget
    // sets to main widget
    setCentralWidget(centralWidget = new QWidget(this));

    // grid layout for the buttons
    gridLayout = new QGridLayout(centralWidget);

    // Resize the button
    buttons.resize(16, QVector<QPushButton*>(30, nullptr));

    //load icons
    loadIcons();



    // Create buttons
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            // Create button
            QPushButton *button = new QPushButton("", this);
            // Set size for the buttons one by one
            button->setFixedSize(35, 35);
            // Add button to the grid
            gridLayout->addWidget(button, row, col);
            // Save the button to array
            buttons[row][col] = button;

            // Connecting the left-click to the handleLeftClick function
            connect(button, &QPushButton::clicked, this, &MainWindow::handleLeftClick);
            //event filter for right-clicks
            button->installEventFilter(this);
        }
    }

    // Apply the grids layout to the main widget
    centralWidget->setLayout(gridLayout);
}

// Destructor for memory clean up
MainWindow::~MainWindow() {}

// This is a function to load icons
void MainWindow::loadIcons(){
    if (!mineIcon.load("icons/bomb.png"))
        qDebug() << "Failed to load bomb.png";
    if (!flagIcon.load("icons/flag.png"))
        qDebug() << "Failed to load flag.png";
    if (!questionIcon.load("icons/faq.png"))
        qDebug() << "Failed to load faq.png";

}

//function for left clicks
void MainWindow::handleLeftClick() {
    // Get the button
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    //if not button
    if (!button) return;

    // Get the row and column of the clicked button
    int row = gridLayout->indexOf(button) / 30;
    int col = gridLayout->indexOf(button) % 30;

    // Check mine
    if (gameBoard->isMine(row, col)) {
        revealAllMines();

        // "Try Again" button
        QMessageBox msgBox;
        msgBox.setText("You hit a mine! Game Over.");
        msgBox.setInformativeText("Try again?");
        msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
        msgBox.setDefaultButton(QMessageBox::Retry);

        //get user choice
        int choice = msgBox.exec();
        if (choice == QMessageBox::Retry) {
            resetGame();
        }
        return;
    } else {
        // Reveal the cell
        gameBoard->revealCell(row, col);
        updateButtonUI(row, col);

        // Check if the player won
        if (gameBoard->checkWin()) {
            QMessageBox::information(this, "You Win!", "You revealed all safe cells!");
            resetGame();
        }
    }
}

// Function to reset board
void MainWindow::resetGame() {
    // Reset the game board
    gameBoard->resetBoard();

    // Reset buttons
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            QPushButton *button = buttons[row][col];
            button->setEnabled(true);
            button->setText("");
            button->setIcon(QIcon());
            button->setProperty("state", 0);
        }
    }
}

// Function to update appearance
void MainWindow::updateButtonUI(int row, int col) {
    QPushButton *button = buttons[row][col];

    // number of adjacent mines
    int adjacentMinesCount = gameBoard->adjacentMines(row, col);
    // Display the number
    if (adjacentMinesCount > 0) {
        button->setText(QString::number(adjacentMinesCount));
    } else {
        button->setText("");
    }
// Disable the button
    button->setEnabled(false);
}

// Function to reveal all mines
void MainWindow::revealAllMines() {
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 30; ++col) {
            if (gameBoard->isMine(row, col)) {
                buttons[row][col]->setIcon(QIcon(mineIcon));
            }
        }
    }
}




// Event filter to handle right-clicks
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        // Check if the right mouse
        if (mouseEvent->button() == Qt::RightButton) {
            QPushButton *button = qobject_cast<QPushButton*>(obj);
            if (button) {
                // Prevent right-clicking
                if (button->property("revealed").toBool()) return true;


                int state = button->property("state").toInt();

                // Cycle through the states
                state = (state + 1) % 3;
                button->setProperty("state", state);


                if (state == 0) {
                    button->setIcon(QIcon());
                } else if (state == 1) {
                    button->setIcon(QIcon(flagIcon));
                } else if (state == 2) {
                    button->setIcon(QIcon(questionIcon));
                }

                return true;
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
