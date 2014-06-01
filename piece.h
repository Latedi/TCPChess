#ifndef PIECE_H
#define PIECE_H

#define WHITE 0
#define BLACK 1

#include <vector>
#include <iostream>

#include "position.h"

class Piece
{
private:
	char representation;
public:
	Piece();
	Piece(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
	void printMe();
protected:
	int team;
	void setRepresentation(char representation);
};

class Pawn : public Piece
{
public:
	Pawn(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
};

class Rook : public Piece
{
public:
	Rook(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
};

#endif /* PIECE_H */