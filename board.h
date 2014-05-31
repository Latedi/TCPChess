#ifndef BOARD_H
#define BOARD_H

#include <iostream>

#include "piece.h"

#define SIZE 8

class Board
{
private:
	Piece tiles[SIZE][SIZE];
	void initialize();
public:
	Board();
	void renderBoard();
};

#endif /* BOARD_H */