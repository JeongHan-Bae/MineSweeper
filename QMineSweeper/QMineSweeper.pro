QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    QMineSweeper_en_150.ts

# Path to the Mines library
MINES_DIR = ../Mines
MINES_LIB_DIR = $$MINES_DIR/lib

# Add the source files of Mines library directly to the project
MINES_SOURCES = \
    $$MINES_DIR/Mines.h \
    $$MINES_DIR/MinesImpl.h \
    $$MINES_DIR/MinesImpl.cpp

# Include the directory containing Mines.h
INCLUDEPATH += $$MINES_DIR

# Link against the Mines library
LIBS += -L$$MINES_LIB_DIR -lMines

RC_ICONS = Bomb.ico

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
