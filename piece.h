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
	bool moved;
	void setRepresentation(char representation);
public:
	Piece();
	Piece(int team);
	virtual ~Piece();
	virtual std::vector<Position> getMovableTiles(Position position) const;
	void printMe(int bgColor) const;
	void printEmpty(int bgColor) const;
	bool doesTileExist(Position position) const;
	int getTeam() const;
	char getRepresentation() const;
	void printData() const;
	bool hasMoved() const;
	void setMoved(bool moved);
};

class King : public Piece
{
public:
	King(int team);
	virtual ~King();
	virtual std::vector<Position> getMovableTiles(Position position) const;
};

class Queen : public Piece
{
public:
	Queen(int team);
	virtual ~Queen();
	virtual std::vector<Position> getMovableTiles(Position position) const;
};

class Pawn : public Piece
{
public:
	Pawn(int team);
	virtual ~Pawn();
	virtual std::vector<Position> getMovableTiles(Position position) const;
};

class Rook : public Piece
{
public:
	Rook(int team);
	virtual ~Rook();
	virtual std::vector<Position> getMovableTiles(Position position) const;
};

class Knight : public Piece
{
public:
	Knight(int team);
	virtual ~Knight();
	virtual std::vector<Position> getMovableTiles(Position position) const;
};

class Bishop : public Piece
{
public:
	Bishop(int team);
	virtual ~Bishop();
	virtual std::vector<Position> getMovableTiles(Position position) const;
};

#endif /* PIECE_H */