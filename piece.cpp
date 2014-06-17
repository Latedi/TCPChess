#include "piece.h"

Piece::Piece()
{
	setRepresentation('-');
}

Piece::Piece(int team)
{
	this->team = team;
	setRepresentation('-');
	moved = false;
}

Piece::~Piece() {}

//Print the piece with correct colors
void Piece::printMe(int bgColor) const
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
void Piece::printEmpty(int bgColor) const
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

int Piece::getTeam() const
{
	return team;
}

char Piece::getRepresentation() const
{
	return representation;
}

bool Piece::hasMoved() const
{
	return moved;
}

void Piece::setMoved(bool moved)
{
	this->moved = moved;
}

//Set the character which will be printed to represent the piece
void Piece::setRepresentation(char representation)
{
	this->representation = representation;
}

// function implemented individually for every piece
std::vector<Position> Piece::getMovableTiles(Position position, const Board *board) const
{
	std::cout << "Something went wrong. Piece getMovableTiles called\n";
	std::vector<Position> p;
	return p;
}

//So we don't go out of bounds of the board
bool Piece::doesTileExist(Position position) const
{
	int x = position.getX();
	int y = position.getY();
	
	if(y < 0 || y >= B_SIZE || x < 0 || x >= B_SIZE)
		return false;
	return true;
}

//Debug
void Piece::printData() const
{
	std::cout << "Representation: " << representation << std::endl;
	std::cout << "Team: " << team << std::endl;
	std::cout << "Has moved: " << moved << std::endl;
}

//Remove all occurances of pieces from a team from a list of positions.
std::vector<Position> Piece::removeFriendly(std::vector<Position> positions, int team, const Board *board) const
{
	std::vector<Position>::iterator it = positions.begin();
	while(it != positions.end())
	{
		if(!board->isTileEmpty(*it))
		{
			if(board->getPiece(*it)->getTeam() == team)
			{
				positions.erase(it);
			}
			else {
				it++;
			}
		}
		else
			it++;
	}
	
	return positions;
}

//Remove positions from the positions array which are blocked by other pieces from the position initialPosition. Straight
std::vector<Position> Piece::removeBlockingStraight(std::vector<Position> positions, Position initialPosition, const Board *board) const
{
	int iX = initialPosition.getX();
	int iY = initialPosition.getY();

	Position up = Position(0, -1);
	Position down = Position(0, B_SIZE);
	Position left = Position(-1, 0);
	Position right = Position(B_SIZE, 0);
	
	//Find the closest positions horizontally and vertically which are occupied by any piece
	for(std::vector<Position>::iterator it = positions.begin(); it != positions.end(); it++)
	{
		if(!board->isTileEmpty(*it))
		{
			int nX = it->getX();
			int nY = it->getY();
			
			if(nX == iX)
			{
				if(nY > iY && nY < up.getY())
					up = Position(iX, nY);
				if(nY < iY && nY > down.getY())
					down = Position(iX, nY);
			}
			else if(nY == iY)
			{
				if(nX > iX && nX < right.getX())
					right = Position(nX, iY);
				if(nX < iX && nX > left.getX())
					left = Position(nX, iY);
			}
		}
	}
	
	//Then delete all tiles that are further away from the vector
	for(std::vector<Position>::iterator it = positions.begin(); it != positions.end(); it++)
	{
		int nX = it->getX();
		int nY = it->getY();
		
		if(nX == iX && (nY < up.getY() || nY > down.getY()))
		{
			positions.erase(it);
			it--;
		}
		else if(nY == iY && (nX > right.getX() || nX < left.getX()))
		{
			positions.erase(it);
			it--;
		}
	}
	
	return positions;
}

//Remove positions from the positions array which are block by other pieces from the position initialPosition. Diagonally
std::vector<Position> Piece::removeBlockingDiagonal(std::vector<Position> positions, Position initialPosition, const Board *board) const
{
	int iX = initialPosition.getX();
	int iY = initialPosition.getY();

	Position upLeft = Position(-1, -1);
	Position upRight = Position(B_SIZE, -1);
	Position downLeft = Position(-1, B_SIZE);
	Position downRight = Position(B_SIZE, B_SIZE);
	
	//Find the closest pieces diagonally
	for(std::vector<Position>::iterator it = positions.begin(); it != positions.end(); it++)
	{		
		if(!board->isTileEmpty(*it))
		{
			int nX = it->getX();
			int nY = it->getY();
			
			int distanceX = nX - iX;
			if(distanceX < 0)
				distanceX *= -1;
			int distanceY = nY - iY;
			if(distanceY < 0)
				distanceY *= -1;
				
			//Piece is diagonal to the initialPosition
			if(distanceX == distanceY)
			{
				if(nX > iX && nY > iY && nX < downRight.getX() && nY < downRight.getY())
					downRight = Position(nX, nY);
				else if(nX > iX && nY < iY && nX < upRight.getX() && nY > upRight.getY())
					upRight = Position(nX, nY);
				else if(nX < iX && nY > iY && nX > downLeft.getX() && nY < downLeft.getY())
					downLeft = Position(nX, nY);
				else if(nX < iX && nY < iY && nX > upLeft.getX() && nY > upLeft.getY())
					upLeft = Position(nX, nY);
			}
		}
	}
	
	//Delete all pieces further away
	for(std::vector<Position>::iterator it = positions.begin(); it != positions.end(); it++)
	{
		int nX = it->getX();
		int nY = it->getY();
		bool erase = false;
		
		if(nX > downRight.getX() && nY > downRight.getY())
		{
			erase = true;
		}
		else if(nX > upRight.getX() && nY < upRight.getY())
		{
			erase = true;
		}
		else if(nX < downLeft.getX() && nY > downLeft.getY())
		{
			erase = true;
		}
		else if(nX < upLeft.getX() && nY < upLeft.getY())
		{
			erase = true;
		}
		
		if(erase)
		{
			positions.erase(it);
			it--;
		}
	}
	
	return positions;
}

/* KING */
King::King(int team)
: Piece(team)
{
	setRepresentation('K');
}

King::~King() {}

std::vector<Position> King::getMovableTiles(Position position, const Board *board) const
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
				if(doesTileExist(movPos))
					res.push_back(movPos);
			}
		}
	}
	
	res = removeFriendly(res, team, board);
	
	return res;
}

/* QUEEN */
Queen::Queen(int team)
: Piece(team)
{
	setRepresentation('Q');
}

Queen::~Queen() {}

std::vector<Position> Queen::getMovableTiles(Position position, const Board *board) const
{
	std::vector<Position> res;
	int x = position.getX();
	int y = position.getY();
	
	for(int i = 0; i < B_SIZE; i++)
	{
		Position pos1 = Position(i, y);
		Position pos2 = Position(x, i);
		if(i != x && doesTileExist(pos1))
			res.push_back(pos1);
		if(i != y && doesTileExist(pos2))
			res.push_back(pos2);
	}
	
	for(int offset = 1; offset < B_SIZE - 1; offset++)
	{
		Position p1, p2, p3, p4;
		p1 = Position(x + offset, y + offset);
		p2 = Position(x + offset, y - offset);
		p3 = Position(x - offset, y + offset);
		p4 = Position(x - offset, y - offset);
		if(doesTileExist(p1))
			res.push_back(p1);
		if(doesTileExist(p2))
			res.push_back(p2);
		if(doesTileExist(p3))
			res.push_back(p3);
		if(doesTileExist(p4))
			res.push_back(p4);
	}
	
	res = removeBlockingStraight(res, position, board);
	res = removeBlockingDiagonal(res, position, board);
	res = removeFriendly(res, team, board);
	
	return res;
}

/* PAWN */
Pawn::Pawn(int team)
: Piece(team)
{
	setRepresentation('P');
}

Pawn::~Pawn() {}

std::vector<Position> Pawn::getMovableTiles(Position position, const Board *board) const
{
	int x = position.getX();
	int y = position.getY();;
	std::vector<Position> res;
	
	//Which direction is the pawn walking in?
	int direction;
	if(team == BLACK)
		direction = 1;
	else if(team == WHITE)
		direction = -1;
	
	//Check the tiles in front of the pawn. Add another tile forward on the first move
	Position p1 = Position(x, y + (1 * direction));
	if(board->doesTileExist(p1) && board->isTileEmpty(p1))
		res.push_back(p1);
	if(moved == false) {
		Position p2 = Position(x, y + (2 * direction));
		if(board->doesTileExist(p1) && board->isTileEmpty(p1))
			res.push_back(p2);
	}
	
	//Add tiles which a pawn can attack
	for(int i = -1; i <= 1; i += 2)
	{
		Position attack = Position(x + i, y + (1 * direction));
		if(!board->isTileEmpty(attack) && !board->isTileTeam(attack, team)) {
			res.push_back(attack);
		}
	}

	res = removeFriendly(res, team, board);
	
	return res;
}

/* ROOK */
Rook::Rook(int team)
: Piece(team)
{
	setRepresentation('R');
}

Rook::~Rook() {}

std::vector<Position> Rook::getMovableTiles(Position position, const Board *board) const
{
	std::vector<Position> res;
	int x = position.getX();
	int y  = position.getY();
	
	for(int i = 0; i < B_SIZE; i++)
	{
		Position pos1 = Position(i, y);
		Position pos2 = Position(x, i);
		if(i != x && doesTileExist(pos1))
			res.push_back(pos1);
		if(i != y && doesTileExist(pos2))
			res.push_back(pos2);
	}
	
	res = removeBlockingStraight(res, position, board);
	res = removeFriendly(res, team, board);
	
	return res;
}

/* KNIGHT */
Knight::Knight(int team)
: Piece(team)
{
	setRepresentation('N');
}

Knight::~Knight() {}

std::vector<Position> Knight::getMovableTiles(Position position, const Board *board) const
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
			
		if(doesTileExist(Position(x+i,y+j)))
			res.push_back(Position(x+i,y+j));
		if(doesTileExist(Position(x+i,y-j)))
			res.push_back(Position(x+i,y-j));
	}
	
	res = removeFriendly(res, team, board);
	
	return res;
}

/* BISHOP */
Bishop::Bishop(int team)
: Piece(team)
{
	setRepresentation('B');
}

Bishop::~Bishop() {}

std::vector<Position> Bishop::getMovableTiles(Position position, const Board *board) const
{
	std::vector<Position> res;
	int x = position.getX();
	int y = position.getY();
	
	for(int offset = 1; offset < B_SIZE - 1; offset++)
	{
		Position p1, p2, p3, p4;
		p1 = Position(x + offset, y + offset);
		p2 = Position(x + offset, y - offset);
		p3 = Position(x - offset, y + offset);
		p4 = Position(x - offset, y - offset);
		if(doesTileExist(p1))
			res.push_back(p1);
		if(doesTileExist(p2))
			res.push_back(p2);
		if(doesTileExist(p3))
			res.push_back(p3);
		if(doesTileExist(p4))
			res.push_back(p4);
	}
	
	res = removeBlockingDiagonal(res, position, board);
	res = removeFriendly(res, team, board);
	
	return res;
}