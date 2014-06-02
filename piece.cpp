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

bool doesTileExist(Position position, int size)
{
	int x = position.getX();
	int y = position.getY();
	
	if(y < 0 || y >= size || x < 0 || x >= size)
		return false;
	return true;
}

/* KING */
King::King(int team)
: Piece(team)
{
	setRepresentation('K');
	moved = false;
}

std::vector<Position> King::getMovableTiles(Position position, int size)
{
	
}

bool King::hasMoved()
{
	return moved;
}

void King::setMoved(bool moved)
{
	this->moved = moved;
}

/* QUEEN */
Queen::Queen(int team)
: Piece(team)
{
	setRepresentation('Q');
}

std::vector<Position> Queen::getMovableTiles(Position position, int size)
{

}

/* PAWN */
Pawn::Pawn(int team)
: Piece(team)
{
	setRepresentation('P');
	moved = false;
}

std::vector<Position> Pawn::getMovableTiles(Position position, int size)
{
	int x = position.getX();
	int y = position.getY();;
	std::vector<Position> res;
	if(team == BLACK)
	{
		res.push_back(Position(x, y+1));
		if(moved == false)
			res.push_back(Position(x, y+2));
	}
	else if(team == WHITE)
	{
		res.push_back(Position(x, y-1));
		if(moved == false)
			res.push_back(Position(x, y-2));
	}
	
	return res;
}

bool Pawn::hasMoved()
{
	return moved;
}

void Pawn::setMoved(bool moved)
{
	this->moved = moved;
}

/* ROOK */
Rook::Rook(int team)
: Piece(team)
{
	setRepresentation('R');
	moved = false;
}

std::vector<Position> Rook::getMovableTiles(Position position, int size)
{
	
}

bool Rook::hasMoved()
{
	return moved;
}

void Rook::setMoved(bool moved)
{
	this->moved = moved;
}

/* KNIGHT */
Knight::Knight(int team)
: Piece(team)
{
	setRepresentation('N');
}

std::vector<Position> Knight::getMovableTiles(Position position, int size)
{

}

/* BISHOP */
Bishop::Bishop(int team)
: Piece(team)
{
	setRepresentation('B');
}

std::vector<Position> Bishop::getMovableTiles(Position position, int size)
{
	
}


