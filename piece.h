#ifndef PIECE_H
#define PIECE_H

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
public:
	Piece();
	Piece(int positionX, int positionY, int team);
	Piece(Position position, int team);
	Position getPosition();
	int moveTo(Position position);
	std::vector<Position> getMovableTiles();
};

#endif /* PIECE_H */