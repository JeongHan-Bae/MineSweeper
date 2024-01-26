// mainwindow.cpp

#include "./ui_mainwindow.h"
#include "mainwindow.h"

/* This program demonstrates the integration of the Mines Library into a
 * Minesweeper game.*/

// Global variables for mine count
int MINENUM = 16;
int MineCount = MINENUM;

// Constructor
MainWindow::MainWindow(Mines& minesweeper, bool& firstStep, bool& endGame,
                       char const** const minesMap,
                       bool const** const revealMap, bool** flagsMap,
                       QWidget* parent)
    : QMainWindow(parent), minesweeper(minesweeper), firstStep(firstStep),
      endGame(endGame), minesMap(minesMap), revealMap(revealMap),
      flagsMap(flagsMap), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowTitle("Minesweeper Game CMake Verso");

    // Set font for UI elements
    font = QFont("Segoe UI", 20);
    font.setWeight(QFont::Bold);

    // Find MineCountLabel and set font
    MineCountLabel = findChild<QLabel*>("MineCountLabel");
    MineCountLabel->setFont(font);

    // Set font for buttons
    QFont buttonFont = QFont("Segoe UI", 16);
    buttonFont.setWeight(QFont::Bold);

    // Find ResetButton and set font
    QToolButton* ResetButton = findChild<QToolButton*>("ResetButton");
    ResetButton->setFont(buttonFont);
    connect(ResetButton, &QToolButton::clicked, this,
            &MainWindow::onResetButtonClicked);

    // Initialize game board frames and labels
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            QString frameName = QString("frame_%1_%2").arg(i).arg(j);
            QString labelName = QString("label_%1_%2").arg(i).arg(j);

            // Find frame and label objects
            QFrame* frame = findChild<QFrame*>(frameName);
            QLabel* label = findChild<QLabel*>(labelName);

            // Add frame and label to arrays and set initial properties
            if (frame) {
                frameArray[i][j] = frame;
                frame->setFrameStyle(QFrame::Box);
                frame->setLineWidth(1);
                frame->setMidLineWidth(0);
                frame->setStyleSheet(
                    "background-color: rgb(191, 191, 191); border: 2px "
                    "solid rgb(127, 127, 127);");
            }

            if (label) {
                labelArray[i][j] = label;
                label->setFont(font);
                label->setText("");
            }
        }
    }
}

// Destructor
MainWindow::~MainWindow() { delete ui; }

// Initialize the game board
void MainWindow::initializeBoard() {
    // Initialize flagsMap with false
    for (int i = 0; i < ROW; ++i) {
        std::memset(flagsMap[i], false,
                    COL * sizeof(bool)); // Initialize boolArray with false
    }

    // Set MineCountLabel text
    MineCountLabel->setText(QString("Total Mines Count: %1").arg(MINENUM));

    // Reset frame styles and label texts
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            frameArray[i][j]->setFrameStyle(QFrame::Box);
            frameArray[i][j]->setStyleSheet(
                "background-color: rgb(191, 191, 191); border: 2px "
                "solid rgb(127, 127, 127);");
            labelArray[i][j]->setText("");
        }
    }
}

// Function to paint a cell
void MainWindow::paint(int i, int j, char type, bool show, bool flag) {
    if (flag) {
        // Set style and text for flagged cell
        frameArray[i][j]->setStyleSheet(
            "background-color: rgb(191, 191, 191); border: 2px solid "
            "rgb(127, 127, 127);");
        labelArray[i][j]->setText("🚩");
    } else if (!show) {
        // Clear style and text for hidden cell
        frameArray[i][j]->setStyleSheet(
            "background-color: rgb(191, 191, 191); border: 2px solid "
            "rgb(127, 127, 127);");
        labelArray[i][j]->setText("");
    } else {
        // Set style and text based on cell type
        if (type == -1) {
            frameArray[i][j]->setStyleSheet(
                "background-color: lightgrey; border: 2px "
                "solid rgb(127, 127, 127);");
            labelArray[i][j]->setText("💣");
        } else {
            frameArray[i][j]->setStyleSheet(
                "background-color: rgb(223, 223, 223); "
                "border: 2px solid rgb(127, 127, 127);");
            labelArray[i][j]->setText(Texts[type]);
            labelArray[i][j]->setStyleSheet(
                QString("color: %1;").arg(textColor[type].name()));
        }
    }
}

// Function to handle explosion animation
void MainWindow::explode(int i, int j) {
    labelArray[i][j]->setText("💥");
    frameArray[i][j]->setStyleSheet(
        "background-color: rgb(221, 221, 1); border: 2px "
        "solid rgb(127, 127, 127);");
}

// Overridden mousePressEvent function for handling mouse events
void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (endGame)
        return;
    int x = event->position().x();
    int y = event->position().y();

    // Calculate grid position based on mouse coordinates
    int Y = (x - 80) / 40;
    int X = (y - 150) / 40;

    if (X < 0 || Y < 0) {
        return;
    } else if (X >= ROW || Y >= COL) {
        return;
    }

    // Handle left click
    if (event->button() == Qt::LeftButton) {
        if (firstStep) {
            // Perform initialization if first click
            minesweeper.initialize(X, Y, MINENUM); // Example mineNum = 20
            minesweeper.step(X, Y);
            firstStep = false;
        } else {
            // Perform step based on click
            if (!flagsMap[X][Y]) {
                StepResults result = minesweeper.step(X, Y);
                if (result == StepResults::LOST) {
                    endGame = true;
                }
            }
        }
    }

    // Handle right click
    if (event->button() == Qt::RightButton) {
        if (revealMap[X][Y])
            return;
        // Toggle flag
        flagsMap[X][Y] ^= true;
        paint(X, Y, 0, 0, flagsMap[X][Y]);
        return;
    }

    // Update GUI
    paintBoard(false);

    // Check game end conditions
    if (endGame) {
        explode(X, Y);
        showLost();
    } else if (minesweeper.getRevNum() + MINENUM == ROW * COL) {
        // Show win message
        paintBoard(true);
        endGame = true;
        showWin();
    }
}

// Function to paint the entire game board
void MainWindow::paintBoard(bool win) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (endGame) {
                paint(i, j, minesMap[i][j], true,
                      minesMap[i][j] == -1 ? flagsMap[i][j] : false);
            } else if (win) {
                paint(i, j, minesMap[i][j], true,
                      minesMap[i][j] == -1 ? true : false);
            } else {
                paint(i, j, minesMap[i][j], revealMap[i][j], flagsMap[i][j]);
            }
        }
    }
}

// Function to show the "You Lost" message
void MainWindow::showLost() {
    QMessageBox* lostMessageBox = new QMessageBox(
        QMessageBox::Information, "Game Over",
        "You Lost. \nPress OK to Restart...", QMessageBox::Ok, this);
    connect(lostMessageBox, &QMessageBox::finished, this, &MainWindow::restart);
    QTimer::singleShot(200, this, [=]() { lostMessageBox->exec(); });
}

// Function to show the "You Win" message
void MainWindow::showWin() {
    QMessageBox* winMessageBox = new QMessageBox(
        QMessageBox::Information, "Congratulations",
        "You Win. \nPress OK to Restart...", QMessageBox::Ok, this);
    connect(winMessageBox, &QMessageBox::finished, this, &MainWindow::restart);
    QTimer::singleShot(200, this, [=]() { winMessageBox->exec(); });
}

// Function to restart the game
void MainWindow::restart() {
    firstStep = true;
    MINENUM = MineCount;
    minesweeper.reInit();
    initializeBoard();
    endGame = false;
}

// Slot function to handle the Reset button click
void MainWindow::onResetButtonClicked() {
    // Create a QDialog to get user input
    QDialog dialog(this);
    dialog.setWindowTitle("Reset Mines");

    QVBoxLayout layout(&dialog);

    QLabel label("Enter the number of mines:");
    layout.addWidget(&label);

    QLineEdit lineEdit;
    layout.addWidget(&lineEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        // User clicked OK, get the entered number of mines
        QString userInput = lineEdit.text();
        bool ok;
        int numMines = userInput.toInt(&ok);
        if (!ok || numMines < 0 || numMines >= ROW * COL) {
            QMessageBox::critical(this, "Error", "Not a valid number!");
            return;
        }

        // Set the number of mines
        MineCount = numMines;

        // Show appropriate message based on whether it's the first game or not
        if (firstStep) {
            MINENUM = MineCount;
            MineCountLabel->setText(
                QString("Total Mines Count: %1").arg(MineCount));
            QMessageBox::information(
                this, "Success", "Successful! You have reset for this game.");
        } else {
            QMessageBox::information(this, "Success",
                                     QString("Successful! You have reset for "
                                             "the next game with a number %1.")
                                         .arg(MineCount));
        }
    }
}
