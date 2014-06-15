#include "position.h"

Position::Position()
{
	positionX = 0;
	positionY = 0;
}

Position::Position(int x, int y)
{
	positionX = x;
	positionY = y;
}

const bool Position::operator==(const Position& other)
{
	if(positionX == other.positionX && positionY == other.positionY)
		return true;
	return false;
}

//If we should need to print a position. Probably for debugging.
const std::string Position::toString()
{
	std::string res = "(";
	std::stringstream s;
	s << positionX;
	res += s.str() + ", ";
	s.str(std::string());
	s << positionY;
	res += s.str() + ")";
	return res;
}