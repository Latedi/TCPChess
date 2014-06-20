#ifndef PIECE_H
#define PIECE_H

#define WHITE 0
#define BLACK 1
#define B_SIZE 8

#define HIGHLIGHT 2

#include <vector>
#include <iostream>
#include <windows.h>

#include "board.h"
#include "position.h"

class Board;

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
	virtual std::vector<Position> getMovableTiles(Position position, const Board *board) const;
	std::vector<Position> removeFriendly(std::vector<Position> positions, int team, const Board *board) const;
	std::vector<Position> removeBlockingStraight(std::vector<Position> positions, Position initialPosition, const Board *board) const;
	std::vector<Position> removeBlockingDiagonal(std::vector<Position> positions, Position initialPosition, const Board *board) const;
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
	virtual std::vector<Position> getMovableTiles(Position position, const Board *board) const;
};

class Queen : public Piece
{
public:
	Queen(int team);
	virtual ~Queen();
	virtual std::vector<Position> getMovableTiles(Position position, const Board *board) const;
};

class Pawn : public Piece
{
public:
	Pawn(int team);
	virtual ~Pawn();
	virtual std::vector<Position> getMovableTiles(Position position, const Board *board) const;
	std::vector<Position> getAttackableTiles(Position position, const Board *board) const;
};

class Rook : public Piece
{
public:
	Rook(int team);
	virtual ~Rook();
	virtual std::vector<Position> getMovableTiles(Position position, const Board *board) const;
};

class Knight : public Piece
{
public:
	Knight(int team);
	virtual ~Knight();
	virtual std::vector<Position> getMovableTiles(Position position, const Board *board) const;
};

class Bishop : public Piece
{
public:
	Bishop(int team);
	virtual ~Bishop();
	virtual std::vector<Position> getMovableTiles(Position position, const Board *board) const;
};

#endif /* PIECE_H */