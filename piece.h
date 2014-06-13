#ifndef PIECE_H
#define PIECE_H

#define WHITE 0
#define BLACK 1
#define B_SIZE 8

#include <vector>
#include <iostream>
#include <windows.h>

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
	virtual ~Piece();
	const virtual std::vector<Position> getMovableTiles(Position position);
	void printMe(int bgColor);
	void printEmpty(int bgColor);
	const bool doesTileExist(Position position);
	const int getTeam();
	const char getRepresentation();
};

class King : public Piece
{
private:
	bool moved;
public:
	King(int team);
	virtual ~King();
	const virtual std::vector<Position> getMovableTiles(Position position);
	const bool hasMoved();
	void setMoved(bool moved);
};

class Queen : public Piece
{
public:
	Queen(int team);
	virtual ~Queen();
	const virtual std::vector<Position> getMovableTiles(Position position);
};

class Pawn : public Piece
{
private:
	bool moved;
public:
	Pawn(int team);
	virtual ~Pawn();
	const virtual std::vector<Position> getMovableTiles(Position position);
	const bool hasMoved();
	void setMoved(bool moved);
};

class Rook : public Piece
{
private:
	bool moved;
public:
	Rook(int team);
	virtual ~Rook();
	const virtual std::vector<Position> getMovableTiles(Position position);
	const bool hasMoved();
	void setMoved(bool moved);
};

class Knight : public Piece
{
public:
	Knight(int team);
	virtual ~Knight();
	const virtual std::vector<Position> getMovableTiles(Position position);
};

class Bishop : public Piece
{
public:
	Bishop(int team);
	virtual ~Bishop();
	const virtual std::vector<Position> getMovableTiles(Position position);
};

#endif /* PIECE_H */