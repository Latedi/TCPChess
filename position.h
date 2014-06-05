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
	int getX() { return positionX; };
	int getY() { return positionY; };
	std::string toString();
};

#endif /* POSITION_H */