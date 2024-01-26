cmake_minimum_required(VERSION 3.24)
project(Mines)

# Add your source files
set(SOURCE_FILES MinesImpl.cpp Mines.h)

# Create a dynamic library from the source files
add_library(Mines SHARED ${SOURCE_FILES})


set(DLL_DIR ${CMAKE_SOURCE_DIR}/lib)

set(DLL_FILES libMines.dll)

set(DEST_DIR ${CMAKE_BINARY_DIR})

foreach (DLL_FILE ${DLL_FILES})
    add_custom_command(TARGET Mines POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL_DIR}/${DLL_FILE}"
            "${DEST_DIR}")
endforeach ()