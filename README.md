# sudoku-cpp-console-version
As the name suggests, this is a console version of sudoku game coded in C++ which I made as my semester project in the course of pf. Just like the classic Sudoku, the objective here is to fill a 9 × 9 grid with digits so that each column, each row, and each of the nine 3X3 subgrids that compose the main board contain all of the digits from 1 to 9.

*REMEMBER!!* no digit can be repeated in anyrow, column or subgrid ;)

## Features

- Interactive console interface for playing Sudoku puzzles.
- Supports input validation to ensure puzzle rules are followed.
- Displays the puzzle board with easy-to-read formatting.
  
## Prerequisites

To compile and run the Sudoku C++ console version, you'll need the following:

- C++ compiler (e.g., GCC, Clang)
- CMake (minimum version 3.1)

*Or you can simply download and run the `main.exe` file (x64 bit) 😉*

## Getting Started

run the following commands on ```cmd``` to play the Sudoku C++ console version *using git*:
**NOTE:** the game is optimized for console proportions *width = 120* & *height = 30* :

1. Clone the repository:

```shell
git clone https://github.com/Fayyez/sudoku-cpp-console-version.git
```
2.Navigate to the project directory:

```shell
cd sudoku-cpp-console-version
```
3.Create a sudoku directory and navigate to it:

```shell
mkdir sudoku && cd sudoku
```

4.Generate the build files with CMake:

```shell
cmake ..
```
5.Build the project:
```shell
cmake --build .
```

6.Run the Sudoku game:
```shell
./main
```
## Contributions
Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.
## License
This project is licensed under the **BSD License**.
