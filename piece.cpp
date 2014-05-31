#include "piece.h"

Piece::Piece()
{
	setRepresentation('-');
}

Piece::Piece(Position position, int team)
{
	this->position = position;
	this->team = team;
	setRepresentation('-');
}

Position Piece::getPosition()
{
	return position;
}

int Piece::setPosition(Position position)
{
	return 0;
}

int Piece::moveTo(Position position)
{
	return 0;
}

char Piece::getChar()
{
	return representation;
}

void Piece::setRepresentation(char representation)
{
	this->representation = representation;
}

/* PAWN */
Pawn::Pawn(Position position, int team)
: Piece(position, team)
{
	setRepresentation('P');
}

std::vector<Position> Pawn::getMovableTiles()
{
	
}

/* ROOK */
Rook::Rook(Position position, int team)
: Piece(position, team)
{
	setRepresentation('R');
}

std::vector<Position> Rook::getMovableTiles()
{
	
}