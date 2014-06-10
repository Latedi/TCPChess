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

//Print the piece with correct colors
void Piece::printMe(int bgColor)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	int foregroundColor;
	if(team == WHITE)
		foregroundColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
	else
		foregroundColor = FOREGROUND_BLUE |FOREGROUND_INTENSITY;
		
	int backgroundColor;
	switch(bgColor)
	{
	case WHITE:
		backgroundColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case BLACK:
		backgroundColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	}
	
	SetConsoleTextAttribute(hConsole, foregroundColor | backgroundColor);
	std::cout << representation;
}

//Print an empty tile
void Piece::printEmpty(int bgColor)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	switch(bgColor)
	{
	case WHITE:
		bgColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case BLACK:
		bgColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	}
	
	SetConsoleTextAttribute(hConsole, bgColor);
	std::cout << ' ';
}

int Piece::getTeam()
{
	return team;
}

char Piece::getRepresentation()
{
	return representation;
}

//Set the character which will be printed to represent the piece
void Piece::setRepresentation(char representation)
{
	this->representation = representation;
}

//Virtual function implemented individually for every piece
std::vector<Position> Piece::getMovableTiles(Position position, int size)
{
}

//So we don't go out of bounds of the board
const bool Piece::doesTileExist(Position position, int size)
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
	std::vector<Position> res;
	int x = position.getX();
	int y = position.getY();
	
	for(int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for(int yOffset = -1; yOffset <= 1; yOffset++)
		{
			if(xOffset != 0 || yOffset != 0)
			{
				Position movPos = Position(x + xOffset, y + yOffset);
				if(doesTileExist(movPos, size))
					res.push_back(movPos);
			}
		}
	}
	return res;
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
	std::vector<Position> res;
	int x = position.getX();
	int y = position.getY();
	
	for(int i = 0; i < size; i++)
	{
		Position pos1 = Position(i, y);
		Position pos2 = Position(x, i);
		if(i != x && doesTileExist(pos1, size))
			res.push_back(pos1);
		if(i != y && doesTileExist(pos2, size))
			res.push_back(pos2);
	}
	
	for(int offset = 1; offset < size - 1; offset++)
	{
		Position p1, p2, p3, p4;
		p1 = Position(x + offset, y + offset);
		p2 = Position(x + offset, y - offset);
		p3 = Position(x - offset, y + offset);
		p4 = Position(x - offset, y - offset);
		if(doesTileExist(p1, size))
			res.push_back(p1);
		if(doesTileExist(p2, size))
			res.push_back(p2);
		if(doesTileExist(p3, size))
			res.push_back(p3);
		if(doesTileExist(p4, size))
			res.push_back(p4);
	}
	
	return res;
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
	std::vector<Position> res;
	int x = position.getX();
	int y  = position.getY();
	
	for(int i = 0; i < size; i++)
	{
		Position pos1 = Position(i, y);
		Position pos2 = Position(x, i);
		if(i != x && doesTileExist(pos1, size))
			res.push_back(pos1);
		if(i != y && doesTileExist(pos2, size))
			res.push_back(pos2);
	}
	
	return res;
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
	std::vector<Position> res;
	int x = position.getX();
	int y = position.getY();
	
	for(int i = -2; i <= 2; i++)
	{
		if(i == 0)
			continue;
			
		int j;
		if(i % 2 == 0)
			j = 1;
		else
			j = 2;
			
		if(doesTileExist(Position(x+i,y+j), size))
			res.push_back(Position(x+i,y+j));
		if(doesTileExist(Position(x+i,y-j), size))
			res.push_back(Position(x+i,y-j));
	}
	
	return res;
}

/* BISHOP */
Bishop::Bishop(int team)
: Piece(team)
{
	setRepresentation('B');
}

std::vector<Position> Bishop::getMovableTiles(Position position, int size)
{
	std::vector<Position> res;
	int x = position.getX();
	int y = position.getY();
	
	for(int offset = 1; offset < size - 1; offset++)
	{
		Position p1, p2, p3, p4;
		p1 = Position(x + offset, y + offset);
		p2 = Position(x + offset, y - offset);
		p3 = Position(x - offset, y + offset);
		p4 = Position(x - offset, y - offset);
		if(doesTileExist(p1, size))
			res.push_back(p1);
		if(doesTileExist(p2, size))
			res.push_back(p2);
		if(doesTileExist(p3, size))
			res.push_back(p3);
		if(doesTileExist(p4, size))
			res.push_back(p4);
	}
	
	return res;
}