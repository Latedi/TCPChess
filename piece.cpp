#include "piece.h"

Piece::Piece()
{
	setRepresentation('-');
}

Piece::Piece(int team)
{
	this->team = team;
	setRepresentation('-');
}

void Piece::printMe()
{
	std::cout << representation;
}

void Piece::setRepresentation(char representation)
{
	this->representation = representation;
}

std::vector<Position> Piece::getMovableTiles(Position position, int size)
{
}

/* PAWN */
Pawn::Pawn(int team)
: Piece(team)
{
	setRepresentation('P');
}

std::vector<Position> Pawn::getMovableTiles(Position position, int size)
{
	int x = position.getX();
	int y = position.getY();;
	std::vector<Position> res;
	if(team == BLACK)
	{
		std::cout << "X=" << x << " Y=" << y << std::endl;
		if(y + 1 < size)
			res.push_back(Position(x, y+1));
		if(y + 2 < size && y == 1)
			res.push_back(Position(x, y+2));
	}
	else if(team == WHITE)
	{
		if(y - 1 >= 0)
			res.push_back(Position(x, y-1));
		if(y - 2 >= 0 && y == size - 1)
			res.push_back(Position(x, y-2));
	}
	
	return res;
}

/* ROOK */
Rook::Rook(int team)
: Piece(team)
{
	setRepresentation('R');
}

std::vector<Position> Rook::getMovableTiles(Position position, int size)
{
	
}