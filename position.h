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
	int getX() const { return positionX; };
	int getY() const { return positionY; };
	bool operator==(const Position& other) const;
	bool operator<(const Position& other) const;
	std::string toString() const;
};

#endif /* POSITION_H */