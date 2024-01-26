cmake_minimum_required(VERSION 3.5)

project(MineSweeper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES MineSweeper_en_150.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
)

# Path to the Mines library
set(MINES_DIR "../Mines")
set(MINES_LIB_DIR "${MINES_DIR}/lib")

# Add the source files of Mines library directly to the project
set(MINES_SOURCES
    ${MINES_DIR}/Mines.h
    ${MINES_DIR}/MinesImpl.h
    ${MINES_DIR}/MinesImpl.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MineSweeper
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(MineSweeper SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(MineSweeper
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Include the directory containing Mines.h
target_include_directories(MineSweeper PRIVATE "${MINES_DIR}")

# Add the Mines sources to the project
target_sources(MineSweeper PRIVATE ${MINES_SOURCES})

# Link against the Mines library
target_link_libraries(MineSweeper PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(MineSweeper PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS MineSweeper
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MineSweeper)
endif()
