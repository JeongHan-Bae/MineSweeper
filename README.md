# Minesweeper Game

Welcome to the Minesweeper game realization! This readme will guide you through the different branches of the repository and how to build and run the game using different build systems.

## Repository Structure

The Minesweeper repository is structured as follows:

```
MineSweeper
   |
    - library branch (core library)
   |      |
   |      ---- Mines (Source files)
   |
   - CMake-Qt branch (CMake Qt realization)
   |      |
   |      ---- Mines (core Source files)
   |      ---- MineSweeper (Qt Source files)
   |      ---- MineSweeper.exe
   |
   - QMake-Qt (QMake Qt realization)
          |
          ---- Mines (core Source files)
          ---- QMineSweeper (Qt Source files)
          ---- Release
                   |
                   ---- QMineSweeper.exe
                   ---- libMines.dll
```

## Minesweeper Core Library

The `Mines` directory in each branch contains the core logic of the Minesweeper game implemented as a library. All branches utilize this library for game functionality.

## [Library Branch](https://github.com/JeongHan-Bae/MineSweeper/tree/library)

The `Library` branch contains only the `Mines` library without any game executables.

## [CMake-Qt Branch](https://github.com/JeongHan-Bae/MineSweeper/tree/CMake-Qt)

In the `CMake-Qt` branch, the Minesweeper game is built using CMake. The game is compiled statically, and the executable `MineSweeper.exe` is located directly within the `CMake-Qt` folder.

## [QMake-Qt Branch](https://github.com/JeongHan-Bae/MineSweeper/tree/QMake-Qt)

The `QMake-Qt` branch employs QMake as the build system for the Minesweeper game. The game is linked dynamically with the Mines library using the `libMines.dll` file. The executable `QMineSweeper.exe` is located within the `Release` folder along with the necessary DLL.

## Running the Game

### CMake-Qt Branch

To run the Minesweeper game from the [CMake-Qt branch](https://github.com/JeongHan-Bae/MineSweeper/tree/CMake-Qt):

1. Navigate and download the contents of the `CMake-Qt` branch.
2. Execute the `MineSweeper.exe` file.

### QMake-Qt Branch

To run the Minesweeper game in the [QMake-Qt branch](https://github.com/JeongHan-Bae/MineSweeper/tree/QMake-Qt):

1. Navigate and download the contents of the `QMake-Qt` branch.
2. Ensure that both `QMineSweeper.exe` and `libMines.dll` are present in the `Release` folder.
3. Execute the `Release/QMineSweeper.exe` file.

Please note: In order to launch the game, make sure that all Qt tool directories are in the PC's path variable, or place the executable (if it's the QMake version, along with the `libMines.dll`) into a folder containing all necessary Qt and C++ DLLs.

## Additional Notes

- Both versions of the game utilize the same core logic implemented in the `Mines` library.
- Feel free to explore the source code and modify the game as needed.

### Implementation Suggestions

The game's core logic is encapsulated within the `Mines.h` file, utilizing C primitive types. This design facilitates seamless integration with various languages and platforms. We recommend users compile and run the game according to their preferences, leveraging the flexibility of the codebase.

Additionally, consider exploring alternative implementations using different languages and platforms:

- **Python with Cython**: Create Python bindings for the Minesweeper game using Cython, enabling integration with Python-based applications.
- **C# with Unity**: Adapt the game for Unity development using C#, allowing for Minesweeper games within the Unity game engine environment.
- **PyQt**: Implement the game using PyQt, providing a cross-platform solution for building Minesweeper games with Python and Qt.

These suggestions showcase the versatility of the Minesweeper codebase, empowering users to tailor the game to their specific requirements and preferences.


## Gaming GUI Example 
<div style="text-align:center">
  <img src="https://github.com/JeongHan-Bae/MineSweeper/assets/128088756/85890608-772c-4554-a93a-9bce3b6d3e90" alt="Minesweeper Game GUI Example">
</div>



## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Security

Please review our [Security Policy](SECURITY.md) for information on reporting security vulnerabilities.
