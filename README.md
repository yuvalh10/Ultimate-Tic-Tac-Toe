# Ultimate-Tic-Tac-Toe

In this game, which is intended for two players, the game board is a 9x9 grid consisting of 9 regular 3x3 sub-boards of the Tic-Tac-Toe game.
The players take turns placing their characters in the free spaces on the board.

Limitation:
The position in the sub-board that a player chooses determines the sub-board in which the next player will have to play.

Example:
If the first player places a character in the upper left corner of one of the sub-boards, the next player must place a character in the same sub-board,
unless there are no empty spaces in that sub-board (in which case they can choose a different sub-board as they wish).

To win a certain sub-board, you must create a straight sequence (perpendicular, horizontal, or diagonal) of length 3. You can continue playing
in the sub-board even after one of the players has won it (in the remaining free spaces).
To win the game, you have to create a straight sequence of 3 victories in sub-boards.

Starting position:
At the beginning of the game, the board is empty, and the first player has the character X.

A single round move:
In each round, the current board will be printed, and the current player will be required to place a character on the board.
If the current player can choose which sub-board they want to play in (in the first round or if the sub-board defined by the previous step is full),
after the sub-board has been defined (by the previous step or by the player), the player will be required to choose a location in the selected sub-board.

Game over:
The game ends when there is a straight sequence of three wins by one of the players in the sub-boards, or when
the board has filled up (resulting in a tie).
