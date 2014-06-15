#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <sstream>

class Position
{
private:
	int positionX;
	int positionY;
public:
	Position();
	Position(int x, int y);
	const int getX() { return positionX; };
	const int getY() { return positionY; };
	const bool operator==(const Position& other);
	const std::string toString();
};

#endif /* POSITION_H */