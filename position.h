#ifndef POSITION_H
#define POSITION_H

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
};

#endif /* POSITION_H */