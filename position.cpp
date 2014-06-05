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

//If we should need to print a position. Probably for debugging.
std::string Position::toString()
{
	std::string res = "(";
	std::stringstream s;
	s << positionX;
	res += s.str() + ", ";
	s << positionY;
	res += s.str() + ")";
	return res;
}