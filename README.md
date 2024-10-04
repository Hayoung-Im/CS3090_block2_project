# CS3090_block2_project
The University of Utah CS3090 block 2 project
# Grid-Based Block Game

## Overview
This is a grid-based block game developed in C++. The goal is to control falling blocks, and clear lines, and prevent the blocks from stacking up to the top of the screen. The game features real-time control of block speed and introduces challenges like rising ground level. Score and combo mechanics reward players for clearing consecutive lines without missing. The game ends when no more blocks can be placed.

## How to Play
**Arrow Keys:**
- **Left (←):** Increase block drop speed.
- **Right (→):** Decrease block drop speed.
- **Up (↑):** Decrease the speed of the rising ground.
- **Down (↓):** Increase the speed of the rising ground.
- **Spacebar:** Start the game.
- **'P' Key:** Pause the game.

## Game Objectives
- Prevent blocks from stacking up by clearing lines.
- A line clears when all columns in a row are filled with blocks.
- Clear multiple lines consecutively to increase your combo multiplier, which rewards higher scores.
- As time passes, the ground rises, adding more difficulty. Manage the rising ground and block placement to survive longer.

## Key Features
- **Combo System:** Clearing lines in consecutive moves boosts the score multiplier.
- **Rising Ground:** Adds pressure by reducing available space as the game progresses.
- **Adjustable Speed:** Control both block drop speed and ground rising speed with arrow keys.

## Scoring
- **Line Clear:** 100 points per cleared line.
- **Combo Bonus:** Clearing multiple lines consecutively adds an additional 100 points per combo.

## Code Structure

### Key Structs:
- **Score:** Tracks the player's score, combo, and combo activation status.
- **Block:** Handles block movement, placement, and collision detection on the grid.

### Functions:
- `void ShowBoard()`: Displays the game board with the initial game title screen.
- `void InIt()`: Initializes the game, resetting the game board, score, and block state.
- `void ShowMenu()`: Displays the control instructions and game status (e.g., current speed and scores).
- `void ShowMap()`: Displays the current state of the game grid, including blocks and cleared lines.
- `void ClearLine()`: Detects and clears completed lines on the grid, updating the score and combo.
- `bool RaiseGround()`: Simulates the rising ground effect by shifting blocks upward.
- `int DropSpeed()`: Allows the player to control the speed of the block drop and ground rising mechanics with the keyboard.
- `void GameOver()`: Displays the "Game Over" message and resets the game.

### Main Loop:
1. The game starts by displaying the title and control instructions.
2. The player can adjust the speed of block dropping and ground rising.
3. Blocks fall, and players can move and drop them to clear lines.
4. The game continues until blocks can no longer be placed, after which the "Game Over" screen appears.

## Dependencies
- **Windows OS** (uses Windows-specific libraries for console control).
- **C++ Standard Library** for input/output and time functions.
