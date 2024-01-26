# Minesweeper Core Library

This library provides functionality for implementing the core logic of the Minesweeper game.

## Introduction

The Minesweeper Core Library allows developers to create Minesweeper game instances, manage game state, and implement game mechanics. It includes classes for initializing game boards, revealing cells, handling user interactions, and checking game outcomes.

## Usage

```cpp
#include "Mines.h"
```

### Static Version

To use the static version of the library, include the `Mines.h` header file in your project:


Then, you can use the Mines class directly in your code.

### Shared Version

If you prefer to use the shared version of the library, ensure that you have the `libMines.dll` file available in your project directory or in a location accessible to your application. Then, include the `Mines.h` header file in your project:


### Example (Qt Realization -- Coming Soon)

Suppose you're using Qt to create a Minesweeper game. Here's how you can incorporate the Minesweeper Core Library:

1. Include the `Mines.h` header file in your Qt project.

2. Use the Mines class to manage the Minesweeper game core logic.

3. You can use the provided methods like `initialize`, `step`, `reInit`, and `getRevNum` to implement game mechanics and interactions within your Qt application.

### Memory Management

Remember that the library handles memory management internally for `minesMap` and `revealMap`, so you don't need to worry about memory allocation or deallocation for these arrays.

## Building MineGame with CMake

Below is an example CMakeLists.txt file that demonstrates how to copy the DLL file from the Mines library directory to the output directory of your MineGame executable during the build process:

```cmake
cmake_minimum_required(VERSION 3.27)
project(MineGame)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the Mines library
set(MINES_DIR "Your/Path/to/Mines")
set(MINES_LIB_DIR "${MINES_DIR}/lib")

add_executable(MineGame main.cpp)

# Include the directory containing Mines.h
target_include_directories(MineGame PRIVATE "${MINES_DIR}")

# Link against the Mines library
target_link_libraries(MineGame PRIVATE "${MINES_LIB_DIR}/libMines.dll")

# Set the working directory for the MineGame executable
set_target_properties(MineGame PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/MineGame")

# Copy the DLL file from Mines to MineGame during build
add_custom_command(TARGET MineGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MINES_LIB_DIR}/libMines.dll"
        "$<TARGET_FILE_DIR:MineGame>"
        COMMENT "Copying libMines.dll to MineGame output directory"
)
```

Make sure to replace `"Your/Path/to/Mines"` with the actual path to your Mines library directory. This script will copy the `libMines.dll` file from the Mines library directory to the output directory of your MineGame executable every time you build the project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
