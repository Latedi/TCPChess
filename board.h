#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <windows.h>

#include "piece.h"
#include "position.h"

#define B_B_SIZE 8

class Board
{
private:
	Piece * tiles[B_SIZE][B_SIZE];
	void initialize();
	void resetConsoleColor();
	bool isTileEmpty(Position position);
	bool doesTileExist(Position position);
	std::vector<Position> removeFriendly(std::vector<Position> positions, int team);
	std::vector<Position> removeBlockingStraight(std::vector<Position> positions, Position initialPosition);
	std::vector<Position> removeBlockingDiagonal(std::vector<Position> positions, Position initialPosition);
public:
	Board();
	~Board();
	void renderBoard();
	int getB_SIZE();
	void printMovable(Position position);
	void printPositionVector(std::vector<Position> positions);
};

#endif /* BOARD_H */