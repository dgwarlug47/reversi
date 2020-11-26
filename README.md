# reversi
https://youtu.be/KOlD3EH4pUU
The game consists of an nxn grid  of cells, each of which can be either empty, black, or white. When the game  begins the middle 4 cells are populated following the  pattern Blak-White-Black-White. Reversi is a two player game where the players take turns placing a piece of their colour in a cell. Black plays first. The goal of Reversi is to have the most clees holding pieces of your colour at the end of the game. If a new piece A would form a line segment with an existsing piece B of the same color, such that all of the cells in betweena are occupied and of the opposite colour, those in-between pieces are flipped to the same colours as A and B.
</br> there is a difference of this version with compared with the standard reversi, whereas a legal move in standard Reversi must cause at least one flip, your program is not required to enforce this rule.
</br>
# Commands
new n: this command as it was shown in the video demonstration starts a new game with a board of size nxn.
</br>
play r c: if the block at row r, and column c is empty (has no color), then that cell gets the color of the current player, otherwise (the cell has already been occupied) then the program ignores the command and waits for the player to play in another cell.
