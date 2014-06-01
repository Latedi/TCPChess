#include "board.h"

Board::Board()
{
	initialize();
}

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
	
	renderBoard();
}

void Board::renderBoard()
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(tiles[i][j] != NULL)
			{
				tiles[i][j]->printMe();
			}
			else
			{
				std::cout << "-";
			}
		}
		
		std::cout << std::endl;
	}
}

int Board::getSize()
{
	return SIZE;
}