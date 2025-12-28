# Tic-Tac-Toe C++ Game

A colorful, feature-rich implementation of the classic Tic-Tac-Toe game written in C++. Play in the terminal with beautiful colored Unicode graphics and the ability to save and load your games.

## Features

-  **Colored Terminal Output** - Beautiful ANSI color support with customizable foreground, background, and text attributes
-  **Save/Load Game** - Pause your game and resume it later
-  **Player vs Player** - Play locally against another player (X and O)
-  **Styled Graphics** - Unicode box drawing and special characters for an enhanced visual experience
-  **Simple Controls** - Number keys 1-9 for moves, 'q' to quit and save

## Requirements

- **C++17 or higher** (uses fold expressions)
- **Linux/Unix-based system** (uses termios for terminal input)
- **g++ compiler** (or compatible C++ compiler)

## Building the Project

### Using g++ directly:
```bash
cd Tic-Tac-Toe-CPP-Game
g++ -std=c++17 -o main main.cpp
```

## Running the Game

```bash
./main
```

When you start the game, you'll be prompted whether to load a previously saved game (if one exists).

## How to Play

### Game Rules
- The board is a 3×3 grid numbered 1-9 (like a phone keypad)
- Players alternate turns: X goes first, then O
- Each player places their mark on an empty cell
- The first player to get three marks in a row (horizontal, vertical, or diagonal) wins
- If all cells are filled with no winner, the game ends in a tie

### Controls
- **1-9**: Place your mark on the corresponding cell number
  ```
  7 8 9
  4 5 6
  1 2 3
  ```
- **q**: Quit and save the current game
- **Any other key**: Advance after game over

## Project Structure

### Core Files

- **main.cpp** - Main game loop, board management, and game logic
  - `printBoard()` - Renders the board with colored output
  - `game_state()` - Checks for win/tie conditions
  - `main()` - Game loop and save/load logic

- **Colored.h** - Terminal color/styling system
  - Enum classes: `Foreground`, `Background`, `Attribute`
  - `Colored` struct with methods for colored printing
  - Supports ANSI color codes and RGB colors

- **FileHandeling.h** - File I/O operations
  - `saveToFile()` - Persists game state to a file
  - `readFromFile()` - Loads a previously saved game

- **UtilsIO.h** - Utility input/output functions
  - `getch()` - Cross-platform character input (Linux/Unix equivalent of conio.h)

- **save.txt** - Stores the saved game state

## Game State Format

The game state is saved in the following format:
```
Saved/NSave (game status)
X/O (current player turn)
<9 lines with board cells>
```

Example:
```
Saved
X
 
X
 
...
```

## Architecture

### Data Structures

The game uses a 2D dynamic character array to represent the board:
```cpp
char **game_board = new char*[BOARD_SIZE];
```

Each cell contains:
- `'X'` - Player X's mark
- `'O'` - Player O's mark  
- `' '` - Empty cell

### Game States

The `GameState` enum represents three states:
- `OnGoing (0)` - Game is still in progress
- `Won (1)` - A player has won
- `Tied (2)` - Board is full with no winner

## Color Scheme

- **Board**: Bright Cyan (borders and structure)
- **X marks**: Bright Red
- **O marks**: Bright Green
- **Prompts**: Yellow

## Limitations & Future Improvements

### Current Limitations
- Linux/Unix only (uses termios for input)
- Player vs Player only (no AI)
- Single board size (3×3)

### Possible Enhancements
- Cross-platform support (Windows, macOS)
- Computer opponent with difficulty levels
- Configurable board sizes
- Game statistics and scoring
- Network multiplayer support

## License

Free to use and modify.


