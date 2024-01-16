# Tetris
#  Description
  This program is an amateur reproduction of the Tetris game made in Qt C++.

  The game is presented as a game board 11 x 20 (the size of the board can be adjusted in the program code), which is filled with figures consisting of 1 - 4 blocks in a 3 x 3 matrix.
  Each cell of the game board is projected on a cell of the array with the dimension equal to the size of the game board.
  Empty cells correspond to the symbol "0" in the array.
  The current game piece corresponds to the symbol "1" in the array.
  The game piece that was fixed on the playing field corresponds to the symbol "*" in the array.

  Game pieces are represented as an array of 9 symbols, where the symbol "0" corresponds to an empty cell, and the symbol "1" corresponds to the cell occupied by the block of the piece.

  Array of figurines is projected in the zone of size 3 х 3 in the top central part of the game board.

  So the symbol L will correspond to the symbol array "010010011" and will be written in the game array in the form:

#  0 1 0
#  0 1 0
#  0 1 1
  
#  Requirements

  -Qt >= 6.0.0
  
  -CMake >= 3.5
  
  -C++14
  
