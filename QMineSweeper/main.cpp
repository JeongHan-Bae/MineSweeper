#include "Mines.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    bool first = true;
    bool dead = false;

    const char** minesMap;
    const bool** revealMap;

    bool** flagsMap = new bool*[ROW];
    for (int i = 0; i < ROW; ++i) {

        flagsMap[i] = new bool[COL];

        std::memset(flagsMap[i], false,
                    COL * sizeof(bool)); // Initialize boolArray with false
    }

    Mines minesweeper(ROW, COL, minesMap, revealMap);
    MainWindow mainWindow(minesweeper, first, dead, minesMap, revealMap,
                          flagsMap);

    // Show the MainWindow
    mainWindow.show();

    // Initialize the board if needed
    mainWindow.initializeBoard();

    return a.exec();
}
