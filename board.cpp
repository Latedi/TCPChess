#include "board.h"

Board::Board()
{
	initialize();
}

//Delete all existing pieces
Board::~Board()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(tiles[i][j] != NULL)
				delete tiles[i][j];
		}
	}
}

//Place all the pieces on the board
void Board::initialize()
{	
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			tiles[i][j] = NULL;
		}
	}
	
	//Place pawns
	for(int i = 0; i < SIZE; i++)
	{
		Pawn *blackPawn = new Pawn(BLACK);
		Pawn *whitePawn = new Pawn(WHITE);
		tiles[1][i] = blackPawn;
		tiles[SIZE-2][i] = whitePawn;
	}
	
	//Place rooks
	Rook *blackRook1 = new Rook(BLACK);
	Rook *blackRook2 = new Rook(BLACK);
	Rook *whiteRook1 = new Rook(WHITE);
	Rook *whiteRook2 = new Rook(WHITE);
	tiles[0][0] = blackRook1;
	tiles[0][SIZE-1] = blackRook2;
	tiles[SIZE-1][0] = whiteRook1;
	tiles[SIZE-1][SIZE-1] = whiteRook2;
	
	//Place knights
	Knight *blackKnight1 = new Knight(BLACK);
	Knight *blackKnight2 = new Knight(BLACK);
	Knight *whiteKnight1 = new Knight(WHITE);
	Knight *whiteKnight2 = new Knight(WHITE);
	tiles[0][1] = blackKnight1;
	tiles[0][SIZE-2] = blackKnight2;
	tiles[SIZE-1][1] = whiteKnight1;
	tiles[SIZE-1][SIZE-2] = whiteKnight2;
	
	//Place bishops
	Bishop *blackBishop1 = new Bishop(BLACK);
	Bishop *blackBishop2 = new Bishop(BLACK);
	Bishop *whiteBishop1 = new Bishop(WHITE);
	Bishop *whiteBishop2 = new Bishop(WHITE);
	tiles[0][2] = blackBishop1;
	tiles[0][SIZE-3] = blackBishop2;
	tiles[SIZE-1][2] = whiteBishop1;
	tiles[SIZE-1][SIZE-3] = whiteBishop2;
	
	//Place kings
	King *blackKing = new King(BLACK);
	King *whiteKing = new King(WHITE);
	tiles[0][4] = blackKing;
	tiles[SIZE-1][4] = whiteKing;
	
	//Place queens
	Queen *blackQueen = new Queen(BLACK);
	Queen *whiteQueen = new Queen(WHITE);
	tiles[0][3] = blackQueen;
	tiles[SIZE-1][3] = whiteQueen;
	
	renderBoard();
	printMovable(Position(0, 1));
}

//Print all tiles a piece can move to. Used for debug purposes.
void Board::printMovable(Position position)
{
	if(doesTileExist(position) && !isTileEmpty(position))
	{
		std::vector<Position> m = tiles[position.getX()][position.getY()]->getMovableTiles(position, SIZE);
		m = removeFriendly(m, tiles[position.getX()][position.getY()]->getTeam());
		
		std::cout << "printing";
		for(std::vector<Position>::iterator it = m.begin(); it != m.end(); it++)
		{
			std::cout << it->getX() << " " << it->getY() << std::endl;
		}
		
		return;
	}
	
	std::cout << "The position (" << position.getX() << ", " << position.getY() <<
				") either does not exist or does not contain a piece" << std::endl;
}

//See if there is a already a piece on the tile or not.
bool Board::isTileEmpty(Position position)
{
	if(tiles[position.getX()][position.getY()] == NULL)
		return true;
	return false;
}

//Check if the tile exists on the board. ie a tile with index -1 2 doesn't exist.
bool Board::doesTileExist(Position position)
{
	int x = position.getX();
	int y = position.getY();
	if(y >= 0 && y < SIZE && x >= 0 && x < SIZE)
		return true;
	return false;
}

//Remove all occurances of pieces from a team from a list of positions.
std::vector<Position> Board::removeFriendly(std::vector<Position> positions, int team)
{
	std::vector<Position>::iterator it = positions.begin();
	while(it != positions.end())
	{
		std::cout << "remove " << it->toString() << "?\n";
		if(tiles[it->getX()][it->getY()]->getTeam() == team)
		{
			std::cout << "removing " << it->toString() << std::endl;
			positions.erase(it);
			std::cout << "removed it\n";
		}
		else {
			it++;
			std::cout << "did not remove " << it->toString() << std::endl;
		}
	}
	
	return positions;
}

//Print the entire board. Pieces are responsible for printing themselves
void Board::renderBoard()
{
	std::cout << " abcdefgh" << std::endl;
	
	for(int i = 0; i < SIZE; i++)
	{
		resetConsoleColor();
		std::cout << SIZE - i;
		
		for(int j = 0; j < SIZE; j++)
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

int Board::getSize()
{
	return SIZE;
}