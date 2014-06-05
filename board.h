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
	~Board();
	void renderBoard();
	int getSize();
	void printMovable(Position position);
	bool isTileEmpty(Position position);
	bool doesTileExist(Position position);
	std::vector<Position> removeFriendly(std::vector<Position> positions, int team);
};

#endif /* BOARD_H */