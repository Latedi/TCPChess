#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <windows.h>

#include "piece.h"
#include "position.h"

#define SIZE 8

class Board
{
private:
	Piece * tiles[SIZE][SIZE];
	void initialize();
	void resetConsoleColor();
public:
	Board();
	void renderBoard();
	int getSize();
};

#endif /* BOARD_H */