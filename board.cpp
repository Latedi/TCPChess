#include "board.h"

Board::Board()
{
	initialize();
}

//Delete all existing pieces
Board::~Board()
{
	for(int i = 0; i < B_SIZE; i++)
	{
		for(int j = 0; j < B_SIZE; j++)
		{
			if(!isTileEmpty(Position(i, j)))
				delete tiles[i][j];
		}
	}
}

//Place all the pieces on the board
void Board::initialize()
{	
	for(int i = 0; i < B_SIZE; i++)
	{
		for(int j = 0; j < B_SIZE; j++)
		{
			tiles[i][j] = NULL;
		}
	}
	
	//Place pawns
	for(int i = 0; i < B_SIZE; i++)
	{
		Pawn *blackPawn = new Pawn(BLACK);
		Pawn *whitePawn = new Pawn(WHITE);
		tiles[1][i] = blackPawn;
		tiles[B_SIZE-2][i] = whitePawn;
	}
	
	//Place rooks
	Rook *blackRook1 = new Rook(BLACK);
	Rook *blackRook2 = new Rook(BLACK);
	Rook *whiteRook1 = new Rook(WHITE);
	Rook *whiteRook2 = new Rook(WHITE);
	tiles[0][0] = blackRook1;
	tiles[0][B_SIZE-1] = blackRook2;
	tiles[B_SIZE-1][0] = whiteRook1;
	tiles[B_SIZE-1][B_SIZE-1] = whiteRook2;
	
	//Place knights
	Knight *blackKnight1 = new Knight(BLACK);
	Knight *blackKnight2 = new Knight(BLACK);
	Knight *whiteKnight1 = new Knight(WHITE);
	Knight *whiteKnight2 = new Knight(WHITE);
	tiles[0][1] = blackKnight1;
	tiles[0][B_SIZE-2] = blackKnight2;
	tiles[B_SIZE-1][1] = whiteKnight1;
	tiles[B_SIZE-1][B_SIZE-2] = whiteKnight2;
	
	//Place bishops
	Bishop *blackBishop1 = new Bishop(BLACK);
	Bishop *blackBishop2 = new Bishop(BLACK);
	Bishop *whiteBishop1 = new Bishop(WHITE);
	Bishop *whiteBishop2 = new Bishop(WHITE);
	tiles[0][2] = blackBishop1;
	tiles[0][B_SIZE-3] = blackBishop2;
	tiles[B_SIZE-1][2] = whiteBishop1;
	tiles[B_SIZE-1][B_SIZE-3] = whiteBishop2;
	
	//Place kings
	King *blackKing = new King(BLACK);
	King *whiteKing = new King(WHITE);
	tiles[0][4] = blackKing;
	tiles[B_SIZE-1][4] = whiteKing;
	
	//Place queens
	Queen *blackQueen = new Queen(BLACK);
	Queen *whiteQueen = new Queen(WHITE);
	tiles[0][3] = blackQueen;
	tiles[B_SIZE-1][3] = whiteQueen;
}

//Print all tiles a piece can move to. Used for debug purposes.
void Board::printMovable(Position position)
{
	std::vector<Position> positionVector = getMovable(position);
	printPositionVector(positionVector);
}

//See if there is a already a piece on the tile or not.
bool Board::isTileEmpty(Position position)
{
	if(tiles[position.getY()][position.getX()] == NULL)
		return true;
	return false;
}

//Check if the tile exists on the board. ie a tile with index -1 2 doesn't exist.
bool Board::doesTileExist(Position position)
{
	int x = position.getX();
	int y = position.getY();
	if(y >= 0 && y < B_SIZE && x >= 0 && x < B_SIZE)
		return true;
	return false;
}

//Check if a tile belongs to a team
bool Board::isTileTeam(Position pos, int team)
{
	if(doesTileExist(pos) && !isTileEmpty(pos))
	{
		if(tiles[pos.getY()][pos.getX()]->getTeam() == team)
			return true;
	}
	
	return false;
}

//See if there's a checkmate
bool Board::gameOver()
{
	return false;
}

//Return the positions a piece can move to.
std::vector<Position> Board::getMovable(Position position)
{
	int x = position.getX();
	int y = position.getY();
	std::vector<Position> res;
	
	if(doesTileExist(position) && !isTileEmpty(position))
	{
		res = tiles[y][x]->getMovableTiles(position);
		Piece *p = tiles[y][x];
		
		if(p->getRepresentation() == 'R' || p->getRepresentation() == 'Q')
		{
			res = removeBlockingStraight(res, position);
		}
		if(p->getRepresentation() == 'B' || p->getRepresentation() == 'Q')
		{
			res = removeBlockingDiagonal(res, position);
		}
		
		res = removeFriendly(res, p->getTeam());
	}
	
	return res;
}

//Remove all occurances of pieces from a team from a list of positions.
std::vector<Position> Board::removeFriendly(std::vector<Position> positions, int team)
{
	std::vector<Position>::iterator it = positions.begin();
	while(it != positions.end())
	{
		if(!isTileEmpty(*it))
		{
			if(tiles[it->getY()][it->getX()]->getTeam() == team)
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

//Remove positions from the positions array which are block by other pieces from the position initialPosition. Straight
std::vector<Position> Board::removeBlockingStraight(std::vector<Position> positions, Position initialPosition)
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
		if(!isTileEmpty(*it))
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
std::vector<Position> Board::removeBlockingDiagonal(std::vector<Position> positions, Position initialPosition)
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
		if(!isTileEmpty(*it))
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

//Helpful when debugging
void Board::printPositionVector(std::vector<Position> positions)
{
	std::cout << "Printing position vector of size " << positions.size() << ":" << std::endl;
	
	for(std::vector<Position>::iterator it = positions.begin(); it != positions.end(); it++)
	{
		if(doesTileExist(*it))
		{
			std::cout << it->toString() << std::endl;
		}
	}
}

//Print the entire board. Pieces are responsible for printing themselves
void Board::renderBoard()
{
	std::cout << " abcdefgh" << std::endl;
	
	for(int i = 0; i < B_SIZE; i++)
	{
		resetConsoleColor();
		std::cout << B_SIZE - i;
		
		for(int j = 0; j < B_SIZE; j++)
		{
			int bgColor = (i + j) % 2;
			if(tiles[i][j] != NULL)
			{
				tiles[i][j]->printMe(bgColor);
			}
			else
			{
				tiles[i][j]->printEmpty(bgColor);
			}
		}
		
		std::cout << std::endl;
	}
	
	resetConsoleColor();
}

//Reset the console color so we don't get a funky looking command line
void Board::resetConsoleColor()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int Board::getB_SIZE()
{
	return B_SIZE;
}

//Add a piece to position
void Board::addPiece(Piece* piece, Position newPos, Position oldPos)
{
	tiles[newPos.getY()][newPos.getX()] = piece;
	tiles[oldPos.getY()][oldPos.getX()] = NULL;
		
	return;
}

//If there is a piece at the given position, then that piece is removed
void Board::removePiece(Position position)
{
	delete tiles[position.getY()][position.getX()];
	
	return;
}

//Moves a piece from one location to another
bool Board::movePiece(Position from, Position to, int team)
{
	Piece* piece = tiles[from.getY()][from.getX()];
	
	if(piece == NULL)
	{
		std::cout << "Cannot move because there is nothing at this location.";
		return false;
	}
	else
	{
		//Check if the tiles exist and if the player owns the piece
		if(doesTileExist(from) && doesTileExist(to) && !isTileEmpty(from) && isTileTeam(from, piece->getTeam()))
		{
			std::vector<Position> movable = getMovable(from);
			
			//Make sure that the piece can actually move to that tile
			for(std::vector<Position>::iterator it = movable.begin(); it != movable.end(); it++)
			{
				if(*it == to)
				{
					//Move the piece and remove pieces from the destination tile
					if(!isTileEmpty(to) && !isTileTeam(to, piece->getTeam()))
					{
						std::cout << "Removing\n";
						removePiece(to);
					}
					addPiece(piece, to, from);
					
					//Special rules for pawns, kings and rooks
					char type = piece->getRepresentation();
					if(type == 'P' || type == 'K' || type == 'R')
					{
						if(!piece->hasMoved())
							piece->setMoved(true);
					}
					
					return true;
				}
			}
		}
	}
	
	return false;
}