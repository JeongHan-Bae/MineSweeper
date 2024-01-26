// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* This program demonstrates the integration of the Mines Library into a
 * Minesweeper game.*/

#include "Mines.h" /* Include the Mines library for controlling the core of the Minesweeper game*/
#include <QMainWindow>
#include <QMouseEvent>
#include <QtWidgets>

#define ROW 9
#define COL 12

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    // Constants for texts and corresponding text colors
    const QList<QString> Texts = {"", "1", "2", "3", "4", "5", "6", "7", "8"};
    const QList<QColor> textColor = {
                                     QColor(255, 255, 255), QColor(31, 63, 195),  QColor(63, 195, 31),
                                     QColor(195, 63, 31),   QColor(159, 63, 159), QColor(1, 1, 63),
                                     QColor(71, 63, 63),    QColor(127, 31, 31),  QColor(1, 95, 95)};

protected:
    // Overridden mousePressEvent function for handling mouse events
    void mousePressEvent(QMouseEvent* event) override;

public:
    // Constructor for MainWindow
    explicit MainWindow(Mines& minesweeper, bool& first, bool& dead,
                        char const** const minesMap,
                        bool const** const revealMap, bool** flagsMap,
                        QWidget* parent = nullptr);

    // Destructor for MainWindow
    ~MainWindow();

    // Function to paint the specified cell
    void paint(int i, int j, char type, bool show, bool flag);

    // Function to initialize the game board
    void initializeBoard();

    // Function to explode a cell
    void explode(int i, int j);

    // Function to paint the entire game board
    void paintBoard(bool dead);

    // Function to show the win message
    void showWin();

    // Function to show the lost message
    void showLost();

    // Function to handle the reset button click
    void onResetButtonClicked();

    // Function to restart the game
    void restart();

private:
    // Reference to the MineSweeper Game object
    Mines& minesweeper;

    // indicating the first step
    bool& firstStep;

    // indicating the game end
    bool& endGame;

    // Pointer to the mines map
    char const** const minesMap;

    // Pointer to the reveal map
    bool const** const revealMap;

    // Pointer to the flags map
    bool** flagsMap;

    // Font object for styling
    QFont font;

    // 2D array of pointers to QFrame objects representing the game board
    QFrame* frameArray[ROW][COL];

    // 2D array of pointers to QLabel objects representing the game board
    QLabel* labelArray[ROW][COL];

    // Pointer to the label displaying mine count
    QLabel* MineCountLabel;

    // Pointer to the reset button
    QToolButton* ResetButton;

    // Pointer to the UI object
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
