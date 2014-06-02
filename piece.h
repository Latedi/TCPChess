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
protected:
	int team;
	void setRepresentation(char representation);
public:
	Piece();
	Piece(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
	void printMe();
	bool doesTileExist(Position position);
};

class King : public Piece
{
private:
	bool moved;
public:
	King(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
	bool hasMoved();
	void setMoved(bool moved);
};

class Queen : public Piece
{
public:
	Queen(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
};

class Pawn : public Piece
{
private:
	bool moved;
public:
	Pawn(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
	bool hasMoved();
	void setMoved(bool moved);
};

class Rook : public Piece
{
private:
	bool moved;
public:
	Rook(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
	bool hasMoved();
	void setMoved(bool moved);
};

class Knight : public Piece
{
public:
	Knight(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
};

class Bishop : public Piece
{
public:
	Bishop(int team);
	virtual std::vector<Position> getMovableTiles(Position position, int size);
};

#endif /* PIECE_H */