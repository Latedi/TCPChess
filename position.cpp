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

bool Position::operator==(const Position& other) const
{
	if(positionX == other.positionX && positionY == other.positionY)
		return true;
	return false;
}

bool Position::operator<(const Position& other) const
{
	if(positionX < other.positionX)
		return true;
	else if(positionX > other.positionX)
		return false;
	else
	{
		if(positionY < other.positionY)
			return true;
		else if(positionY > other.positionY)
			return false;
	}
	
	return false;
}

//If we should need to print a position. Probably for debugging.
std::string Position::toString() const
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