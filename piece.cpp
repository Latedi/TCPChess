#include "piece.h"

Piece::Piece()
{

}

Piece::Piece(int positionX, int positionY, int team)
{
	position.positionX = positionX;
	position.positionY = positionY;
	this->team = team;
}

Piece::Piece(Position position, int team)
{
	this->position = position;
	this->team = team;
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