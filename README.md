OVERVIEW:

This is a terminal-based implementation of the popular 2048 puzzle game in C. The game features a 4x4 grid where players combine tiles with the same value to reach the 2048 tile and achieve the highest possible score.

FEATURES:

Grid Initialization: Starts with a predefined setup to randomly place the  initial tiles.

Tile Movement: Supports tile movement in all four directions (up, down, left, right).

Tile Merging: Tiles with the same value merge to form a new tile with double the value.

Score Tracking: Accumulates points based on tile merges.

Game Over Detection: Ends the game when no more valid moves are possible and no empty spaces in the grid are left.

INSTRUCTIONS:

1) To Move the page up press the PgUp key.

2) To Move the page up press the PgDn key.

3) To Move the page up press the Home key.

4) To Move the page up press the End key.

5) To exit the game press the 0 key.

GAME LOGIC:

1) Grid Representation: 

A 4x4 grid is used to represent the game board.

2) Random Tile Generation:

New tiles (2 or 4) are added to empty spaces in the grid after each move.

3)CMovement and Merging:

* Tiles are shifted towards the edge of the grid.
* Tiles of the same value merge into a single tile with double the value.
  
4) Win Condition:

The game announces a win if the 2048 tile is created.

5) Game Over Condition:

The game ends when no more moves are possible and no empty spaces are left.

Functions

default_grid():Initializes the grid with some starting tiles.

random_generator(): Generates random values for placing new tiles.

random_value(): Places a new tile (2 or 4) at a random empty position.

grid_display(): Displays the current state of the grid and score.

up(), down(), left(), right(): Handle tile movement and merging for respective directions.

get_input(): Reads user input and triggers corresponding movements.

check_zero(): Checks if there are any empty spaces in the grid.

check_move(): Verifies if there are possible moves left.

check_2048(): Checks if the 2048 tile has been achieved.
