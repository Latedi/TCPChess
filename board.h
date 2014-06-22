#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

#include "piece.h"
#include "position.h"

#ifndef B_SIZE
#define B_SIZE 8
#endif

class Piece;

class Board
{
private:
	Piece * tiles[B_SIZE][B_SIZE];
	void initialize();
	void resetConsoleColor() const;
	std::vector<Position> removeFriendly(std::vector<Position> positions, int team) const;
	std::vector<Position> removeBlockingStraight(std::vector<Position> positions, Position initialPosition) const;
	std::vector<Position> removeBlockingDiagonal(std::vector<Position> positions, Position initialPosition) const;
	void addPiece(Piece* piece, Position newPos, Position oldPos);
	void removePiece(Position position);
	std::vector<Position> getThreatenedPositions(int team) const;
	bool pawnToQueen(Position position);
	int getEnemyTeam(int team) const;
public:
	Board();
	~Board();
	void renderBoard() const;
	void renderHighlightedPosiotions(std::vector<Position> positions) const;
	int getB_SIZE() const;
	void printPositionVector(std::vector<Position> positions) const;
	std::vector<Position> getMovable(Position position) const;
	bool isTileTeam(Position pos, int team) const;
	bool movePiece(Position from, Position to, int team);
	bool isCheck(int team, bool printDebug=false) const;
	bool isChekmate(int team);
	bool isTileEmpty(Position position) const;
	bool doesTileExist(Position position) const;
	Piece* getPiece(Position position) const;
	bool castle(int team, bool kingside);
};

#endif /* BOARD_H */