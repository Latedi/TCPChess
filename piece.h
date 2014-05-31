#ifndef PIECE_H
#define PIECE_H

#define WHITE 0
#define BLACK 1

#include <vector>

struct Position
{
	int positionX;
	int positionY;
};

class Piece
{
private:
	Position position;
	int team;
	int setPosition(Position position);
	char representation;
public:
	Piece();
	Piece(Position position, int team);
	Position getPosition();
	int moveTo(Position position);
	std::vector<Position> getMovableTiles();
	char getChar();
protected:
	void setRepresentation(char representation);
};

class Pawn : public Piece
{
public:
	Pawn(Position position, int team);
	std::vector<Position> getMovableTiles();
};

class Rook : public Piece
{
public:
	Rook(Position position, int team);
	std::vector<Position> getMovableTiles();
};

#endif /* PIECE_H */